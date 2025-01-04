void All_Rooms(){
  Room1();
  Room2();
  Room3();
  Room4();
  
}

void Room1(){
    while(1)
  {
    //Step 1:  from starting point move forward until find main junction
    //Serial1.println("At starting point...moving up hallway");
    MotorGo(FWD, leftDuty, rightDuty);
    hallFollow();
    if(recognizeJunction()){
        MotorStop();
        delay(150);
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
  while(abs(angle - 88) > .4){
    angle = IMU();
    MotorGo(CCW, 15, 15);
  }
  MotorStop();

  leftDuty = 43;
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
    if(recognizeDoor_Left()){
        MotorStop();
        break;
      }
    }
  
  //Step 6: Beep that we have reached room 1.
  Serial1.println("Inside room 1...time to beep ");
  tone(buzzer_pin, 1000);
  delay(100);
  noTone(buzzer_pin);
  delay(100);
}

void Room2(){

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
 
  //Step 6: Beep that we have reached room 1.
  Serial1.println("Inside room 1...time to beep ");
  tone(buzzer_pin, 1000);
  delay(100);
  noTone(buzzer_pin);
  delay(100);
  
}

void Room3(){

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
  leftDuty = 43;
  rightDuty = 40;
  delay(100);
  MotorGo(FWD, leftDuty, rightDuty);
  delay(2000);

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


  leftDuty = 42;
  rightDuty = 40;
  //Need to find door on left
  MotorGo(FWD, leftDuty, rightDuty);
  
  angle = IMU();
  while(abs(angle + 95) > .4){
    angle = IMU();
    MotorGo(CCW, 15, 15);
  }
//Correct Angle
//Correct Angle


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
   
  //Step 6: Beep that we have reached room 1.
  Serial1.println("Inside room 1...time to beep ");
  tone(buzzer_pin, 1000);
  delay(100);
  noTone(buzzer_pin);
  delay(100);
  
}

void Room4(){

  //Step 2: at the main junction turn left 90 degrees.
  //Between Junction and Hall
  angle = IMU();
  Serial1.println(" ");
  Serial1.println("At main junction...turning to room 1 hallway");
  Serial1.print("angle:  ");
  Serial1.println(angle);
  while(abs(angle - 94) > .4){
    angle = IMU();
    MotorGo(CW, 15, 15);
  }
  MotorStop();
  leftDuty = 42;
  rightDuty = 40;
  delay(100);
  MotorGo(FWD, leftDuty, rightDuty);

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


  leftDuty = 42;
  rightDuty = 40;
  //Need to find door on left
  MotorGo(FWD, leftDuty, rightDuty);
  
  angle = IMU();
  while(abs(angle) > .4){
    angle = IMU();
    MotorGo(CW, 15, 15);
  }
//Correct Angle
//Correct Angle


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
   
  //Step 6: Beep that we have reached room 1.
  Serial1.println("Inside room 1...time to beep ");
  tone(buzzer_pin, 1000);
  delay(100);
  noTone(buzzer_pin);
  delay(100);
  

  
}
