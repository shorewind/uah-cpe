int offsetSensor = 25;

void recognizeLocation(){
  if(recognizeJunction()){
    //Serial.println("Junction");
    Serial1.println("Junction");
  }
  else{
    if(recognizeDoor_Left()){
      //Serial.println("Door");
      Serial1.println("Door on the left");     
    }
    else if(recognizeDoor_Right()){
      //Serial.println("Door");
      Serial1.println("Door on the right");
    }
    else{
      if(recognizeHall()){
        //Serial.println("Hall");
        Serial1.println("Hall");     
      }
      else{
        //Serial.println("Room"); 
        Serial1.println("Room");    
      }
    }
  }
}

bool recognizeHall(){
  //If returns 1, hall
  FrontRange = SonarRange(FrontSonar_pin);
  LeftRange = SonarRange(LeftSonar_pin);
  RightRange = SonarRange(RightSonar_pin);
  RearRange = SonarRange(RearSonar_pin);

  if (FrontRange >= offsetSensor && RearRange >= offsetSensor && RightRange <= offsetSensor && LeftRange <= offsetSensor)
  {
    //Front and back are clear
    return 1;
  }
  else if (RightRange >= offsetSensor && LeftRange >= offsetSensor && FrontRange <= offsetSensor && RearRange <= offsetSensor){
    //Left and Right Clear
    return 1;
  }
  else{
    return 0;
  }
}

bool recognizeDoor_Left(){
  FrontRange = SonarRange(FrontSonar_pin);
  LeftRange = SonarRange(LeftSonar_pin);
  RightRange = SonarRange(RightSonar_pin);
  RearRange = SonarRange(RearSonar_pin);

 
  if (LeftRange >= offsetSensor) // left door
  {
    if(FrontRange >= offsetSensor || RearRange >= offsetSensor)
    {
      Serial.println("Left ");
      Serial1.println("Door Found on Left... ");
      return 1;
    }
    else{
      return 0;
    }
  }
  else if (RightRange >= offsetSensor){
    if(FrontRange >= offsetSensor || RearRange >= offsetSensor)
    {
      Serial.println("Right ");
      Serial1.println("Door Found on Right... ");
      //return 1;
      return 0;
    }
    else{
      return 0;
    }
  }
  return 0;
}

bool recognizeDoor_Right(){
  FrontRange = SonarRange(FrontSonar_pin);
  LeftRange = SonarRange(LeftSonar_pin);
  RightRange = SonarRange(RightSonar_pin);
  RearRange = SonarRange(RearSonar_pin);

 
  if (LeftRange >= offsetSensor) // left door
  {
    if(FrontRange >= offsetSensor || RearRange >= offsetSensor)
    {
      Serial.println("Left ");
      Serial1.println("Door Found on Left... ");
      //return 1;
      return 0;
    }
    else{
      return 0;
    }
  }
  else if (RightRange >= offsetSensor){
    if(FrontRange >= offsetSensor || RearRange >= offsetSensor)
    {
      Serial.println("Right ");
      Serial1.println("Door Found on Right... ");
      return 1;
    }
    else{
      return 0;
    }
  }
  return 0;
}

bool recognizeJunction(){
  FrontRange = SonarRange(FrontSonar_pin);
  LeftRange = SonarRange(LeftSonar_pin);
  RightRange = SonarRange(RightSonar_pin);
  RearRange = SonarRange(RearSonar_pin);
  if(FrontRange >= offsetSensor && RearRange >= offsetSensor && LeftRange >= offsetSensor && RightRange >= offsetSensor)
  {
    Serial1.println("Main Junction Found... ");
    return 1;
  }
  return 0;
}
