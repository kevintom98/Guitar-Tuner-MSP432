/******************************************************************************************
   File Name           : main.c
   Author&Editor Name  : Kevin Tom
                         Professional Masters in Embedded Systems
                         Fall 2021, UCB.
   Editor email id     : keto9919@colorado.edu
   IDE used for Coding : ccstudio IDE
   Compiler            : GCC
   Date                : 4th December 2021

   Info on Code obtained from other sources: None

*******************************************************************************************/
/*header files*/
#include "msp.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "autocorrelation.h"
#include "lcd.h"
#include "delay.h"
#include "adc.h"
#include "app.h"

/**
 * application entry point
 * i.e main function
 */
void main(void)
{
    /*initialise peripherals*/
    LCD_init();
    ADC_init();
    initUart();

    /*boot up message*/
    displayBootUpMessage();
    printUserInterface();

    while(1)
    {
        /*
         * detect the input audio signal
         * frequency and help tune to guitar
         * string
         */
        tuneGuitarString();
    }
}

/***************************end of file*************************************/
