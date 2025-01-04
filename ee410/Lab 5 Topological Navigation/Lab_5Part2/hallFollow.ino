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
