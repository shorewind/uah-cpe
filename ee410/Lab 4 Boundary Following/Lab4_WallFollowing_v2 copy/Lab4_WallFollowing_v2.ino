/*                     
 *    Red Team Lab 4 - Wall Following               
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
volatile long left_cnt = 0; 
volatile long right_cnt = 0;

int leftINA_pin  = 4;
int leftINB_pin  = 5;
int leftPWM_pin  = 6;
int rightINA_pin = 7;
int rightINB_pin = 8;
int rightPWM_pin = 9; 

float FrontRange;
float Left45Range;
float LeftRange;
float RearRange;
float RightRange;
float Right45Range;

float leftDuty;
float rightDuty;
float offset = 30; //30 cm desired set point from the wall
float Error; //distance error between robot current positon and desired set point
float correction; //calculated PD correction value
float proportionalK = .1; //.1 best-fit constant
float differentialK = 4;  //4 best-fit constant
float leftSpeed;

float delX;
float delY;
float delU; 

int leftDelta;
int rightDelta;
int lastLeft;
int lastRight;

float xChange;
float yChange;

float pi = 3.1415926535;
float RadToDeg = 180/pi;
float x;
float y;
float U;
float theta = 0;
float dist;

float leftWheelSpeed;
float rightWheelSpeed;


//  Cm value depends on which encoder transitions counted
float Cm  = 2.991993e-3;  // cm/cnt
float Es =  .99475;;
float base = 23;           //wheel base in cm
float CmStar = Es*Cm;;
float radius = 4;
float deltaT = 100; //.1second
float T0;
float T;

bool running = false;

void setup() {
  Serial.begin(9600);
  Serial1.begin(19200);

 InitInterrupt();          // this function sets up the port interrupts and starts the timer interrupt  
 
//setup motor control pins  
  pinMode(rightINA_pin, OUTPUT);
  pinMode(rightINB_pin, OUTPUT);
  pinMode(rightPWM_pin, OUTPUT);
  pinMode(leftINA_pin, OUTPUT);
  pinMode(leftINB_pin, OUTPUT);
  pinMode(leftPWM_pin, OUTPUT);  
  setupSonar();


//initialize motor speeds to equal values;
  leftDuty    = 40; // 
  rightDuty   = 40; // keep right constant but change left
  left_cnt    =  0;
  right_cnt   =  0;  
  running = true; 
  T0 = millis();
  //Serial1.println("Distance");

}
  
void loop() {
  MotorGo(FWD, leftDuty, rightDuty);  
  
  while(running){
      T = millis();
      if (T - T0 >= 100 )
      {
        T0 = millis();
        Serial1.println(" ");
        Serial1.print(T0);
        Follow();
        Odometry(left_cnt, right_cnt);
        Serial1.print("  ,  ");
        LogoPrint();
      }
      if(U > 1000){
        MotorStop();
        running = false;
      }
  }
  MotorStop();
}  
