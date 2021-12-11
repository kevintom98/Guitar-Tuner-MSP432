/******************************************************************************************
   File Name           : lcd.h
   Author&Editor Name  : Ananth Deshpande
                         Professional Masters in Embedded Systems
                         Fall 2021, UCB.
   Editor email id     : ande9392@colorado.edu
   IDE used for Coding : ccstudio IDE
   Compiler            : GCC
   Date                : 4th December 2021

   Info on Code obtained from other sources:

   This code has been obtained from TI C code examples and has been edited
   according to our program needs
*******************************************************************************************/

#ifndef LCD_H_
#define LCD_H_

/***************************************************************************
 * initialise LCD
 *
 * Parameters: void
 *
 * Returns: void
 **************************************************************************/
void LCD_init();

/***************************************************************************
 * to execute commands to LCD
 *
 * Parameters: command --> the command for LCD
 *
 * Returns: void
 **************************************************************************/
void LCD_command(register unsigned char command);

/***************************************************************************
 * to send data to LCD
 *
 * Parameters: data --> data to be sent to LCD
 *
 * Returns: void
 **************************************************************************/
void LCD_data(register unsigned char data);

/***************************************************************************
 * to display string on LCD
 *
 * Parameters: str --> the string to be displayed
 *
 * Returns: void
 **************************************************************************/
void displayString(char *str);

/***************************************************************************
 * to display frequency values on LCD
 *
 * Parameters: frequency --> frequency to be displayed
 *
 * Returns: void
 **************************************************************************/
void displayFrequency(register int frequency);

/***************************************************************************
 * to display boot up message
 *
 * Parameters: void
 *
 * Returns: void
 **************************************************************************/
void displayBootUpMessage();

/***************************************************************************
 * to display success message
 *
 * Parameters: void
 *
 * Returns: void
 **************************************************************************/
void displaySucessMessage();

#endif /* LCD_H_ */

/***************************end of file*************************************/
