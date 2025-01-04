/********************************************************************************
 *   File:        Lab6_D5.c
 *   Description: The program detects when SW1 is pressed and turns on LED1.
 *                LED1 is kept on as long as SW1 is pressed.
 *                P1_ISR is used to detect both SW1 presses and releases.
 *   Board:       MSP430FG461x/F20xx Experimenter Board
 *   Clocks:      ACLK = 32.768kHz, MCLK = SMCLK = default DCO
 *
 *                 MSP430FG461x
 *            +-----------------+
 *            |                 |
 *            |                 |
 *            |                 |
 *            |                 |
 *            |             P2.2|--> LED1
 *            |             P1.0|<-- SW1
 *
 *   Author: Aleksandar Milenkovic, milenkovic@computer.org
 *   Date:   September 2010
********************************************************************************/
#include  <msp430.h>

unsigned char SW1pressed = 0;       // SW1 status (0 not pressed, 1 pressed)
unsigned char SW2pressed = 0;       // SW2 status (0 not pressed, 1 pressed)

void main(void) {
    WDTCTL = WDTPW+WDTHOLD;         // Stop WDT
    P2DIR |= BIT2;                  // Set LED1 as output
    P2DIR |= BIT1;                  // Set LED2 as output
    P2OUT = 0x00;                   // Clear LED1, LED2 status
    SW1pressed = 0;                 // Initialize SW1 status
    SW2pressed  = 0;
    _EINT();                        // Enable interrupts
    P1IE |= BIT0;                   // P1IE.BIT0 interrupt enabled
    P1IE |= BIT1;
    P1IES |= BIT0;                  // P1IES.BIT0 hi/low edge
    P1IES |= BIT1;
    P1IFG &= ~BIT0;                 // P1IFG.BIT0 is cleared
    P1IFG &= ~BIT1;

    FLL_CTL0 |= XCAP18PF;
    SCFI0 |= FN_2;
    SCFQCTL = 75;
    P1DIR |= 0x32;
    P1SEL |= 0x32;

    while(1) {
        __delay_cycles(1048576);
        P2OUT ^= BIT1;  // toggle LED2
    }
}

// Port 1 interrupt service routine
#pragma vector = PORT1_VECTOR
__interrupt void Port1_ISR (void) {
    if (P1IFG&BIT0) {
        if (SW1pressed == 0) {
            SW1pressed = 1;
            P2OUT |= BIT2;                // LED1 is turned ON
            P1IFG &= ~BIT0;               // P1IFG.BIT0 is cleared
            P1IES &= ~BIT0;               // P1IES.BIT0 low/high edge
        } else if (SW1pressed == 1) {
            SW1pressed = 0;
            P2OUT &= ~BIT2;                // LED1 is turned OFF
            P1IFG &= ~BIT0;                // P1IFG.BIT0 is cleared
            P1IES |= BIT0;                 // P1IES.BIT0 hi/low edge
        }
    } else if (P1IFG&BIT1) {
        if (SW2pressed == 0) {
            SW2pressed = 1;
            P2OUT |= BIT2;                // LED1 is turned ON
            P1IFG &= ~BIT1;               // P1IFG.BIT0 is cleared
            P1IES &= ~BIT1;               // P1IES.BIT0 low/high edge
        } else if (SW2pressed == 1) {
            SW2pressed = 0;
            P2OUT &= ~BIT2;                // LED1 is turned OFF
            P1IFG &= ~BIT1;                // P1IFG.BIT0 is cleared
            P1IES |= BIT1;                 // P1IES.BIT0 hi/low edge
        }
    }
}
