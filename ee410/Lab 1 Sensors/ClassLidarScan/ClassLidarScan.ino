//                            Class LidarScan
//                              30 November 2021
// Scans Lidar from zero to 180 degrees in one degree increments
//  and prints distance to the serial monitor

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41); //board I2C address

#include <LIDARLite.h>                
LIDARLite myLidarLite;

/*  SERVO LIMITS
 *   Robot      ServoMin     ServoMax
 *   Red         100          475
 *   White        90          440
 *   Green        90          450
 *   Blue         90          440
 *   Black        80          430
 *   Yellow      110          490
 */

#define SERVOMIN   80 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  430 // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

int servonum = 0;
int pulselen;
float servoAngle;
float D;

void setup() {
  delay(500);
  Serial.begin(9600);                      //Serial Monitor  
  Serial1.begin(19200); 

//   configure(int configuration, char lidarliteAddress);  
  myLidarLite.begin(0, true);
  myLidarLite.configure(0);
    
//   configure(int configuration, char lidarliteAddress);  
  myLidarLite.begin(0, true);
  myLidarLite.configure(0);

  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates  

  delay(10);  
  Serial.println("Angle    Distance");  
}
  
void loop() {
//  point the Lidar to zero degrees   
    pulselen = SERVOMIN;  
    pwm.setPWM(servonum, 0, pulselen);
    delay(1000);                 // time for servo to reach position
                                 //  before taking a lidar distance measurement
// scan to 180 degrees

  for (int pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
    pwm.setPWM(servonum, 0, pulselen);
    servoAngle = Angle(pulselen);
// Find the distance  
    D = myLidarLite.distance(false);  

//  print to monitor with Serial; to logomatic with Serial1    
    Serial.print(servoAngle,1);
    Serial.write(9);
    Serial.println(D,1);
  }
}   

float Angle(int pulseWidth) {
float servoAng = 0;

  servoAng = 180*(float(pulseWidth - SERVOMIN)/float(SERVOMAX - SERVOMIN));

  return servoAng;
}
