// this function sets up all the port interrupts and begins the timer interrupt

void InterruptSetup(){
  PORTA = 0x00;
  DDRA = 0x00;

  PORTB = 0x00;
  DDRB = 0x00;

  PORTC = 0x00;
  DDRC = 0x00;

  PORTD = 0x00;
  DDRD = 0x00;

  PORTE = 0x00;
  DDRE = 0x00;

  PORTK = 0x00;
  DDRK = 0x00;

  pinMode(13, OUTPUT);

TCCR1A = 0x03;   
TCCR1B = 0x05;    // 0x04: 32 ms;  0x05:  131 ms
TCNT1H = 0x00;
TCNT1L = 0x00;
ICR1H =  0x00;
ICR1L =  0x00;
OCR1AH = 0x00;
OCR1AL = 0x00;
OCR1BH = 0x00;
OCR1BL = 0x00;
OCR1CH = 0x00;
OCR1CL = 0x00;

// External Interrupt(s) initialization
EICRA = 0x00;
EICRB = 0x05;
EIMSK = 0x30;
EIFR = 0x30;
// Interrupt on PCINT
PCICR  = 0x05;
PCIFR  = 0x05;
PCMSK0 = 0x10;
PCMSK1 = 0x00;
PCMSK2 = 0x80;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK1 |= 0x01;
TIFR1 |= 0x01;
// Global enable interrupts
sei();
}
