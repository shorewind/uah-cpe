/*************************************************** 
 *               Class LIDARPoint
 *               30 November 2021
   Use the Serial Monitor to enter an angle in this format:
        e.g. ang 90
   or whatever angle you wish to point the lidar, between 0 and 180 deg
   then hit enter or click on Send
 ****************************************************/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41); //board I2C address

#include <LIDARLite.h>
LIDARLite myLidarLite;

#define SERVOMIN   90 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  450 // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

String cmd   = "";                   // the Command 
float arg[3] = {0};                  // you can pass up one argument in a serial command
int ArgIndex;                        // index into arguments
String inputString = "";             // a string to hold incoming serial data

byte go;
int servonum = 0;
int pulselen;
float servoAng;
float servoAngle;
float angle;
float D;

void setup() {
  Serial.begin(9600);
  Serial1.begin(19200);                    // Logomatic  

//   configure(int configuration, char lidarliteAddress);  
  myLidarLite.begin(0, true);
  myLidarLite.configure(0);

  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  delay(10);
  go = 0;
  Serial.println("Angle   Distance");
  Serial.println("");
}

void loop() {
  if (go == 1) {
// point the lidar    
    pulselen = Point(servoAng);  
    pwm.setPWM(servonum, 0, pulselen);
    delay(1000);                 // time for servo to reach position
                                 //  before taking a lidar distance measurement

// Find the distance 
      D = myLidarLite.distance(false);            
      Serial.print(servoAng,0);
      Serial.write(9);
      Serial.println(D,1);     
   }

  go = 0;
}

int Point(float ang) {
int pulsePWM = 0;

  if(ang < 0)   ang = 0.0;
  if(ang > 180) ang = 180.0;

  pulsePWM = int(SERVOMIN + (ang/180)*(SERVOMAX - SERVOMIN));

  return pulsePWM;
}
