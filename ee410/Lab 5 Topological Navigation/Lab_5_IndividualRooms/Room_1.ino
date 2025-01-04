/******************************************************************
 * The purpose of ROOM_1 is to design a sequence of navigation
 * of our mock building using landmarks and sensors.
 * 
 * Room 1 Navigation sequence is as follows:
 * S-->H1-->MJ-->H2-->D1-->R1
 * ***************************************************************
 */

void Room_1(){
  while(1)
  {
    //Step 1:  from starting point move forward until find main junction
    //Serial1.println("At starting point...moving up hallway");
    MotorGo(FWD, leftDuty, rightDuty);
    hallFollow();
    if(recognizeJunction())
    {
        MotorStop();
        delay(150);
        break;
    }
  }//end while loop

  //Step 2: at the main junction turn left 90 degrees.
  //Between Junction and Hall
  angle = IMU();
  Serial1.println(" ");
  Serial1.println("At main junction...turning to hallway 2");
  Serial1.print("angle:  ");
  Serial1.println(angle);
  while(abs(angle - 90) > .4)
  {
    angle = IMU();
    MotorGo(CCW, 15, 15);
  }//end while loop
  MotorStop();

  leftDuty = 43;
  rightDuty = 40;
  //Need to find door 
  MotorGo(FWD, leftDuty, rightDuty);
  delay(1250);


  //Step 3:  from main junction facing hallway 2 move to room 1 doorway
  while(1)
  {
    MotorGo(FWD, leftDuty, rightDuty);
    hallFollow();
    //Serial1.println("At hallway 2...moving up hallway");
    if(recognizeDoor_Left())
    {
        MotorStop();
        break;
    }
  }//end while loop
 
  //Step 4: at room 1 doorway turn left 90 degrees.
  angle = IMU();
  while(abs(angle - 180) > .4 && abs(angle + 180) > .4)
  {
    //Serial1.println("At room 1 doorway...turning to room 1 ");
    angle = IMU();
    MotorGo(CCW, 15, 15);
  }//end while loop

  //Step 5: enter room 1.
  T0 = millis();
  T = millis();
  while(T-T0 < 2000)
  {
    T = millis();
    leftDuty = 43;
    rightDuty = 40;
    MotorGo(FWD, leftDuty, rightDuty);
  }//end while loop
  
  MotorStop();
  
  //Step 6: Beep that we have reached room 1.
  Serial1.println("Inside room 1...time to beep ");
  tone(buzzer_pin, 1000);
  delay(100);
  noTone(buzzer_pin);
  delay(100);
  
}//end room 1 navigation
