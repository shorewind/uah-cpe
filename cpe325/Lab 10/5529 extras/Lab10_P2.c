/*------------------------------------------------------------------------------
 * File:        Lab10_D3.c (CPE 325 Lab10 Demo code)
 * Function:    Sinusoidal wave with DAC (MPS430FG4618)
 * Description: This C program reconstructs the sinusoidal wave (y=1.25(1+sin(x)))
 *              from the samples using DAC and outputs at P6.6. WDT is used to
 *              give an interrupt for every ~0.064ms to wake up the CPU and
 *              feed the DAC with new value. Connect the oscilloscope to P6.6
 *              to observe the signal. The interval used to read the samples
 *              controls the frequency of output signal.
 * Clocks:      ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = DCO = default (~1MHz)
 *              An external watch crystal between XIN & XOUT is required for ACLK
 *
 *                         MSP430xG461x
 *                      -------------------
 *                   /|\|              XIN|-
 *                    | |                 | 32kHz
 *                    --|RST          XOUT|-
 *                      |                 |
 *                      |        DAC0/P6.6|--> sine (10Hz)
 *                      |                 |
 * Input:       None
 * Output:      Sinusoidal wave with 10Hz frequency at P6.6
 * Author:      Aleksandar Milenkovic, milenkovic@computer.org
 *              Max Avula, ma0004@uah.edu
 *------------------------------------------------------------------------------*/
#include <msp430.h>
#include <sine_lut_512.h>  /*512 samples are stored in this table */
#include <math.h>

unsigned char SW1pressed = 0;       // SW1 status (0 not pressed, 1 pressed)
unsigned char SW2pressed = 0;       // SW2 status (0 not pressed, 1 pressed)
unsigned char sinusoid = 1;

void TimerA_setup(void) {
    TACTL = TASSEL_2 + MC_1;              // SMCLK, up mode
    TACCR0 = 68;                         // Sets Timer Freq (1048576*0.0333333sec/512)
    TACCTL0 = CCIE;                       // CCR0 interrupt enabled
}

void DAC_setup(void) {
    ADC12CTL0 = REF2_5V + REFON;          // Turn on 2.5V internal ref volage
    unsigned int i = 0;
    for (i = 50000; i > 0; i--);          // Delay to allow Ref to settle
    DAC12_0CTL = DAC12IR + DAC12AMP_5 + DAC12ENC;   //Sets DAC12
}

void Switch_setup(void) {
    P1IE |= BIT0 | BIT1;            // P1IE.BIT0 and BIT1 interrupt enabled
    P1IES |= BIT0 | BIT1;           // P1IES.BIT0 and BIT1 hi/low edge
    P1IFG &= ~(BIT0 | BIT1);        // P1IFG.BIT0 and BIT1 are cleared
}

void main(void) {
    WDTCTL = WDTPW + WDTHOLD;             // Stop WDT
    TimerA_setup();                       // Set timer to uniformly distribute the samples
    DAC_setup();                          // Setup DAC
    Switch_setup();
    unsigned int i = 0;
    int value = 2048;
    int sign = -1;

    while (1) {
        __bis_SR_register(LPM0_bits + GIE); // Enter LPM0, interrupts enabled
        if (sinusoid == 1) {
            DAC12_0DAT = LUT512[i];
            i=(i+1)%512;
        } else if (sinusoid == 0) {
            DAC12_0DAT = value;
            if (i % 256 == 0) {
                sign = -sign;
            }
            value += sign * 8;
            i = (i+1)%256;
        }
    }
}

#pragma vector = TIMERA0_VECTOR
__interrupt void TA0_ISR(void) {
    __bic_SR_register_on_exit(LPM0_bits);  // Exit LPMx, interrupts enabled
}

#pragma vector = PORT1_VECTOR
__interrupt void Port1_ISR(void) {
    if (P1IFG&BIT0) {
        if (SW1pressed == 0) {
            sinusoid = 0;
            TACCR0 = 68;
            SW1pressed = 1;
            P1IFG &= ~BIT0;               // P1IFG.BIT0 is cleared
            P1IES &= ~BIT0;               // P1IES.BIT0 low/high edge
        } else if (SW1pressed == 1) {
            sinusoid = 1;
            TACCR0 = 68;
            SW1pressed = 0;
            P1IFG &= ~BIT0;                // P1IFG.BIT0 is cleared
            P1IES |= BIT0;                 // P1IES.BIT0 hi/low edge
        }
    }
    else if (P1IFG&BIT1) {
        if (SW2pressed == 0) {
            SW2pressed = 1;
            TACCR0 = 136;
            P1IFG &= ~BIT1;               // P1IFG.BIT1 is cleared
            P1IES &= ~BIT1;               // P1IES.BIT1 low/high edge
        } else if (SW2pressed == 1) {
            SW2pressed = 0;
            TACCR0 = 68;
            P1IFG &= ~BIT1;                // P1IFG.BIT1 is cleared
            P1IES |= BIT1;                 // P1IES.BIT1 hi/low edge
        }
    }
}
