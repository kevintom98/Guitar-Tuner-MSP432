/******************************************************************************************
   File Name           :  autocorrelation.c
   Author&Editor Name  : Ananth Deshpande
                         Professional Masters in Embedded Systems
                         Fall 2021, UCB.
   Editor email id     : ande9392@colorado.edu
   IDE used for Coding : ccstudio IDE
   Compiler            : GCC
   Date                : 5th December 2021

   Info on Code obtained from other sources:
       Our idea of correlation was derived from the websites listed below,
    https://www.instructables.com/Reliable-Frequency-Detection-Using-DSP-Techniques/
    https://github.com/akellyirl/Arduino-Guitar-Tuner/blob/master/Tuner_aRead.ino

*******************************************************************************************/
/*header file*/
#include "autocorrelation.h"
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

/***************************************************************************
 * autocorrelation algorithm to detect period
 *
 * Parameters: samples --> pointer to samples in buffer
 *             nsamp --> number of samples
 *             format --> the sizeof digital values from ADC ( 12, 14 or 16)
 *
 * Returns: void
 **************************************************************************/
int autocorrelate_detect_period(void *samples, uint32_t nsamp,
    autocorrelate_sample_format_t format)
{
  register int32_t sum = 0;
  register int prev_sum = 0, i = 0, k = 0;
  register int32_t thresh = 0;
  register bool slope_positive = false;

  int32_t s1 = 0;
  int32_t s2 = 0;

  sum = 0;
  for (i=0; i < nsamp; i++)
  {
    prev_sum = sum;
    sum = 0;

    for (k=0; k < nsamp - i; k++)
    {
      //The code ca be used for 12,14 or 16 bit ADC configurations
      switch (format)
      {
      case kAC_12bps_unsigned:
        s1 = (int32_t)*((uint16_t*)samples + k) - (1 << 11);
        s2 = (int32_t)*((uint16_t*)samples + k+i) - (1 << 11);
        sum += (s1 * s2) >> 12;
        break;

      case kAC_14bps_unsigned:
              s1 = (int32_t)*((uint16_t*)samples + k) - (1 << 13);
              s2 = (int32_t)*((uint16_t*)samples + k+i) - (1 << 13);
              sum += (s1 * s2) >> 14;
              break;

      case kAC_16bps_unsigned:
        s1 = (int32_t)*((uint16_t*)samples + k) - (1 << 15);
        s2 = (int32_t)*((uint16_t*)samples + k+i) - (1 << 15);
        sum += (s1 * s2) >> 16;
        break;

      case kAC_12bps_signed:
      case kAC_16bps_signed:
        s1 = *((int16_t*)samples + k);
        s2 = *((int16_t*)samples + k+i);
        sum += (s1 * s2) >> (format == kAC_12bps_signed ? 12 : 16);
        break;
      }
    }

    if (i == 0)
    {
      thresh = sum / 2;

    } else if ((sum > thresh) && (sum - prev_sum > 0))
    {
      /*slope is positive, so now enter mode where we're looking for*/
      /*negative slope*/
      slope_positive = true;

    } else if (slope_positive && (sum - prev_sum) <= 0)
    {
      /*We have crested the peak and started down the other*/
      /*side; actual peak was one sample back*/
      return i-1;
    }
  }

  /*no correlation found*/
  return -1;
}

/***************************end of file*************************************/
