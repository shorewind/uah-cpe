 /*                       Red Team Square with IMU readings
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
  ODO = false;      //true uses encoders to calc. robot pose angle; false uses IMU

  delay(500); 
}
  
void loop() {
/*  The program will use IMU reading to create a square of 1m side length
*/
  MotorGo(FWD, leftDuty, rightDuty);
      
  while(x < dist) { 
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
  
  MotorStop();
  delay(250);
  
  Odometry(left_cnt, right_cnt);
  while (abs(theta*RadToDeg) <= 90) {
    Odometry(left_cnt, right_cnt);
    LogoPrint();  
    MotorGo(CW, 15, 15);    // choose turn direction
  }

  MotorStop();
  delay(250);

    while(abs(y) < dist) { 
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
    MotorStop();
  delay(250);
  
  Odometry(left_cnt, right_cnt);
  while (abs(theta*RadToDeg) <= 178) {
    Odometry(left_cnt, right_cnt);
    LogoPrint();  
    MotorGo(CW, 15, 15);    // choose turn direction
  }

  MotorStop();
  delay(250);

    while(abs(x) > 3) { 
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
  
  MotorStop();
  delay(250);
  
  Odometry(left_cnt, right_cnt);
  while (90 < theta*RadToDeg ) {
    Odometry(left_cnt, right_cnt);
    LogoPrint();  
    MotorGo(CW, 15, 15);    // choose turn direction
  }

  MotorStop();
  delay(250);

    while(abs(y) > 3) { 
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
  MotorStop();
  delay(250);
  
  Odometry(left_cnt, right_cnt);
  while (abs(theta*RadToDeg) > 2) {
    Odometry(left_cnt, right_cnt);
    LogoPrint();  
    MotorGo(CW, 15, 15);    // choose turn direction
  }
  MotorStop();
  delay(250);

  
  

//   Stop  
    MotorStop();
    Serial1.println(" Stopped ");    
    delay(500);

    while(1) {          //prevent loop from continuing and dump logomatic buffer
      Serial1.println("idle");
      delay(20);
    }
}  
