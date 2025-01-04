void Room_3(){
  while(1)
  {
    //Step 1:  from starting point move forward until find main junction
    //Serial1.println("At starting point...moving up hallway");
    MotorGo(FWD, leftDuty, rightDuty);
    hallFollow();
    if(recognizeJunction()){
        MotorStop();
        delay(200);
        break;
    }
  }

  //Step 2: at the main junction turn left 90 degrees.
  //Between Junction and Hall
  angle = IMU();
  Serial1.println(" ");
  Serial1.println("At main junction...turning to room 1 hallway");
  Serial1.print("angle:  ");
  Serial1.println(angle);
  while(abs(angle + 78) > .4){
    angle = IMU();
    MotorGo(CW, 15, 15);
  }
  MotorStop();

  leftDuty = 44;
  rightDuty = 40;
  //Need to find door on left
  MotorGo(FWD, leftDuty, rightDuty);
  delay(1250);


  //Step 3:  from main junction facing room 1 hallway move to room 1 doorway
  while(1)
  {
    MotorGo(FWD, leftDuty, rightDuty);
    hallFollow();
    //Serial1.println("At room 1 hallway...moving up hallway");
    if(recognizeDoor_Right()){
        MotorStop();
        break;
      }
    }
 
  //Step 4: at room 1 doorway turn right 90 degrees.
  angle = IMU();
  //while(abs(angle - 180) > .4 && abs(angle + 180) > .4){
  while(abs(angle - 180) > .4 && abs(angle + 180) > .4){
    //Serial1.println("At room 1 doorway...turning to room 1 ");
    angle = IMU();
    MotorGo(CW, 15, 15);
  }

  //Step 5: enter room 1.
  T0 = millis();
  T = millis();
  while(T-T0 < 2000)
  {
    T = millis();
    leftDuty = 44;
    rightDuty = 40;
    MotorGo(FWD, leftDuty, rightDuty);
  }
  MotorStop();
  
  //Step 6: Beep that we have reached room 1.
  Serial1.println("Inside room 1...time to beep ");
  tone(buzzer_pin, 1000);
  delay(100);
  noTone(buzzer_pin);
  delay(100);
  
}
