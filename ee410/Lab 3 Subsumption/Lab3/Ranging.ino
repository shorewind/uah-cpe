 /*                    Ranging
 * The ranging function takes reading from the sonar sensors
 * and converts it to distance in centimeters
 * 
 * Ranging provides sensor input to the perceptual schemes
 * Collide and FeelForce.
 */  
 
void Ranging(float *sensorValues){
  //FrontSonar_pin, Left45Sonar_pin, Right45Sonar_pin, LeftSonar_pin, RightSonar_pin, RearRange
  sensorValues[0] = SonarRange(FrontSonar_pin);
  sensorValues[1] = SonarRange(Left45Sonar_pin);
  sensorValues[2] = SonarRange(Right45Sonar_pin);
  sensorValues[3] = SonarRange(LeftSonar_pin);
  sensorValues[4] = SonarRange(RightSonar_pin);
  sensorValues[5] = SonarRange(RearSonar_pin);
}

float SonarRange(int sonar_pin) {
  float echo;
  float range;
  pulseOut(sonar_pin);                      //sends out a ultrasonic pulse
  pinMode(sonar_pin, INPUT);
  echo = pulseIn (sonar_pin, HIGH);         //times the return pulse
  range = echo/58.0;                       //converts round trip pulse time to distance
  delay(50);  
  return range;
}

//pings the ultrasonic sensor
void pulseOut(int pin) {
  pinMode(pin, OUTPUT);  
  digitalWrite(pin, HIGH);
  delayMicroseconds(15);
  digitalWrite(pin, LOW);
}
