/******************************************************************************************
   File Name           : delay.c
   Author&Editor Name  : Kevin Tom
                         Professional Masters in Embedded Systems
                         Fall 2021, UCB.
   Editor email id     : keto9919@colorado.edu
   IDE used for Coding : ccstudio IDE
   Compiler            : GCC
   Date                : 4th December 2021

   Info on Code obtained from other sources:

*******************************************************************************************/

#include <stdio.h>
#include "delay.h"

/***************************************************************************
 * to achieve delay in the function
 *
 * Parameters: n --> no of milliseconds
 *
 * Returns: void
 **************************************************************************/
void delayMs(int n)
{
    register int i, j;

    for(j = 0; j < n; j++)
        for(i = 250; i > 0; i--); /*delay*/
}

/*********************************end of file*********************************************/
