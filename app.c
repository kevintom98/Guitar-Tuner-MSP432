/******************************************************************************************
   File Name           :  app.c
   Author&Editor Name  : Kevin Tom
                         Professional Masters in Embedded Systems
                         Fall 2021, UCB.
   Editor email id     : keto99192@colorado.edu
   IDE used for Coding : ccstudio IDE
   Compiler            : GCC
   Date                : 4th December 2021

   Info on Code obtained from other sources: None

*******************************************************************************************/
/*header files*/
#include <stdio.h>
#include "msp.h"
#include "autocorrelation.h"
#include "lcd.h"
#include <string.h>
#include "uart.h"

/*macros*/
#define ERROR_LIMIT 1
#define BUFSIZE 1024
#define SAMPLING_FREQUENCY 32000

/*static variables*/
static uint16_t buffer[BUFSIZE];

/***************************************************************************
 * to detect the signal frequency
 *
 * Parameters: ipFrequency --> user provided input frequency
 *
 * Returns: void
 **************************************************************************/
void detectFrequency(register uint16_t ipFrequency)
{
    uint32_t result;
    register int index = 0;
    register int period = 0;
    register int frequency = 0;
    register int lowerLimit = 0;
    register int upperLimit = 0;
    register int noOfAttempts = 0;
    char str[100];

    /*setting tolerant frequency range*/
    lowerLimit = ipFrequency - ERROR_LIMIT;
    upperLimit = ipFrequency + ERROR_LIMIT;

    while(1)
    {
       /*start a conversion*/
       ADC14->CTL0 |= 1;

       /*wait till conversion is complete*/
       while(!ADC14->IFGR0);

       /*read conversion result*/
       result  = ADC14->MEM[5];

       buffer[index] = result;
       index++;

       /*
        * when the buffer fills up, then trigger
        * the autocorrelation algorithm
        */
       if(index == (BUFSIZE-1))
       {
           /*reset index to zero for future buffer filling*/
           index  = 0;

           /*autocorrelation algorithm for 14 bit precision ADC values*/
           period = autocorrelate_detect_period(buffer, BUFSIZE,kAC_14bps_unsigned);
           frequency = SAMPLING_FREQUENCY / period;

           noOfAttempts++;

           if((frequency >= lowerLimit) && (frequency <= upperLimit))
           {
               displaySucessMessage();
               sprintf(str, "\r\nString tuned: %d Hz\r\n", frequency);
               putStr(str);

               sprintf(str,"\n\n\r");
               putStr(str);

               break;
           }
           else if(frequency > 0)
           {
               sprintf(str, "\n\rFrequency : %d Hz", frequency);
               putStr(str);
           }

           /*
            * if we reach maximum no of attempts, then
            * break away from the loop
            */
           if(20 == noOfAttempts)
           {
               break;
           }
       }
    }
}

/***************************************************************************
 * convert string input fed by user to its frequency
 *
 * Parameters: ipFrequency --> user provided input frequency
 *
 * Returns: void
 **************************************************************************/
int convertStringToFreq(char *guitarString)
{
    int retVal = 0;

    if(0 == strcmp("E4",guitarString))
        retVal = 330;

    if(0 == strcmp("B3",guitarString))
        retVal = 247;

    if(0 == strcmp("G3",guitarString))
        retVal = 196;

    if(0 == strcmp("D3", guitarString))
        retVal = 147;

    if(0 == strcmp("A2", guitarString))
        retVal = 110;

    if(0 == strcmp("E2", guitarString))
        retVal = 82;

    return retVal;
}

/***************************************************************************
 * prints the user interface
 *
 * Parameters: void
 *
 * Returns: void
 **************************************************************************/
void printUserInterface()
{
    char str[100];

    sprintf(str, "\n\rGUITAR TUNER\r\n");
    putStr(str);

    sprintf(str, "***************************************\r\n");
    putStr(str);

    sprintf(str, "ESD Project by Ananth & Kevin\r\n");
    putStr(str);

    sprintf(str, "***************Strings*****************\r\n");
    putStr(str);

    sprintf(str, "---Frequency(Hz)---------Notation------\r\n");
    putStr(str);

    sprintf(str, "      329.63               E4         \r\n");
    putStr(str);

    sprintf(str, "      246.94               B3         \r\n");
    putStr(str);

    sprintf(str, "      196                  G3         \r\n");
    putStr(str);

    sprintf(str, "      146.83               D3         \r\n");
    putStr(str);

    sprintf(str, "      110                  A2         \r\n");
    putStr(str);

    sprintf(str, "      82.41                E2         \r\n");
    putStr(str);

    sprintf(str, "**************************************\r\n");
    putStr(str);
}

/***************************************************************************
 * detect the current string frequency and thus achive guitar tuning
 *
 * Parameters: void
 *
 * Returns: void
 **************************************************************************/
void tuneGuitarString()
{
    char guitarString[2];
    char str[100];
    register int ipFreq = 0;
    char tuneMessage[20] = "Tuning for ";

    /*Prompt the user to input string of his choice*/
    sprintf(str, "\r\nEnter the string being tuned \r\n");
    putStr(str);

    gets(guitarString);

    tuneMessage[11] = guitarString[0];
    tuneMessage[12] = guitarString[1];

    displayString(tuneMessage);

    ipFreq = convertStringToFreq(guitarString);

    /*display the respective string frequency*/
    sprintf(str, "Frequency for tuning : %d Hz\n\r", ipFreq);
    putStr(str);

    detectFrequency(ipFreq);
}

/*****************************end of file***********************************/
