 /*                       Class ODOMETRY 
 *                      8 Febuary 2023 
 *                      *  
 *  The program runs the robot straight for a given number of encoder counts,
 *  performs Odometry calculations, and reports the robot pose (x, y, theta)
 *  using the encoders to calculate distance and either the encoders or the 
 *  IMU to calculate theta.
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

int leftDuty;
int rightDuty;

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
  dist = 400;      //straight line distance in cm
  
// **********  Enter Es value here
  base = 23;
  Es = .99475;
  CmStar = Es*Cm;
  ODO = false;      //true uses encoders to calc. robot pose angle; false uses IMU

  delay(500); 
}
  
void loop() {
/*  while loop compensates for different motor speed differences  
    using the encoder counts furnished by interrupts.  The loop is initially
    set up to go straight, keeping right motor speed constant and 
    adjusting the left motor speed.
*/
  MotorGo(FWD, leftDuty, rightDuty);
      
  while(U < dist) { 
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
  }

//   Stop  
    MotorStop();
    Serial1.println(" Stopped ");    
    delay(500);

    while(1) {          //prevent loop from continuing and dump logomatic buffer
      Serial1.println("idle");
      delay(20);
    }
}  
