/***************************************************************
 * Lidar
 * This code is reused from earlier labs
 * *************************************************************
 */
int servonum = 0;
int pulselen;
float servoAng;
float servoAngle;
float angle;

void setupLidar() {
//   configure(int configuration, char lidarliteAddress);  
  myLidarLite.begin(0, true);
  myLidarLite.configure(0);

  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
  delay(10);
  pulselen = Point(lidarAngle*180/3.14159265);  
  pwm.setPWM(servonum, 0, pulselen);
  delay(100);                 // time for servo to reach position
                         
}
//D = myLidarLite.distance(false); get lidarDistance

int Point(float ang) {
int pulsePWM = 0;

  if(ang < 0)   ang = 0.0;
  if(ang > 180) ang = 180.0;

  pulsePWM = int(SERVOMIN + (ang/180)*(SERVOMAX - SERVOMIN));

  return pulsePWM;
}
