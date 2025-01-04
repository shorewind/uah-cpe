/***************************************************************
 * This code is reused from earlier labs
 * *************************************************************
 */

float IMU() {
float currentAngle;

// Get a new IMU sensor event 
  sensors_event_t event;
  bno.getEvent(&event);  
  currentAngle = event.orientation.x;  
  
// IMU angles measured positive CW from zero to 360
// Odometry angles measured positive CCW from zero to 180 
//  and negative CW zero to 180

  if((currentAngle  > 0) && (currentAngle < 180)) {
    currentAngle = - currentAngle;
  }
  
  else if((currentAngle > 180) && (currentAngle <= 360)) {
    currentAngle = 360 - currentAngle; 
  }
  return currentAngle;
}

void InitializeIMU() {
if(!bno.begin())  {
      //There was a problem detecting the BNO055 .. check connections
      Serial.print("Ooops, no BNO055 detected ..  Check wiring or I2C address");
      while(1);
  }
  delay(1000);
  bno.setExtCrystalUse(true);      
}
