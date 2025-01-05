/*------------------------------------------------------------------------------
 * File:        Lab08_P1.c
 * Function:    Typing practice
 * Description: Prompts input for three different strings and counts/shows the
 *            incorrect characters if there are any
 * Input:     Characters entered via MobaXterm received via UART
 * Output:    Results of string comparisons sent over UART
 * Author:    Esther Shore
 * Date:      July 2023
 *----------------------------------------------------------------------------*/
#include <msp430xG46x.h>
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
void caesar_cipher(char* string);
void substitution_cipher(char* string);
void vigenere_cipher(char* string);
void setCaesar();
void setSubstitution();
void setVigenere();
void switch_setup();
void timerB_setup();
void clearStates();

unsigned int caesar = 1;
unsigned int substitution = 0;
unsigned int vigenere = 0;
unsigned int S1pressed = 0;

void main(void) {

    WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
    _EINT();
    switch_setup();
    timerB_setup();
    P2DIR |= BIT1;
    P2SEL |= BIT1 + BIT4 + BIT5;
    UART_setup();

//    char input[50];
    UART_send_string(COLOR_RED);
    UART_send_string("\r\nWelcome to cipher tool!");
    UART_send_string(COLOR_BLUE);
    UART_send_string("\r\n\r\nPress switch 1 to toggle through cipher options\r\n");
    UART_send_string(COLOR_RESET);
    while (1) {

        UART_send_string(COLOR_GREEN);
        if (caesar == 1) {
            UART_send_string("\r\nCaesar Cipher\r\n\r\n");
            TB0CCR0 = 32000;
        } else if (substitution == 1) {
            UART_send_string("\r\nSubstitution Cipher\r\n\r\n");
            TB0CCR0 = 16000;
        } else if (vigenere == 1) {
            UART_send_string("\r\nVigenere Cipher\r\n\r\n");
            TB0CCR0 = 8000;
        }

        _BIS_SR(LPM0_bits + GIE);
    }
}

void setCaesar() {
    caesar = 1;
    substitution = 0;
    vigenere = 0;
}

void setSubstitution() {
    caesar = 0;
    substitution = 1;
    vigenere = 0;
}

void setVigenere() {
    caesar = 0;
    substitution = 0;
    vigenere = 1;
}

void clearStates() {
    caesar = 0;
    substitution = 0;
    vigenere = 0;
}

void UART_setup() {
    UCA0CTL1 |= UCSWRST;                      // **Put state machine in reset**
    UCA0CTL1 |= UCSSEL_2;                     // SMCLK
    UCA0BR0 = 18;                             // 1MHz / 57600 = 18.2(see User's Guide)
    UCA0BR1 = 0;                              // 1MHz 57600
    UCA0MCTL |= UCBRS_2 + UCBRF_0;            // Modulation UCBRSx=1, UCBRFx=0
    UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
    IE2 |= UCA0RXIE;                         // Enable USCI_A0 RX interrupt
}


void switch_setup() {
    P1IE |= BIT0;
    P1IES |= BIT0;
    P1IFG &= ~BIT0;  // switch 2 setup
}

void timerB_setup() {
    TB0CCTL0 = OUTMOD_4;
    TB0CTL = TBSSEL_1 + MC_1;
    TB0CCR0 = 32767;
}

void UART_send_character(char my_char) {
    while (!(IFG2&UCA0TXIFG));             // USCI_A0 TX buffer ready?
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
        while (!(IFG2 & UCA0RXIFG));  // USCI_A0 RX buffer ready?
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

#pragma vector = PORT1_VECTOR
__interrupt void Port1_ISR(void) {
    if (P1IFG&BIT0) {
        if (S1pressed == 0) {
            __delay_cycles(20000);
            if (S1pressed == 0) {
                printf("sw1 pressed\n");
                S1pressed = 1;
                if (caesar == 1) {
                    clearStates();
                    printf("caesar");
                    setSubstitution();
                    UART_send_string("\r\nSubstitution Cipher\r\n\r\n");
                    TB0CCR0 = 16000;
                } else if (substitution == 1) {
                    clearStates();
                    printf("substitution");
                    setVigenere();
                    UART_send_string("\r\nVigenere Cipher\r\n\r\n");
                    TB0CCR0 = 8000;
                } else if (vigenere == 1) {
                    clearStates();
                    printf("vigenere");
                    setCaesar();
                    UART_send_string("\r\nCaesar Cipher\r\n\r\n");
                    TB0CCR0 = 32000;
                }
                P1IFG &= ~BIT0;               // P1IFG.BIT0 is cleared
                P1IES &= ~BIT0;               // P1IES.BIT0 low/high edge
            }
        } else if (S1pressed == 1) {
            __delay_cycles(20000);
            if (S1pressed == 1) {
                S1pressed = 0;
                P1IFG &= ~BIT0;                // P1IFG.BIT0 is cleared
                P1IES |= BIT0;                 // P1IES.BIT0 hi/low edge
            }
        }
    }
}
