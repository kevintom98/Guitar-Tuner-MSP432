/******************************************************************************************
   File Name           :  adc.c
   Author&Editor Name  : Ananth Deshpande
                         Professional Masters in Embedded Systems
                         Fall 2021, UCB.
   Editor email id     : ande9392@colorado.edu
   IDE used for Coding : ccstudio IDE
   Compiler            : GCC
   Date                : 4th December 2021

   Info on Code obtained from other sources:

*******************************************************************************************/
/*header files*/
#include "msp.h"
#include "adc.h"

/***************************************************************************
 * Initialise ADC
 *
 * Parameters: None
 *
 * Returns: void
 **************************************************************************/
void ADC_init()
{
    /*configure P2.2-P2.0 as output for tricolor LEDs*/
    P2->SEL0 &= ~7;
    P2->SEL1 &= ~7;
    P2->DIR |= 7;

    /*power on and disable during configuration*/
    ADC14->CTL0 = 0x00000010;

    /*S/H pulse mode, sysclk, 32 sample clocks, software trigger*/
    ADC14->CTL0 |= 0x04080300;

    /*14-bit resolution*/
    ADC14->CTL1 = 0x00000030;

    /*A6 input, single-ended, vref=vcc*/
    ADC14->MCTL[5] = 5;

    /*configure P5.0 for A6*/
    P5->SEL1 |= 0x01;
    P5->SEL0 |= 0x01;

    /*convert for mem reg 5*/
    ADC14->CTL1 |= 0x00050000;

    /*enable ADC after configuration*/
    ADC14->CTL0 |= 2;
}


