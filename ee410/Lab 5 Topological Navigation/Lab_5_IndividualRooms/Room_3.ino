/******************************************************************
 * The purpose of ROOM_3 is to design a sequence of navigation
 * of our mock building using landmarks and sensors.
 * 
 * Room 3 Navigation sequence is as follows:
 * S-->H1-->MJ-->H3-->D3-->R3
 * ***************************************************************
 */
 
void Room_3(){
  while(1)
  {
    //Step 1:  from starting point move forward until find main junction
    Serial1.println("At starting point...moving up hallway");
    MotorGo(FWD, leftDuty, rightDuty);
    hallFollow();
    if(recognizeJunction())
    {
        MotorStop();
        delay(200);
        break;
    }
  }//end while loop

  //Step 2: at the main junction turn right 90 degrees.
  //Between Junction and Hall
  angle = IMU();
  Serial1.println(" ");
  Serial1.println("At main junction...turning to hallway 3");
  Serial1.print("angle:  ");
  Serial1.println(angle);
  while(abs(angle + 78) > .4)
  {
    angle = IMU();
    MotorGo(CW, 15, 15);
  }//end while loop
  MotorStop();

  leftDuty = 44;
  rightDuty = 40;
  //Need to find door 
  MotorGo(FWD, leftDuty, rightDuty);
  delay(1250);


  //Step 3:  from main junction facing hallway 3 move to room 3 doorway
  while(1)
  {
    MotorGo(FWD, leftDuty, rightDuty);
    hallFollow();
    Serial1.println("At hallway 3...moving up hallway");
    if(recognizeDoor_Right())
    {
        MotorStop();
        break;
    }
  }//end while loop
 
  //Step 4: at room 1 doorway turn right 90 degrees.
  angle = IMU();
  while(abs(angle - 180) > .4 && abs(angle + 180) > .4)
  {
    Serial1.println("At room 3 doorway...turning to room 3 ");
    angle = IMU();
    MotorGo(CW, 15, 15);
  }//end while loop

  //Step 5: enter room.
  T0 = millis();
  T = millis();
  while(T-T0 < 2000)
  {
    T = millis();
    leftDuty = 44;
    rightDuty = 40;
    MotorGo(FWD, leftDuty, rightDuty);
  }//end while loop
  MotorStop();
  
  //Step 6: Beep that we have reached room 3.
  Serial1.println("Inside room 1...time to beep ");
  tone(buzzer_pin, 1000);
  delay(100);
  noTone(buzzer_pin);
  delay(100);
  
}//end room 3 navigation
