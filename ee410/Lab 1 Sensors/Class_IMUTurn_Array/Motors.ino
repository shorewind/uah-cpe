
void MotorGo(byte Dir, int LSpeed, int RSpeed) {
//  driver motor1 = left;  driver motor2 = right
//  left motor:  INA low;  INB high --> forward
// right motor:  INA high; INB low  --> forward
  
int leftSpeed;
int rightSpeed;

Serial1.print(" Motors   ");
Serial1.println(Dir);

  if(Dir == FWD) {
    digitalWrite(rightINA_pin, HIGH);
    digitalWrite(rightINB_pin, LOW);
    digitalWrite(leftINA_pin,  LOW);
    digitalWrite(leftINB_pin,  HIGH);
  }

  else if(Dir == REV) {
    digitalWrite(rightINA_pin, LOW);
    digitalWrite(rightINB_pin, HIGH);
    digitalWrite(leftINA_pin,  HIGH);
    digitalWrite(leftINB_pin,  LOW);
  }

  else if(Dir == CCW) {
    digitalWrite(rightINA_pin, HIGH);
    digitalWrite(rightINB_pin, LOW);
    digitalWrite(leftINA_pin,  HIGH);
    digitalWrite(leftINB_pin,  LOW);
  }

  else if (Dir == CW) {
    digitalWrite(rightINA_pin, LOW);
    digitalWrite(rightINB_pin, HIGH);
    digitalWrite(leftINA_pin,  LOW);
    digitalWrite(leftINB_pin,  HIGH);
  }

// scale speed
  leftSpeed = LSpeed*255/100;
  rightSpeed = RSpeed*255/100;

// start motors
  analogWrite(leftPWM_pin, leftSpeed);
  analogWrite(rightPWM_pin, rightSpeed);
}

void MotorStop() {
  digitalWrite(rightINA_pin, HIGH);   //HIGH = BRAKE;  LOW = COAST
  digitalWrite(rightINB_pin, HIGH);
  digitalWrite(leftINA_pin,  HIGH);
  digitalWrite(leftINB_pin,  HIGH);
  analogWrite(leftPWM_pin,  0);
  analogWrite(rightPWM_pin, 0);  
}
