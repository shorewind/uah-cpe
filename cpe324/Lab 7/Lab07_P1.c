/*------------------------------------------------------------------------------
 * File:        Lab7_D6.c (CPE 325 Lab7 Demo code)
 * Function:    Blinking LED1 & LED2 using Timer_B with interrupts (MPS430FG4618)
 * Description: In this C program, Timer_B is configured for up/down mode with
 *              ACLK source and interrupts for channel 0 and channel 1 are
 *              enabled. In up/down mode timer TB counts the value from 0 up to
 *              value stored in TB0CCR0 and then counts back to 0. The interrupt
 *              for TB0 is generated when the counter reaches value in TB0CCR0.
 *              The interrupt TB1 is generated whenever the counter reaches value
 *              in TB0CCR1. Thus, TB1 gets two interrupts while counting upwards
 *              and counting downwards. This simulates a PWM control - adjusting
 *              the TB1 and TB0 CCR register values adjusts the duty cycle of the
 *              PWM signal.
 * Clocks:      ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = DCO = default (~1MHz)
 *              An external watch crystal between XIN & XOUT is required for ACLK
 *
 *                          MSP430xG461x
 *                       -----------------
 *                   /|\|              XIN|-
 *                    | |                 | 32kHz
 *                    --|RST          XOUT|-
 *                      |                 |
 *                      |             P2.1|--> LED2(YELLOW)
 *                      |             P2.2|--> LED1(GREEN)
 * Input:       None
 * Output:      LED1 blinks at 1.64Hz with 20-80% duty cycle and LED2 blinks at
 *              0.82Hz with 50-50% duty cycle.
 * Author:      Aleksandar Milenkovic, milenkovic@computer.org
 *------------------------------------------------------------------------------*/
#include <msp430fg4618.h>
#include <stdio.h>

#define SW1 P1IN&BIT0
#define SW2 P1IN&BIT1

int main(void) {
    WDTCTL = WDTPW + WDTHOLD;       // Stop WDT

    P2DIR |= BIT2;                  // Set P2.2 (LED1) as output
    P2OUT |= BIT2;
    P2SEL |= BIT2;                  // Select Timer B0 output on P2.2

    P1IE |= BIT0 | BIT1;            // P1IE.BIT0 and BIT1 interrupt enabled
    P1IES |= BIT0 | BIT1;           // P1IES.BIT0 and BIT1 hi/low edge
    P1IFG &= ~(BIT0 | BIT1);        // P1IFG.BIT0 and BIT1 are cleared

    TBCTL = TBSSEL_2 + MC_1;        // SMCLK, Up mode
    TBCCTL1 = OUTMOD_2;             //

    TBCCR0 = 40;                    // Set max count value
    TBCCR1 = 0;                     // Set count value

    _BIS_SR(LPM0_bits + GIE);       // low power mode w/ interrupts
}

// Port 1 interrupt service routine
#pragma vector = PORT1_VECTOR
__interrupt void Port1_ISR (void) {
    if (SW1 && SW2) {
        __delay_cycles(20000);
        if (SW1 && SW2) {
            printf("both pressed\n");
            P1IFG &= ~BIT1;                // P1IFG.BIT1 is cleared
            P1IFG &= ~BIT0;               // P1IFG.BIT0 is cleared
        }
    } else if (!SW1 && SW2) {
        __delay_cycles(20000);
        if (!SW1 && SW2) {
            if (TBCCR1 > 0) {
                TBCCR1 -= 10;
            }
            printf("sw2 pressed %u\n", TBCCR1);
            P1IFG &= ~BIT1;               // P1IFG.BIT1 is cleared
        }
    } else if (SW1 && !SW2) {
        __delay_cycles(20000);
        if (SW1 && !SW2) {
            if (TBCCR1 < TBCCR0) {
                TBCCR1 += 10;
            }
            printf("sw1 pressed %u\n", TBCCR1);
            P1IFG &= ~BIT0;               // P1IFG.BIT0 is cleared
        }
    } else {
        P1IFG &= ~BIT0;                // P1IFG.BIT0 is cleared
        P1IFG &= ~BIT1;                // P1IFG.BIT1 is cleared
    }
}
