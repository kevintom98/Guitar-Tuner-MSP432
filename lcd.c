/******************************************************************************************
   File Name           : lcd.c
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
/*header files*/
#include <stdio.h>
#include "msp.h"
#include "lcd.h"
#include "delay.h"

/*macros*/
#define RS 0x20 /*P3.5 mask*/
#define RW 0x40 /*P3.6 mask*/
#define EN 0x80 /*P3.7 mask*/
#define LCD_DELAY 250
#define ASCII_OFFSET 48

/***************************************************************************
 * to execute commands to LCD
 *
 * Parameters: command --> the command for LCD
 *
 * Returns: void
 **************************************************************************/
void LCD_command(register unsigned char command)
{
    /*RS = 0, R/W = 0*/
    P3->OUT &= ~(RS | RW);

    /*put command on data bus*/
    P4->OUT = command;

    /*pulse E high*/
    P3->OUT |= EN;

    delayMs(0);

    P3->OUT &= ~EN;

    /*command 1 and 2 need up to 1.64ms*/
    if(command < 4)
        delayMs(4);
    else
        delayMs(1);/*all other 40 ms*/
}

/***************************************************************************
 * initialise LCD
 *
 * Parameters: void
 *
 * Returns: void
 **************************************************************************/
void LCD_init()
{
    /*make P3 pins output for control*/
    P3->DIR |= RS | RW | EN;

    /*make P4 pins output for data*/
    P4->DIR = 0xFF;

    /*initialisation sequence*/
    delayMs(30);
    LCD_command(0x30);
    delayMs(10);

    LCD_command(0x30);
    delayMs(1);
    LCD_command(0x30);

    LCD_command(0x38);
    LCD_command(0x06);
    LCD_command(0x01);
    LCD_command(0x0F);
}

/***************************************************************************
 * to send data to LCD
 *
 * Parameters: data --> data to be sent to LCD
 *
 * Returns: void
 **************************************************************************/
void LCD_data(register unsigned char data)
{
    /*RS = 1*/
    P3->OUT |= RS;

    /*R/W = 0*/
    P3->OUT &= ~RW;

    /*put data on bus*/
    P4->OUT = data;

    /*pulse E*/
    P3->OUT |= EN;

    delayMs(0);

    /*clear E*/
    P3->OUT &= ~EN;

    /*wait for controller to do the display*/
    delayMs(1);
}

/***************************************************************************
 * to display string on LCD
 *
 * Parameters: str --> the string to be displayed
 *
 * Returns: void
 **************************************************************************/
void displayString(char *str)
{
    register int i = 0;

    LCD_command(1);
    delayMs(LCD_DELAY);
    LCD_command(0x80);

    for(i = 0; str[i] != '\0'; i++)
    {
        LCD_data(str[i]);
    }

    delayMs(LCD_DELAY);
}

/***************************************************************************
 * to display frequency values on LCD
 *
 * Parameters: frequency --> frequency to be displayed
 *
 * Returns: void
 **************************************************************************/
void displayFrequency(register int frequency)
{
    register int temp1 = 0, temp2 = 0, temp3 = 0, temp4 = 0;

    if(frequency <= 0)
    {
        displayString("Frequency is 0");
    }

    if(frequency >= 100)
    {
        temp1 = frequency / 100;
        temp2 = frequency % 100;
    }
    else
    {
        temp2 = frequency;
    }

    temp3 = temp2 / 10;
    temp4 = temp2 % 10;

    displayString("Frequency ");

    LCD_data(temp1 + ASCII_OFFSET);
    LCD_data(temp3 + ASCII_OFFSET);
    LCD_data(temp4 + ASCII_OFFSET);
}

/***************************************************************************
 * to display boot up message
 *
 * Parameters: void
 *
 * Returns: void
 **************************************************************************/
void displayBootUpMessage()
{
    displayString("Guitar Tuner");
}

/***************************************************************************
 * to display success message
 *
 * Parameters: void
 *
 * Returns: void
 **************************************************************************/
void displaySucessMessage()
{
    displayString("String tuned!!:)");
}

/***************************end of file*************************************/
