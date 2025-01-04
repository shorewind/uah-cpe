/***************************************************************
 * Class Sonar
 * This code is reused from earlier labs
 * We are using the range function
 * *************************************************************
 */
int FrontSonar_pin    = 38;
int Left45Sonar_pin   = 39;
int LeftSonar_pin     = 40;
int RearSonar_pin     = 41;
int RightSonar_pin    = 42;
int Right45Sonar_pin  = 43; 

void setupSonar()  {
  pinMode(FrontSonar_pin, OUTPUT);
  pinMode(Left45Sonar_pin, OUTPUT);
  pinMode(LeftSonar_pin, OUTPUT);
  pinMode(RearSonar_pin, OUTPUT);
  pinMode(RightSonar_pin, OUTPUT);
  pinMode(Right45Sonar_pin, OUTPUT); 
}

void getSonar() {
  FrontRange = SonarRange(FrontSonar_pin);
  Left45Range = SonarRange(Left45Sonar_pin);
  Right45Range = SonarRange(Right45Sonar_pin);
  LeftRange = SonarRange(LeftSonar_pin);
  RightRange = SonarRange(RightSonar_pin);
  RearRange = SonarRange(RearSonar_pin);
}

//  
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
