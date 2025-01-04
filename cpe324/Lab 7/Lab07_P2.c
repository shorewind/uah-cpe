/*------------------------------------------------------------------------------
 * File:        Lab7_D6.c (CPE 325 Lab7 Demo code)
 * Function:    Blinking LED1 & LED2 using Timer_B with interrupts (MPS430FG4618)
 * Description:
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
#include <msp430xG46x.h>

unsigned int buzz = 0;

void main(void)
{
    WDTCTL = WDT_MDLY_32;             // 1 s interval timer
    P2DIR |= BIT2;                    // Set P2.2 to output direction
    P3DIR |= BIT5;                    // Set P3.5 to output direction
    P3SEL |= BIT5;                    // Set P3.5 as peripheral function (Timer B output)
    P3OUT &= ~BIT5;
    TB0CTL = TBSSEL_1 + MC_1;         // ACLK is clock source, Up mode
    TB0CCTL4 = OUTMOD_4;              // Toggle mode for TB0CCR1 (buzzer)
    IE1 |= WDTIE;                     // Enable WDT interrupt
    _BIS_SR(LPM0_bits + GIE);         // Enter LPM0 with interrupt
}

// Watchdog Timer interrupt service routine
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void) {
    static int i = 0;
    i++;
    if (i == 32) {
        P2OUT ^= BIT2;                    // Toggle P2.2 using exclusive-OR
        if (buzz == 0) {
            buzz = 1;
            TB0CCR0 = 16;                 // Set TB0CCR0 for 1 kHz frequency (ACLK is assumed to be 32.768 kHz)
        } else {
            buzz = 0;
            TB0CCR0 = 0;
        }
        i = 0;
    }
}


