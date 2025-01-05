/*------------------------------------------------------------------------------
 * File:        Lab10_D2.c (CPE 325 Lab10 Demo code)
 * Function:    Interfacing thumbstick (MPS430FG4618)
 * Description: This C program interfaces with a thumbstick sensor that has
 *              x (HORZ) and y (VERT) axis and outputs from 0 to 3V.
 *              The value of x and y axis
 *              is sent as the percentage of power to the UAH Serial App.
 * Clocks:      ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = DCO = default (~1MHz)
 *              An external watch crystal between XIN & XOUT is required for ACLK
 *
 *                         MSP430xG461x
 *                      -------------------
 *                   /|\|              XIN|-
 *                    | |                 | 32kHz
 *                    --|RST          XOUT|-
 *                      |                 |
 *                      |     P2.4/UCA0TXD|------------>
 *                      |                 | 38400 - 8N1
 *                      |     P2.5/UCA0RXD|<------------
 *                      |                 |
 * Input:       Connect thumbstick to the board
 * Output:      Displays % of power in UAH serial app
 * Author:      Micah Harvey
 *------------------------------------------------------------------------------*/

#include <msp430xG46x.h>
#include <math.h>

volatile long int ADCXval, ADCYval, ADCZval;
volatile float Xaccel, Yaccel, Zaccel, Xdeviation;
//volatile float magnitude;

void TimerA_setup(void) {
    TACCR0 = 3277;                      // 3277 / 32768 Hz = 0.1s
    TACTL = TASSEL_1 + MC_1;            // ACLK, up mode
    TACCTL0 = CCIE;                     // Enabled interrupt
}

void ADC_setup(void) {
    int i = 0;

    P6DIR &= ~BIT3+ ~BIT7 + ~BIT5;             // Configure P6.3 and P6.7 as input pins
    P6SEL |= BIT3+ BIT7 + BIT5;               // Configure P6.3 and P6.7 as analog pins
    ADC12CTL0 = ADC12ON + SHT0_6 + MSC; // configure ADC converter
    ADC12CTL1 = SHP + CONSEQ_1;         // Use sample timer, single sequence
    ADC12MCTL0 = INCH_3;                // ADC A3 pin - Stick X-axis
    ADC12MCTL1 = INCH_7;          // ADC A7 pin - Stick Y-axis
    ADC12MCTL2 = INCH_5 + EOS;
                                        // EOS - End of Sequence for Conversions
    ADC12IE |= 0x02;                    // Enable ADC12IFG.1
    for (i = 0; i < 0x3600; i++);       // Delay for reference start-up
    ADC12CTL0 |= ENC;                   // Enable conversions
}

void UART_putCharacter(char c) {
    while(!(IFG2 & UCA0TXIFG));         // Wait for previous character to be sent
    UCA0TXBUF = c;                      // Send byte to the buffer for transmitting
}

void UART_setup(void) {
    P2SEL |= BIT4 + BIT5;               // Set up Rx and Tx bits
    UCA0CTL0 = 0;                       // Set up default RS-232 protocol
    UCA0CTL1 |= BIT0 + UCSSEL_2;        // Disable device, set clock
    UCA0BR0 = 27;                       // 1048576 Hz / 38400
    UCA0BR1 = 0;
    UCA0MCTL = 0x94;
    UCA0CTL1 &= ~BIT0;                  // Start UART device
}

void LED_setup(void) {
    P2DIR |= BIT2 | BIT1;               // Set LED1 and LED2 as output
    P2OUT = 0x00;                   // Clear LED1, LED2 status
}

void sendData(void) {
    int i;
    Xaccel = (ADCXval*3.0/4095 - 1.5) / 0.3;    // Calculate percentage outputs
    Yaccel = (ADCYval*3.0/4095 - 1.5) / 0.3;
    Zaccel = (ADCZval*3.0/4095 - 1.5) / 0.3;    // acceleration (g) = output reading (V) - zero output (V) / sensitivity (V/g)
    Xdeviation = atan(Xaccel / sqrt(pow(Yaccel, 2.0) + pow(Zaccel, 2.0))) * 180.0 / M_PI;
//    magnitude = sqrt(pow(Xaccel, 2.0) + pow(Yaccel, 2.0) + pow(Zaccel, 2.0));

    // Use character pointers to send one byte at a time
    char *xpointer=(char *)&Xaccel;
    char *ypointer=(char *)&Yaccel;
    char *zpointer=(char *)&Zaccel;
    char *devpointer=(char *)&Xdeviation;
//    char *magpointer=(char *)&magnitude;

    UART_putCharacter(0x55);            // Send header
    for(i = 0; i < 4; i++) {            // Send x accel - one byte at a time
        UART_putCharacter(xpointer[i]);
    }
    for(i = 0; i < 4; i++) {            // Send y accel - one byte at a time
        UART_putCharacter(ypointer[i]);
    }
    for(i = 0; i < 4; i++) {            // Send z accel - one byte at a time
        UART_putCharacter(zpointer[i]);
    }
    for(i = 0; i < 4; i++) {            // Send x deviation - one byte at a time
        UART_putCharacter(devpointer[i]);
    }
//    for(i = 0; i < 4; i++) {            // Send x deviation - one byte at a time
//        UART_putCharacter(magpointer[i]);
//    }
}

void main(void) {
    WDTCTL = WDTPW +WDTHOLD;            // Stop WDT
    TimerA_setup();                     // Setup timer to send ADC data
    ADC_setup();                        // Setup ADC
    UART_setup();                       // Setup UART for RS-232
    LED_setup();
    _EINT();

    while (1){
        ADC12CTL0 |= ADC12SC;               // Start conversions
        if (Xdeviation > 15.0) {
            P2OUT |= BIT2;
            P2OUT &= ~BIT1;
        } else if (Xdeviation < -15.0) {
            P2OUT |= BIT1;
            P2OUT &= ~BIT2;
        } else {
            P2OUT &= ~BIT2;
            P2OUT &= ~BIT1;
        }
        __bis_SR_register(LPM0_bits + GIE); // Enter LPM0
    }
}

#pragma vector = ADC12_VECTOR
__interrupt void ADC12ISR(void) {
    ADCXval = ADC12MEM0;                  // Move results, IFG is cleared
    ADCYval = ADC12MEM1;
    ADCZval = ADC12MEM2;
    __bic_SR_register_on_exit(LPM0_bits); // Exit LPM0
}

#pragma vector = TIMERA0_VECTOR
__interrupt void timerA_isr() {
    sendData();                           // Send data to serial app
    __bic_SR_register_on_exit(LPM0_bits); // Exit LPM0
}
