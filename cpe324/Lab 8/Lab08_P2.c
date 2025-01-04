/*------------------------------------------------------------------------------
 * File:        Demo8_D4.c
 * Function:    Send floating data to Serial port
 * Description: UAH serial app expects lower byte first so send each byte at a
 *              time sending Lowest byte first
 * Clocks:      ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO
 *
 * Instructions: Set the following parameters in putty
 * Port: COM1
 * Baud rate: 115200
 * Data bits: 8
 * Parity: None
 * Stop bits: 1
 * Flow Control: None
 *
 *        MSP430xG461x
 *     -----------------
 * /|\ |            XIN|-
 *  |  |               | 32kHz
 *  |--|RST        XOUT|-
 *     |               |
 *     |   P2.4/UCA0TXD|------------>
 *     |               | 115200 - 8N1
 *     |   P2.5/UCA0RXD|<------------
 *     |               |
 * Input:     None
 * Output:    Ramp signal in UAH Serial app
 * Author:    Prawar Poudel
 * Date:      October 2018
 *----------------------------------------------------------------------------*/
#include <msp430.h>
#include <stdint.h>

volatile float myData;

void UART_setup(void) {
    P3SEL |= BIT3+BIT4;                       // P3.3,4 = USCI_A0 TXD/RXD
    UCA0CTL1 |= UCSWRST;                      // **Put state machine in reset**
    UCA0CTL1 |= UCSSEL_2;                     // SMCLK
    UCA0BR0 = 18;                             // 1MHz / 57600 = 18.2(see User's Guide)
    UCA0BR1 = 0;                              // 1MHz 57600
    UCA0MCTL |= UCBRS_2 + UCBRF_0;            // Modulation UCBRSx=1, UCBRFx=0
    UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
}

void UART_putCharacter(char c) {
    while (!(UCA0IFG&UCTXIFG));             // USCI_A0 TX buffer ready? Wait for previous character to transmit
    UCA0TXBUF = c;               // Put character into tx buffer
}

int main() {
    WDTCTL = WDT_MDLY_32;
    UART_setup();                // Initialize USCI_A0 module in UART mode
    SFRIE1 |= WDTIE;

    myData = 0.0;
    __bis_SR_register(LPM0_bits + GIE);
}

// Sends a ramp signal; amplitude of one period ranges from 0.0 to 9.9
#pragma vector = WDT_VECTOR
__interrupt void watchdog_timer(void) {
    static int counter = 0;

    if (counter < 12) {
        static int multiplier = 0;
        static int sign = 1;
        multiplier += sign;

        if (multiplier == 0 || multiplier == 90) {
            sign = -sign;
            counter++;
        }

        char index = 0;
        // Use character pointers to send one byte at a time
        char *myPointer = (char* )&myData;

        UART_putCharacter(0x55);                // Send header
        for(index = 0; index < 4; index++) {    // Send 4-bytes of myData
            UART_putCharacter(myPointer[index]);
        }

        // Update myData for next transmission
        myData = multiplier * 0.01;
    } else if (counter == 12) {
        counter++;
        char index = 0;
        // Use character pointers to send one byte at a time
        char *myPointer = (char* )&myData;

        UART_putCharacter(0x55);                // Send header
        for(index = 0; index < 4; index++) {    // Send 4-bytes of myData
            UART_putCharacter(myPointer[index]);
        }
    }
}
