//******************************************************************************
//   MSP430F552x Demo - USCI_A0, 115200 UART Echo ISR, DCO SMCLK
//
//   Description: Echo a received character, RX ISR used. Normal mode is LPM0.
//   USCI_A0 RX interrupt triggers TX Echo.
//   Baud rate divider with 1048576hz = 1048576/115200 = ~9.1 (009h|01h)
//   ACLK = REFO = ~32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
//   See User Guide for baud rate divider table
//
//                 MSP430F552x
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//            |     P3.3/UCA0TXD|------------>
//            |                 | 115200 - 8N1
//            |     P3.4/UCA0RXD|<------------
//
//   Bhargavi Nisarga
//   Texas Instruments Inc.
//   April 2009
//   Built with CCSv4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include <msp430.h>
#include <stdio.h>
#include <string.h>

// ANSI escape codes for text color
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_RESET   "\x1b[0m"

void UART_setup();
void UART_send_character(char);
void UART_send_string(char* string);
void UART_get_word(char* buffer, int limit);


void main(void) {

    WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
    UART_setup();
    char input[50];
    char strings[3][50] = {"Hello", "hello", "hELLO"};

    while (1) {
        do {
            UART_send_string(COLOR_BLUE);
            UART_send_string("\r\nWelcome to typing practice! Are you ready to start? ");
            UART_send_string(COLOR_RESET);
            UART_get_word(input, sizeof(input));
        } while (strcmp(input, "Let's go!") != 0);

        UART_send_string("\r\nType in the following strings:\r\n\r\n");

        int i = 0;
        while (i < 3) {
            UART_send_string(strings[i]);
            UART_send_string("\r\n");
            UART_get_word(input, sizeof(input));

            if (strcmp(input, strings[i]) == 0) {
                UART_send_string(COLOR_GREEN);
                UART_send_string("\r\n\r\nCorrect!\r\n\r\n");
                UART_send_string(COLOR_RESET);
            } else {
                int incorrect_chars = 0;
                int max_index;
                int j = 0;
                if (strlen(strings[i]) > strlen(input)) {
                    max_index = strlen(strings[i]) - 1;
                } else {
                    max_index = strlen(input) - 1;
                }
                while (j <= max_index) {
                    if (strings[i][j] != input[j]) {
                        incorrect_chars++;
                        UART_send_string(COLOR_RED);
                        UART_send_character(input[j]);
                        UART_send_string(COLOR_RESET);
                    } else {
                        UART_send_character(input[j]);
                    }
                    j++;
                }

                char result[50];
                UART_send_string(COLOR_RED);
                snprintf(result, sizeof(result), "\r\n\r\nIncorrect characters: %d\r\n\r\n", incorrect_chars);
                UART_send_string(result);
                UART_send_string(COLOR_RESET);
            }
            i++;
        }
    }

}


void UART_setup() {
    P3SEL |= BIT3+BIT4;                       // P3.3,4 = USCI_A0 TXD/RXD
    UCA0CTL1 |= UCSWRST;                      // **Put state machine in reset**
    UCA0CTL1 |= UCSSEL_2;                     // SMCLK
    UCA0BR0 = 18;                             // 1MHz / 57600 = 18.2(see User's Guide)
    UCA0BR1 = 0;                              // 1MHz 57600
    UCA0MCTL |= UCBRS_2 + UCBRF_0;            // Modulation UCBRSx=1, UCBRFx=0
    UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
    UCA0IE |= UCRXIE;                         // Enable USCI_A0 RX interrupt
}


void UART_send_character(char my_char) {
    while (!(UCA0IFG&UCTXIFG));             // USCI_A0 TX buffer ready?
    UCA0TXBUF = my_char;                  // TX -> RXed character
}


void UART_send_string(char* string) {
    int i;
    for (i = 0; i < strlen(string); i++) {
        UART_send_character(string[i]);
    }
}


void UART_get_word(char* buffer, int limit)
{
    int i = 0;
    char received_char;

    while (i < limit - 1) {
        while (!(UCA0IFG & UCRXIFG));  // USCI_A0 RX buffer ready?
        received_char = UCA0RXBUF;     // RX -> Get received character
        UART_send_character(received_char);

        if (received_char == '\r') {
            break;
        }
        buffer[i] = received_char;
        i++;
    }

    buffer[i] = '\0';  // Terminate the string with null character
}
