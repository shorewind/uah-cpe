void setupSonar()  {
  pinMode(FrontSonar_pin, OUTPUT);
  pinMode(Left45Sonar_pin, OUTPUT);
  pinMode(LeftSonar_pin, OUTPUT);
  pinMode(RearSonar_pin, OUTPUT);
  pinMode(RightSonar_pin, OUTPUT);
  pinMode(Right45Sonar_pin, OUTPUT); 
}

//  FrontRange = SonarRange(FrontSonar_pin);
//  Left45Range = SonarRange(Left45Sonar_pin);
//  Right45Range = SonarRange(Right45Sonar_pin);
//  LeftRange = SonarRange(LeftSonar_pin);
//  RightRange = SonarRange(RightSonar_pin);
//  RearRange = SonarRange(RearSonar_pin);


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
