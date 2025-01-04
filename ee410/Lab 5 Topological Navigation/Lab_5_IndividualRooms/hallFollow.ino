/******************************************************************
 * The purpose of HALLFOLLOW is to follow a wall at the approximate
 * center point using a minor correction from the right sonar.
 * ***************************************************************
 */
 
void hallFollow(){
  LeftRange = SonarRange(LeftSonar_pin);
  RightRange = SonarRange(RightSonar_pin);
  if(RightRange > offset)
  {
    rightDuty += 3;
  }
  else{
    rightDuty -= 3;
  }
  
}
