 /*                       Red Team ZigZag Final
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

int AvgCount;
int nTurns;

int startingLeft;
int startingRight;
int leftDelta;
int rightDelta;
int lastLeft;
int lastRight;

int leftCntDel;          //change in encoder counts
int rightCntDel;
int leftCntPrev;         //previous encoder counts
int rightCntPrev;

float pi = 3.1415926535;
float RadToDeg = 180/pi;
float x;
float y;
float U;
float theta;
float dist;
float IMUAngle;
int thetaNeeded;

//  Cm value depends on which encoder transitions counted
float Cm  = 2.991993e-3;  // cm/cnt
float CmStar;
float Es;
float base;           //wheel base in cm

float thetaOdo;
float delThetaOdo;

unsigned long T0;
unsigned long T;
int countMax;
int turnMax;

void setup() {
  Serial.begin(9600);
  Serial1.begin(19200);

  InitInterrupt();
  InitializeSerialPorts();
  InitializeIMU();
//initialize variables, except for motor speeds
  InitializeVariables();
  InitializePinModes(); 
  
// **********  Enter Es value here
  base = 23;
  Es = .99475;
  CmStar = Es*Cm;
  ODO = false;      //true uses encoders to calc. robot pose angle; false uses IMU
  
  T0 = millis();  
  delay(500); 
}
  
void loop() {
/* The while loop gets the robot to go in a zigzag starting from the bottom right. The zigzag uses the encoder counts to go in a straight line and uses the IMU to 
turn the variety of degrees
*/
  leftDuty = 40; //Sets the duty cycle
  rightDuty = 40;
  left_cnt = 0;
  right_cnt = 0; // Sets the encoder counts to zero

    while (left_cnt <= 150/CmStar)  { //Go straight for 150cm
        T = millis();
        // use encoder counts every 100 ms to adjust right motor speed
        if(T >= T0 + 100) {              // Count encoder pulses every 100 ms and adjust motor speeds
          leftCntDel = left_cnt - leftCntPrev;
          rightCntDel = right_cnt - rightCntPrev;        
          leftCntPrev = left_cnt;   
          rightCntPrev = right_cnt;
         
          if(leftCntDel > rightCntDel)
            rightDuty = rightDuty + 1;
          else if (rightCntDel > leftCntDel)
            rightDuty = rightDuty - 1;     
          T0 = millis();    
          MotorGo(FWD, leftDuty, rightDuty);    
      }
    }

  MotorStop();
  delay(250);
   
  IMUAngle = 0;
  while (abs(IMUAngle) > 225 || abs(IMUAngle) < 2) { // Rotates 135 degrees CCW
    sensors_event_t event; // checks IMUangle
    bno.getEvent(&event);  
    IMUAngle = event.orientation.x;
    MotorGo(CCW, 10, 10);    // turns the robot 
  }
 
  MotorStop(); // turn finished
  delay(250);

    left_cnt = 0; // reset encoder count
    right_cnt = 0;
    while (left_cnt <= 212/CmStar)  {  // goes 212cm straight
        T = millis();
        // use encoder counts every 100 ms to adjust right motor speed
        if(T >= T0 + 100) {              // Count encoder pulses every 100 ms and adjust motor speeds
          leftCntDel = left_cnt - leftCntPrev;
          rightCntDel = right_cnt - rightCntPrev;        
          leftCntPrev = left_cnt;   
          rightCntPrev = right_cnt;
         
          if(leftCntDel > rightCntDel)
            rightDuty = rightDuty + 1;
          else if (rightCntDel > leftCntDel)
            rightDuty = rightDuty - 1;     
          T0 = millis();    
          MotorGo(FWD, leftDuty, rightDuty);    
      }
    }

    MotorStop(); // end of straight line
    delay(250);
 
    while (abs(IMUAngle) > 2) { // turns until it faces the original orientation, 135 degrees CW
      sensors_event_t event; // check the IMU angle
      bno.getEvent(&event);  
      IMUAngle = event.orientation.x;
      MotorGo(CW, 10, 10);    // choose turn direction
    }
    MotorStop(); // done turning
    delay(250);

    left_cnt = 0; // reset encoder counts
    right_cnt = 0;
    while (left_cnt <= 150/CmStar)  { //goes straight for 150cm
        T = millis();
        // use encoder counts every 100 ms to adjust right motor speed
        if(T >= T0 + 100) {              // Count encoder pulses every 100 ms and adjust motor speeds
          leftCntDel = left_cnt - leftCntPrev;
          rightCntDel = right_cnt - rightCntPrev;        
          leftCntPrev = left_cnt;   
          rightCntPrev = right_cnt;
         
          if(leftCntDel > rightCntDel)
            rightDuty = rightDuty + 1;
          else if (rightCntDel > leftCntDel)
            rightDuty = rightDuty - 1;     
          T0 = millis();    
          MotorGo(FWD, leftDuty, rightDuty);    
      }
    }

  MotorStop(); // done with straight line
  delay(250);


  while (IMUAngle < 135 || IMUAngle > 355) { // turns CW 135 degrees
    sensors_event_t event; // check IMU angle
    bno.getEvent(&event);  
    IMUAngle = event.orientation.x;
    MotorGo(CW, 10, 10);    // choose turn direction
  }
    
    MotorStop(); // done turning
    delay(250);


    left_cnt = 0; // reset encoder counts
    right_cnt = 0;
    while (left_cnt <= 212/CmStar)  { 
        T = millis();
        // use encoder counts every 100 ms to adjust right motor speed
        if(T >= T0 + 100) {              // Count encoder pulses every 100 ms and adjust motor speeds
          leftCntDel = left_cnt - leftCntPrev;
          rightCntDel = right_cnt - rightCntPrev;        
          leftCntPrev = left_cnt;   
          rightCntPrev = right_cnt;
         
          if(leftCntDel > rightCntDel)
            rightDuty = rightDuty + 1;
          else if (rightCntDel > leftCntDel)
            rightDuty = rightDuty - 1;     
          T0 = millis();    
          MotorGo(FWD, leftDuty, rightDuty);    
      }
    }
    MotorStop(); // done going straight
    delay(250);

  while (IMUAngle > 2) { // turn CCW 135 degrees 
    sensors_event_t event;
    bno.getEvent(&event);  
    IMUAngle = event.orientation.x;
    MotorGo(CCW, 10, 10);    // choose turn direction
  }
  MotorStop(); // reached end of zigzag

  

//   Stop  
    MotorStop();
    Serial1.println(" Stopped ");    
    delay(500);

    while(1) {          //prevent loop from continuing and dump logomatic buffer
      Serial1.println("idle");
      delay(20);
    }
}  
