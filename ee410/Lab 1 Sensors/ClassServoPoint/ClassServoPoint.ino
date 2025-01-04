/*************************************************** 
 *               Class Servo
 *               12 July 2020
   Use the Serial Monitor to enter an angle in this format:
        e.g. ang 90
   or whatever angle you wish to point the lidar, between 0 and 180 deg
   then hit enter or click on Send
 ****************************************************/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41); //board I2C address

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

void setup() {
  Serial.begin(9600);
  Serial.println("Servo test!");

  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  delay(100);
  go = 0;
  Serial.print("  Angle ");
  Serial.println("");
}

void loop() {
  if (go == 1) {
    pulselen = Point(servoAng);  

// Drive servo using setPWM()
    pwm.setPWM(servonum, 0, pulselen);

    Serial.println(servoAng, 0);
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
