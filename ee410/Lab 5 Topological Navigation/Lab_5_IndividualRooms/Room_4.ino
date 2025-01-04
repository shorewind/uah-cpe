/******************************************************************
 * The purpose of ROOM_4 is to design a sequence of navigation
 * of our mock building using landmarks and sensors.
 * 
 * Room 4 Navigation sequence is as follows:
 * S-->H1-->MJ-->H4-->D4-->R4
 * ***************************************************************
 */

void Room_4(){
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

  //Step 2: at the main junction turn right 15 degrees.
  //Between Junction and Hall
  angle = IMU();
  Serial1.println(" ");
  Serial1.println("At main junction...turning to hallway 4");
  Serial1.print("angle:  ");
  Serial1.println(angle);

  //Zig
  if(angle > -2 and angle < -9)
  {
      //need to zig a bit... 
      while(abs(angle + 2) > .4 )
      {
        angle = IMU();
        
        Serial1.print("  ********** ");
        Serial1.print("Inside turn, angle:  ");
        Serial1.println(angle);
    
        Serial1.print("  ********** ");
        Serial1.print("Calculated value:  ");
        Serial1.println(abs(angle + 2));
        
        MotorGo(CW, 15, 15);
      }//end while loop
  }
  MotorStop();

  //slow down motors
  leftDuty = 38;
  rightDuty = 40;

  //Need to find door 
  MotorGo(FWD, leftDuty, rightDuty);
  delay(1250);


  //Step 3:  from main junction facing hallway 4 move to room 4 doorway
  while(1)
  {
    MotorGo(FWD, leftDuty, rightDuty);
    hallFollow();
    //Serial1.println("At hallway 4...moving up hallway");
    if(recognizeDoor_Right())
    {
        MotorStop();
        break;
    }
  }//end while loop
 
  //Step 4: at room 4 doorway turn right 90 degrees.
  angle = IMU();

  Serial1.println(" ");
  Serial1.println("At room 4 doorway...turning ");
  Serial1.print("angle:  ");
  Serial1.println(angle);
  
  while(abs(angle + 30) > 1 )
  {
    //Serial1.println("At room 4 doorway...turning to room 4 ");
    angle = IMU();

    Serial1.print("  ********** ");
    Serial1.print("Inside turn, angle:  ");
    Serial1.println(angle);

    Serial1.print("  ********** ");
    Serial1.print("Calculated value:  ");
    Serial1.println(abs(angle + 30));
    
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
  
  //Step 6: Beep that we have reached room 4.
  Serial1.println("Inside room 4...time to beep ");
  tone(buzzer_pin, 1000);
  delay(100);
  noTone(buzzer_pin);
  delay(100);
 
}//end room 4 navigation
