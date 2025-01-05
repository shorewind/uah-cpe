/*------------------------------------------------------------------------------
 * File:        Lab09_D2.c (CPE 325 Lab09 Demo code)
 * Function:    SPI Interface (MPS430F2013)
 * Description: Using the MSP-EXP430FG4618 Development Tool establish a data
 *              exchange between the MSP430FG4618 and MSP430F2013 devices using
 *              the SPI mode. The MSP430FG4618 uses the USCI module while the
 *              MSP430F2013 uses the USI module. MSP430FG4618 communicates with
 *              PC via RS232 module using USCI Serial Communication peripheral
 *              interface. This program takes user prompts the user to input a
 *              choice to turn ON or OFF the LED3 located on MSP430F2013. The
 *              user choice is communicated to MSP430FG4618 (master) via  USCI
 *              serial interface and the corresponding action is communicated
 *              to MSP430F2013(slave) via SPI. Based on the user choice,
 *              MSP430F2013 will turn ON or OFF the LED3. This is the salve code
 *              that runs on MSP430F2013.
 *                               Slave                    Master
 *                            MSP430F2013              MSP430FG4618
 *                        -----------------          -----------------
 *                       |              XIN|-    /|\|              XIN|-
 *                       |                 |      | |                 | 32kHz xtal
 *                       |             XOUT|-     --|RST          XOUT|-
 *                       |                 |        |                 |
 *                 LED <-|P1.0             |        |                 |
 *                       |         BF /P1.4|------->|P3.0/BF          |
 *                       |         SDI/P1.7|<-------|P3.1/UCB0SIMO    |
 *                       |         SDO/P1.6|------->|P3.2/UCB0SOMI    |
 *                       |        SCLK/P1.5|<-------|P3.3/UCB0CLK     |
 *
 * Clocks:      ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = DCO = ~1MHz
 *              An external watch crystal between XIN & XOUT is required for ACLK
 * Instructions: 1. Set the following parameters in HyperTerminal
 *                  Port :        COM1
 *                  Baud rate :   19200
 *                  Data bits:    8
 *                  Parity:       None
 *                  Stop bits:    1
 *                  Flow Control: None
 *              2. This lab requires to configure the USI module of MSP430F2013
 *                 as slave and MSP430FG4618 as master in SPI mode.
 *              3. Connect the following jumpers on header 1 (H1) on the
 *                 experimenter's board.  [1-2], [3-4], [5-6], [7-8]
 *                          H1
 *                        _______
 *                      1|-------|2
 *                      3|-------|4
 *                      5|-------|6
 *                      7|-------|8
 *                       |_______|
 *                  Jumper must be present on PWR1, PWR2 and JP2.
 *
 *              4. Download and run this code by the connecting the FET debugger
 *                 to JTAG2 on the experimenter's board.
 *              5. Make sure the device selected is MSP430F2013 in the General
 *                 Options of CCS.
 *
 * Input:       Character 1 or 0 or NULL from the master
 * Output:      Turn on or off the LED3 and send the status of LED3 to master
 *------------------------------------------------------------------------------*/
#include "msp430x20x3.h"
#include <math.h>

#define SET_BUSY_FLAG()   P1OUT |= 0x10
#define RESET_BUSY_FLAG() P1OUT &= ~0x10

unsigned char LEDState, NextState;
unsigned int wdt_cycles, blink;

void SPI_setup(void) {
    USICTL0 |= USISWRST;          // Set UCSWRST -- needed for re-configuration process
    USICTL0 |= USIPE5 + USIPE6 + USIPE7 + USIOE; // SCLK-SDO-SDI port enable,MSB first
    USICTL1 = USIIE;              // USI  Counter Interrupt enable
    USICTL0 &= ~USISWRST;         // **Initialize USCI state machine**
}

void SPI_initComm(void) {
    USICNT = 8;                   // Load bit counter, clears IFG
    USISRL = LEDState;            // Set LED state
    RESET_BUSY_FLAG();            // Reset busy flag
}

void systemInitialize() {
    BCSCTL1 = CALBC1_1MHZ;        // Set DCO
    DCOCTL = CALDCO_1MHZ;
}

void main(void) {
    systemInitialize();
    SPI_setup();                  // Setup USI module in SPI mode
    SPI_initComm();               // Initialization communication
    WDTCTL = WDT_MDLY_32;           // Stop watchdog timer
    P1DIR |= BIT0;
    P1DIR |= BIT4;                // P1.4 as output - Busy flag
    IE1 |= WDTIE;

    blink = 1; // default blink is true
    wdt_cycles = 16; // default for 1Hz

    while(1) {
        _BIS_SR(LPM0_bits + GIE );// Enter LPM0 with interrupt

        switch (NextState) {
            case 0xFF:            // Dummy operation; no change in the state
                break;
            default:
                LEDState = NextState;   // New state
                break;
        }

        // Change the status of LED depending on the command
        if (LEDState > 0 && LEDState <= 20) {
            unsigned int target_freq = LEDState / 4;
            unsigned int target_period = 1 / target_freq * 1000;
            wdt_cycles = round(target_period / 2 / 32);
            blink = 1;
        } else if (LEDState == 0) {
            P1OUT |= BIT0;
            blink = 0;
        }

        USISRL = LEDState;        // Prepares reply to master with new state
        RESET_BUSY_FLAG();        // Clears busy flag - ready for new communication
    }
}

#pragma vector = USI_VECTOR
__interrupt void USI_ISR(void) {
    SET_BUSY_FLAG();              // Set busy flag - busy with new communication
    NextState = USISRL;           // Read new command
    USICNT = 8;                   // Load bit counter for next TX
    _BIC_SR_IRQ(LPM0_bits);       // Exit from LPM0 on RETI
}

#pragma vector = WDT_VECTOR
__interrupt void watchdog_timer(void) {
    static int i = 0;
    if (blink == 1) {
        i++;
        if (i == wdt_cycles) {
            P1OUT ^= BIT0;
            i = 0;
        }
    }
}
