  

//             Class Sonar
//             30 November 2021

//   Program Pings an Ultrasonic Sensor and returns a distance in cm
//  Arduino pin assignments
int FrontSonar_pin    = 38;
int Left45Sonar_pin   = 39;
int LeftSonar_pin     = 40;
int RearSonar_pin     = 41;
int RightSonar_pin    = 42;
int Right45Sonar_pin  = 43; 

float FrontRange;
float Left45Range;
float LeftRange;
float RearRange;
float RightRange;
float Right45Range;

void setup()  {
  Serial.begin(9600);
  pinMode(FrontSonar_pin, OUTPUT);
  pinMode(Left45Sonar_pin, OUTPUT);
  pinMode(LeftSonar_pin, OUTPUT);
  pinMode(RearSonar_pin, OUTPUT);
  pinMode(RightSonar_pin, OUTPUT);
  pinMode(Right45Sonar_pin, OUTPUT); 

  Serial.println("       Sonar Ranges (cm)  ");
  Serial.println(" ");
}

void loop() {
  FrontRange = SonarRange(FrontSonar_pin);
  Serial.print("           ");
  Serial.println(FrontRange,0); 
  delay(20);

// Comment/uncomment the lines below to ping and print ranges for all the sonar sensors   

  Left45Range = SonarRange(Left45Sonar_pin);
  Serial.print("      ");  
  Serial.print(Left45Range,0); 
  delay(20);

  Right45Range = SonarRange(Right45Sonar_pin);
  Serial.print("        ");
  Serial.println(Right45Range,0); 
  delay(20);   

 LeftRange = SonarRange(LeftSonar_pin);
  Serial.print("   ");  
  Serial.print(LeftRange,0); 
  delay(20);  

  RightRange = SonarRange(RightSonar_pin);
  Serial.print("              ");
  Serial.println(RightRange,0);  
  delay(20); 

  RearRange = SonarRange(RearSonar_pin);
  Serial.print("           ");
  Serial.println(RearRange,0); 
  delay(20); 

  Serial.println(" ");
  Serial.println(" ");    
    
  delay(1000);                        //just to slow down serial monitor scrolling
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
