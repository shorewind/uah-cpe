/*------------------------------------------------------------------------------
 * File:        project.c
 * Function:    Cipher tool
 * Description: Toggles between different ciphers via switch press, relative
 *              security indicated by frequency of LED blinking
 * Input:     Characters entered via MobaXterm received via UART
 * Output:    Encrypted text
 * Author:    Esther Shore
 * Date:      August 2023
 *----------------------------------------------------------------------------*/
#include <msp430xG46x.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// ANSI escape codes for text color
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_RESET   "\x1b[0m"

// function prototypes
void UART_setup();
void UART_send_character(char);
void UART_send_string(char* string);
void UART_get_word(char* buffer, int limit);
void caesar_cipher(char* string);
void substitution_cipher(char* string);
void xor_cipher(char* string);
void switch_setup();
void timerB_setup();

unsigned int current_cipher = 0;  // 1: caesar, 2: substitution, 3: xor
unsigned int S1pressed = 0;
unsigned int S2pressed = 0;  // booleans for switch press handling
char input[50];  // buffer for input strings

void main(void) {
    WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
    _EINT();  // enable interrupts
    switch_setup();
    timerB_setup();
    P2DIR |= BIT1;  // LED2 output
    P2SEL |= BIT1 + BIT4 + BIT5;  // set special reg for timer b and tx/rx
    UART_setup();

    // greeting message
    UART_send_string(COLOR_RED);
    UART_send_string("\r\nWelcome to cipher tool!");
    UART_send_string(COLOR_BLUE);
    UART_send_string("\r\n\r\nPress switch 1 to toggle through cipher options\r\nPress switch 2 to enter cipher\r\n");
    UART_send_string(COLOR_RESET);

    while (1) {
        _BIS_SR(LPM0_bits + GIE);
    }
}


void UART_setup() {
    UCA0CTL1 |= UCSWRST;                      // **Put state machine in reset**
    UCA0CTL1 |= UCSSEL_2;                     // SMCLK
    UCA0BR0 = 18;                             // 1MHz / 57600 = 18.2(see User's Guide)
    UCA0BR1 = 0;                              // 1MHz 57600
    UCA0MCTL |= UCBRS_1 + UCBRF_0;            // Modulation UCBRSx=1, UCBRFx=0
    UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
    IE2 |= UCA0RXIE;                         // Enable USCI_A0 RX interrupt
}


void switch_setup() {
    P1IE |= BIT0;
    P1IES |= BIT0;
    P1IFG &= ~BIT0;  // switch 1 setup with interrupt
    P1IE |= BIT1;
    P1IES |= BIT1;
    P1IFG &= ~BIT1;  // switch 2 setup with interrupt
}

void timerB_setup() {
    TB0CCTL0 = OUTMOD_4;  // toggle mode
    TB0CTL = TBSSEL_1 + MC_1;  // ACLK, UP mode
    TB0CCR0 = 32767;  // default 1 sec interval, 0.5 Hz frequency blink
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

void caesarCipher(char* string) {
    int i;
    int shift = 1;
    for (i = 0; string[i] != '\0'; i++) {
        char ch = string[i];
        // for both upper and lower case characters
        if (ch >= 'A' && ch <= 'Z') {
            ch = 'A' + (ch - 'A' + shift) % 26;  // determine new character based on shift
        } else if (ch >= 'a' && ch <= 'z') {
            ch = 'a' + (ch - 'a' + shift) % 26;
        }
        string[i] = ch;
    }
}

void substitutionCipher(char* string) {
    const char key[] = "ZYXWVUTSRQPONMLKJIHGFEDCBA";  // example key, could be any order
    int i;
    for (i = 0; string[i] != '\0'; i++) {
        char ch = string[i];
        if (isalpha(ch)) {
            ch = toupper(ch); //convert char if letter, temp convert to uppercase to handle
            int index = ch - 'A';  // find index of char in the alphabet key
            // find corresponding char in alphabet key
            if (index >= 0 && index < 26) {
                string[i] = isupper(string[i]) ? key[index] : tolower(key[index]);  // back to original case
            } else {
                string[i] = ch;  // not changed if not found
            }
        }
    }
}

void xorCipher(char* string) {
    char xor_key = 'A';  // could be any number or character
    int i;
    for (i = 0; string[i] != '\0'; i++) {
        string[i] = string[i] ^ xor_key; // xor each character
    }
}

#pragma vector = PORT1_VECTOR
__interrupt void Port1_ISR(void) {
    if (P1IFG&BIT0) {
        if (S1pressed == 0) {
            __delay_cycles(20000);  // debounce
            if (S1pressed == 0) {
                S1pressed = 1;
                current_cipher = (current_cipher + 1) % 4;  // get current cipher selection (1-3)
                UART_send_string(COLOR_GREEN);
                if (current_cipher == 1) {
                    UART_send_string("\r\nCaesar Cipher\r\n\r\n");
                    TB0CCR0 = 32767;  // 0.5 Hz
                } else if (current_cipher == 2) {
                    UART_send_string("\r\nSubstitution Cipher\r\n\r\n");
                    TB0CCR0 = 16384;  // 1 Hz
                } else if (current_cipher == 3) {
                    UART_send_string("\r\nXOR Cipher\r\n\r\n");
                    TB0CCR0 = 8192;  // 2 Hz
                }
                UART_send_string(COLOR_RESET);
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
    else if (P1IFG&BIT1) {
        if (S2pressed == 0) {
            __delay_cycles(20000);
            if (S2pressed == 0) {
                S2pressed = 1;
                UART_send_string("\r\nEnter a string to encrypt:\r\n");
                UART_get_word(input, sizeof(input));  // get input from user

                if (current_cipher == 1) {
                    UART_send_string("\r\nOutput caesar string:\r\n");
                    caesarCipher(input);
                } else if (current_cipher == 2) {
                    UART_send_string("\r\nOutput substitution string:\r\n");
                    substitutionCipher(input);
                } else if (current_cipher == 3) {
                    UART_send_string("\r\nOutput xor string:\r\n");
                    xorCipher(input);
                }
                UART_send_string(input);
                UART_send_string(COLOR_BLUE);
                UART_send_string("\r\n\r\nPress switch 1 to toggle through cipher options\r\nPress switch 2 to enter cipher\r\n");
                UART_send_string(COLOR_RESET);
                P1IFG &= ~BIT1;               // P1IFG.BIT1 is cleared
                P1IES &= ~BIT1;               // P1IES.BIT1 low/high edge
            }
        } else if (S2pressed == 1) {
            __delay_cycles(20000);
            if (S2pressed == 1) {
                S2pressed = 0;
                P1IFG &= ~BIT1;                // P1IFG.BIT1 is cleared
                P1IES |= BIT1;                 // P1IES.BIT1 hi/low edge
            }
        }
    }
}
