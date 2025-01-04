 /*                       Red Team Square with Encoders
*/  
#define  FWD     1      
#define  REV     2
#define  CCW     3
#define  CW      4

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

Adafruit_BNO055 bno = Adafruit_BNO055(55);

//  encoder variables
volatile long left_cnt; 
volatile long right_cnt;

bool ODO;

int leftINA_pin  = 4;
int leftINB_pin  = 5;
int leftPWM_pin  = 6;
int rightINA_pin = 7;
int rightINB_pin = 8;
int rightPWM_pin = 9; 

int leftDuty = 0;
int rightDuty = 0;

int leftDelta;
int rightDelta;
int lastLeft;
int lastRight;

float pi = 3.1415926535;
float RadToDeg = 180/pi;
float x;
float y;
float U;
float theta;
float dist;

//  Cm value depends on which encoder transitions counted
float Cm  = 2.991993e-3;  // cm/cnt
float CmStar;
float Es;
float base;           //wheel base in cm

float thetaOdo;
float delThetaOdo;

unsigned long T0;
unsigned long T;

void setup() {
  Serial.begin(9600);
  Serial1.begin(19200);

  InterruptSetup();
  InitializeSerialPorts();
  InitializeIMU();
//initialize variables, except for motor speeds
  InitializeVariables();
  InitializePinModes(); 

//initialize motor speeds to equal values;
  leftDuty  = 40;
  rightDuty = 40;
  dist = 100;      //straight line distance in cm
  
// **********  Enter Es value here
  base = 23;
  Es = .99475;
  CmStar = Es*Cm;
  ODO = true;      //true uses encoders to calc. robot pose angle; false uses IMU

  delay(500); 
}
  
void loop() {
/*  This program will use the encoders to estimate the distance and turns for a 1 meter by 1 meter square
*/
  MotorGo(FWD, leftDuty, rightDuty);
  while(x < dist) { //Go straight until the robot has moved 100 cm in the x direction
    T = millis();

    if(T >= T0 + 100) {                   // Count encoder pulses every 100 ms 
      if(leftDelta > rightDelta)
        leftDuty = leftDuty - 1;
      else if (leftDelta < rightDelta)
        leftDuty = leftDuty + 1;           
        
      MotorGo(FWD, leftDuty, rightDuty);  //adjust motor speed
    
      Odometry(left_cnt, right_cnt); // get location output
      LogoPrint(); 
      T0 = millis();    
    }
      Odometry(left_cnt, right_cnt); // check the encoder count
  }
  
  MotorStop();
  delay(250);
  
  Odometry(left_cnt, right_cnt);
  while (abs(theta*RadToDeg) <= 90) { // turn 90 degrees CW
    Odometry(left_cnt, right_cnt);
    MotorGo(CW, 15, 15);    // choose turn direction
  }

 MotorStop();
  delay(250);

    while(abs(y) < dist) { //Go until y has a value of 100cm
    T = millis();

    if(T >= T0 + 100) {                   // Count encoder pulses every 100 ms 
      if(leftDelta > rightDelta)
        leftDuty = leftDuty - 1;
      else if (leftDelta < rightDelta)
        leftDuty = leftDuty + 1;           
        
      MotorGo(FWD, leftDuty, rightDuty);  //adjust motor speed
    
      Odometry(left_cnt, right_cnt);
      LogoPrint(); 
      T0 = millis();    
    }
      Odometry(left_cnt, right_cnt);
  }
  MotorStop(); // done going straight
  delay(250);
  
  while (abs(theta*RadToDeg) <= 180) { // turn 90 degrees CW
    Odometry(left_cnt, right_cnt); 
    MotorGo(CW, 15, 15);    // choose turn direction
  }

  MotorStop(); // done turning
  delay(250);

    while(abs(x) > 2) {   //Go until x is about 0
    T = millis();

    if(T >= T0 + 100) {                   // Count encoder pulses every 100 ms 
      if(leftDelta > rightDelta)
        leftDuty = leftDuty - 1;
      else if (leftDelta < rightDelta)
        leftDuty = leftDuty + 1;           
        
      MotorGo(FWD, leftDuty, rightDuty);  //adjust motor speed
    
      Odometry(left_cnt, right_cnt); // check location
      LogoPrint();  //print location
      T0 = millis();    
    }
      Odometry(left_cnt, right_cnt); // check the encoder measurement

  }
  
  MotorStop(); // done going straight
  delay(250);
  
  Odometry(left_cnt, right_cnt); // turn 90 degrees CW
  while (abs(theta*RadToDeg) <= 270) {
    Odometry(left_cnt, right_cnt);
    MotorGo(CW, 15, 15);    // choose turn direction
  }

  MotorStop(); // done turning
  delay(250);

    while(abs(y) > 2) {  //Go until y is about zero
    T = millis();

    if(T >= T0 + 100) {                   // Count encoder pulses every 100 ms 
      if(leftDelta > rightDelta)
        leftDuty = leftDuty - 1;
      else if (leftDelta < rightDelta)
        leftDuty = leftDuty + 1;              
      MotorGo(FWD, leftDuty, rightDuty);  //adjust motor speed
    
      Odometry(left_cnt, right_cnt); // check location
      LogoPrint();  //print location
      T0 = millis();    
    }
     Odometry(left_cnt, right_cnt); // check location

  }
  MotorStop(); // done going stright
  delay(250);
  
  Odometry(left_cnt, right_cnt);
  while (abs(theta*RadToDeg) < 360 && abs(theta*RadToDeg) > 1) { // turn until the direction returns to start
    Odometry(left_cnt, right_cnt);
    MotorGo(CW, 15, 15);    // choose turn direction
  }
  MotorStop(); // done turning
  delay(250);
 
   Odometry(left_cnt, right_cnt) //Check location and print
   LogoPrint(); 
 
//   Stop  
    MotorStop(); // Done with square
    Serial1.println(" Stopped ");    
    delay(500);

    while(1) {          //prevent loop from continuing and dump logomatic buffer
      Serial1.println("idle");
      delay(20);
    }
}  
