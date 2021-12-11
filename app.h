/******************************************************************************************
   File Name           : app.h
   Author&Editor Name  : Kevin Tom
                         Professional Masters in Embedded Systems
                         Fall 2021, UCB.
   Editor email id     : keto9919@colorado.edu
   IDE used for Coding : ccstudio IDE
   Compiler            : GCC
   Date                : 4th December 2021

   Info on Code obtained from other sources: None

*******************************************************************************************/

#ifndef APP_H_
#define APP_H_

/***************************************************************************
 * to detect the signal frequency
 *
 * Parameters: ipFrequency --> user provided input frequency
 *
 * Returns: void
 **************************************************************************/
void detectFrequency(register uint16_t ipFrequency);

/***************************************************************************
 * convert string input fed by user to its frequency
 *
 * Parameters: ipFrequency --> user provided input frequency
 *
 * Returns: void
 **************************************************************************/
int convertStringToFreq(char *guitarString);

/***************************************************************************
 * prints the user interface
 *
 * Parameters: void
 *
 * Returns: void
 **************************************************************************/
void printUserInterface();

/***************************************************************************
 * detect the current string frequency and thus achive guitar tuning
 *
 * Parameters: void
 *
 * Returns: void
 **************************************************************************/
void tuneGuitarString();

#endif /* APP_H_ */
