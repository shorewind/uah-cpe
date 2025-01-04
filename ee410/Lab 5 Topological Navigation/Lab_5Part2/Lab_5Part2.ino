/*                     
 *    Red Team Lab 5   
*/ 

#define  FWD     1      
#define  REV     2
#define  CCW     3
#define  CW      4

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41); //board I2C address

Adafruit_BNO055 bno = Adafruit_BNO055(55);

int leftINA_pin  = 4;
int leftINB_pin  = 5;
int leftPWM_pin  = 6;
int rightINA_pin = 7;
int rightINB_pin = 8;
int rightPWM_pin = 9; 
 

int buzzer_pin        = 11;

float leftDuty;
float rightDuty;

//Sonar
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

//Infrared
int FrontIR_pin = A0;
int LeftIR_pin  = A1;  
int RightIR_pin = A5;

float LeftIRange; 
float FrontIRange;
float RightIRange;

float hallway = 46; //30 cm
float offset;
float pi = 3.1415926535;

//  encoder variables
volatile long left_cnt = 0; 
volatile long right_cnt = 0;

bool start;
float angle;
float T0;
float T;

void setup() {
  Serial.begin(9600);
  Serial1.begin(19200);
  
  setupSonar();
  setupInfrared();
  InitInterrupt();          // this function sets up the port interrupts and starts the timer interrupt  
  InitializeIMU();
 //setup motor control pins  
  pinMode(rightINA_pin, OUTPUT);
  pinMode(rightINB_pin, OUTPUT);
  pinMode(rightPWM_pin, OUTPUT);
  pinMode(leftINA_pin, OUTPUT);
  pinMode(leftINB_pin, OUTPUT);
  pinMode(leftPWM_pin, OUTPUT);  

  leftDuty    = 42; 
  rightDuty   = 40;
  offset = (hallway - 24)/2;
}
  
void loop() {
  //Room_1();
  //Room_4();
  All_Rooms();
  //Serial.println(millis());
  Serial1.println(" ");
  //Serial1.println(millis());
  while(1){
     //Serial.println(millis());
     //Serial1.println(millis());
     delay(10000);
  }
}  
