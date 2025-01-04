/***************************************************************
 * The purpose of INSIDE is to stop for an interior corner
 * and then turn in place until the path ahead is clear
 * *************************************************************
 */
void Inside(){
  //Sensors to use
  //LeftIRange = IRange(LeftIR_pin);
  //RightIRange = IRange(RightIR_pin);
  //FrontRange = SonarRange(FrontSonar_pin);
  MotorStop();
  //Started turning
  while(Crash() && Wall()){
    started = true;
    MotorGo(CCW, 12, 12);
  }
}
