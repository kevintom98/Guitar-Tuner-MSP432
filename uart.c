/******************************************************************************************
   File Name           : uart.c
   Author&Editor Name  : Kevin Tom
                         Professional Masters in Embedded Systems
                         Fall 2021, UCB.
   Editor email id     : keto9919@colorado.edu
   IDE used for Coding : ccstudio IDE
   Compiler            : GCC
   Date                : 3rd December 2021

   Info on Code obtained from other sources:
                    Inspired from TI Example Reference Code

*******************************************************************************************/
#include "msp.h"
#include "uart.h"

/***************************************************************************
 * writes one byte at a time to uart tx
 *
 * Parameters: c --> char to be written
 *
 * Returns   : void
 **************************************************************************/
void putChar(char c)
{
    while(!(EUSCI_A0->IFG & EUSCI_A_IFG_TXIFG));
    EUSCI_A0->TXBUF = c;
}

/***************************************************************************
 * writes a string via uart tx
 *
 * Parameters: s --> ptr to the string
 *
 * Returns   : void
 **************************************************************************/
void putStr(char* s)
{
    while(*s)
    {
        putChar(*s++);
    }
}

/***************************************************************************
 * initialise pins for UART transmissions
 *
 * Parameters: None
 *
 * Returns   : void
 **************************************************************************/
void initUart()
{
     CS->KEY = CS_KEY_VAL;                   /*Unlock CS module for register access*/
     CS->CTL0 = 0;                           /*Reset tuning parameters*/
     CS->CTL0 = CS_CTL0_DCORSEL_3;           /*Set DCO to 12MHz (nominal, center of 8-16MHz range)*/
     CS->CTL1 = CS_CTL1_SELA_2 |             /*Select ACLK = REFO*/
             CS_CTL1_SELS_3 |                /*SMCLK = DCO*/
             CS_CTL1_SELM_3;                 /*MCLK = DCO*/
     CS->KEY = 0;                            /*Lock CS module from unintended accesses*/

     /*Configure UART pins*/
     P1->SEL0 |= BIT2 | BIT3;                /*set 2-UART pin as secondary function*/

     /*Configure UART*/
     EUSCI_A0->CTLW0 |= EUSCI_A_CTLW0_SWRST; /*Put eUSCI in reset*/
     EUSCI_A0->CTLW0 = EUSCI_A_CTLW0_SWRST | /*Remain eUSCI in reset*/
             EUSCI_B_CTLW0_SSEL__SMCLK;      /*Configure eUSCI clock source for SMCLK*/
     
     /*
         Baud Rate calculation
         12000000/(16*9600) = 78.125
         Fractional portion = 0.125
         User's Guide Table 21-4: UCBRSx = 0x10
         UCBRFx = int ( (78.125-78)*16) = 2
     */
     EUSCI_A0->BRW = 78;                     /*12000000/16/9600*/
     EUSCI_A0->MCTLW = (2 << EUSCI_A_MCTLW_BRF_OFS) |
             EUSCI_A_MCTLW_OS16;

     EUSCI_A0->CTLW0 &= ~EUSCI_A_CTLW0_SWRST; /*Initialize eUSCI*/
     EUSCI_A0->IFG &= ~EUSCI_A_IFG_RXIFG;    /*Clear eUSCI RX interrupt flag*/
     EUSCI_A0->IE |= EUSCI_A_IE_RXIE;        /*Enable USCI_A0 RX interrupt*/
}

/***************************************************************************
 * UART interrupt service routine
 *
 * Parameters: void
 *
 * Returns   : void
 **************************************************************************/
void EUSCIA0_IRQHandler(void)
{
    if (EUSCI_A0->IFG & EUSCI_A_IFG_RXIFG)
    {
        /*Check if the TX buffer is empty first*/
        while(!(EUSCI_A0->IFG & EUSCI_A_IFG_TXIFG));

        /*Echo the received character back*/
        EUSCI_A0->TXBUF = EUSCI_A0->RXBUF;
    }
}
