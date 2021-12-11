/******************************************************************************************
   File Name           :  autocorrelation.h
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

#ifndef AUTOCORRELATION_H_
#define AUTOCORRELATION_H_

#include <stdint.h>

typedef enum
{
  kAC_12bps_unsigned,   // 12 bits per sample, unsigned samples (stored in 16 bits)
  kAC_16bps_unsigned,   // 16 bits per sample, unsigned samples
  kAC_12bps_signed,     // 12 bits per sample, signed samples (stored in 16 bits)
  kAC_16bps_signed,      // 16 bits per sample, signed samples
  kAC_14bps_unsigned
} autocorrelate_sample_format_t;

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
    autocorrelate_sample_format_t format);

#endif /* AUTOCORRELATION_H_ */

/***************************end of file*************************************/
