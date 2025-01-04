/******************************************************************
 * The purpose of RECOGNIZE_LOCATION is to design functions to
 * recognize major landmarks of our mock builing such as junctions,
 * and doorways.
 * ***************************************************************
 */
int offsetSensor = 25;

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
    else
    {
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

  if (RightRange >= offsetSensor)
  {
    if(FrontRange >= offsetSensor || RearRange >= offsetSensor)
    {
      Serial.println("Right ");
      Serial1.println("Door Found on Right... ");
      return 1;
    }
    else
    {
      return 0;
    }
  }
  return 0;
}
