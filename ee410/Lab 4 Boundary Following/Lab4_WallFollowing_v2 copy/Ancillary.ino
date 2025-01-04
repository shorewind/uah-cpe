
/***************************************************************
 * This code is reused from earlier labs
 * *************************************************************
 */
// INTERRUPT FUNCTIONS 
// 
// As the encoders pulse they cause interrupts which are serviced here
// the functions decide whether the cnt variables should inc or dec.
//
// at the bottom of this page you will find the vector called by the timer interrupt
// this vector, as you can, see calls the function Odometry(left_cnt,right_cnt)
// nothing for you to do here.


// External Interrupt 4 service routine => PIN2 (Right encoder ch A)
ISR(INT4_vect){
  if ((PINK & 0x80) != 0) {     // PK7 Pin A15
    if ((PINE & 0x10) != 0)     // PE4 Pin 2
      right_cnt--;
    else
      right_cnt++;
    } else {
      if ((PINE & 0x10) == 0)   // PE4 Pin 2  
        right_cnt--;
      else
        right_cnt++;
       }
}

// External Interrupt 5 service routine => PIN3 (Left encoder ChA)
ISR(INT5_vect){
  if ((PINB & 0x10) != 0) {
  if ((PINE & 0x20) != 0)
    left_cnt++;
  else
    left_cnt--;
  } else {
    if ((PINE & 0x20) == 0)
      left_cnt++;
    else
      left_cnt--;
    }
}

// Pin change 0-7 interrupt service routine => PIN10 (Left encoder ChB)
ISR(PCINT0_vect){
  if ((PINE & 0x20) != 0) {   // PE5 Pin-3
  if ((PINB & 0x10) != 0) {   // PB4 Pin-10
    left_cnt--;
    } else
    left_cnt++;
    } else {
      if ((PINB & 0x10) == 0) {
        left_cnt--;
      } else
        left_cnt++;
      }
}

// Pin change 16-23 interrupt service routine => PIN-ADC15  (Right encoder ChB)
ISR(PCINT2_vect){
  if ((PINE & 0x10) != 0) {
  if ((PINK & 0x80) != 0)
    right_cnt++;
  else
    right_cnt--;
  } else {
    if ((PINK & 0x80) == 0)
      right_cnt++;
    else
      right_cnt--;
    }
}

// Timer 1 overflow interrupt service routine
ISR(TIMER1_OVF_vect){
  sei();                    // enable interrupts  
//
} 
