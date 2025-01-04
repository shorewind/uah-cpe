/***************************************************************
 * The purpose of OUTSIDE is to detect an exterior corner
 * and move around it in a circle.
 * *************************************************************
 */
void Outside(){
  float R;
  float a;
  float ratio; //L/R
  float wheelBase = 23.5;
  // d = RightRange
  // theta = lidarAngle

  //-------------------- Perception Scheme ------------------------
    RightRange = SonarRange(RightSonar_pin); //Distance in cm

 //--------------------- Motor Scheme ------------------------------   
    a = (offset)*tan(lidarAngle);
    R = a + RightRange + wheelBase/2;
    ratio = (R+wheelBase/2)/(R - wheelBase/2);
    Serial.println(ratio);
    rightDuty = 20;
    leftDuty = 20*ratio+26;
    MotorGo(FWD, leftDuty, rightDuty);  
  while (RightRange > offset-10 && FrontRange > offset)
  {
    RightRange = SonarRange(RightSonar_pin); //Distance in cm
    FrontRange = SonarRange(FrontSonar_pin);
    MotorGo(FWD, leftDuty, rightDuty);  
    Serial.println("Turning");
  }
}
