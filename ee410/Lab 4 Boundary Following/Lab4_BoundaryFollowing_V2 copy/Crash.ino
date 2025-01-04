
/***************************************************************
 * This purpose of CRASH is to act as a releaser for the
 * boundary following behavior
 * 
 * CRASH is TRUE if forward object is detected
 * CRASH is FALSE if forward object is not detected
 * *************************************************************
 */
bool Crash(){ // the infrared is buggy
  bool firstSet;
  bool front;
  RightIRange = IRange(RightIR_pin);
  distanceIRRight = 21.9/(RightIRange-.135); // Voltage to distance in cm
  FrontRange = SonarRange(FrontSonar_pin);
  RightRange = SonarRange(RightSonar_pin); //Distance 
  if (started){
    if(FrontRange < offset+3 ||distanceIRRight <= .8*RightRange){ //checks to see if it still needs to turn
      return true;
    }
    else
    {
      return false;
    }
  }
  if(FrontRange < offset+3 || distanceIRRight <= 1.1*RightRange){ //forward object detected
    return true;
  }
  else{
    return false;
  }
}
