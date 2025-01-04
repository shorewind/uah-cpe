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

#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41); //board I2C address

#include <LIDARLite.h>
LIDARLite myLidarLite;

#define SERVOMIN   90 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  450 // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates


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

float offset = 30; //30 cm
float proportionalError;
float differentialError;
float integrableError;
float Error;
float correction;

float proportionalK = .1;
float differentialK = 4;
float integrableK;

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

bool started;

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

int FrontIR_pin = A0;
int LeftIR_pin  = A1;  
int RightIR_pin = A5;

float LeftIRange; 
float FrontIRange;
float RightIRange;

float distanceIRRight;
float estimatedLidarDistance;
float lidarAngle = 4*pi/16;
float D;


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
  setupInfrared();
  setupLidar();



//initialize motor speeds to equal values;
  leftDuty    = 30; // 
  rightDuty   = 30; // keep right constant but change left
  left_cnt    =  0;
  right_cnt   =  0;  
  offset = 30; //30 cm

  running = true; 
  T0 = millis();
  Serial1.println("Distance");

}
  
void loop() {
  while(running){
    started = false;
      if (!Crash() && Wall()){ // Follow wall
         T = millis();
         if (T - T0 >= 100 )
            { 
              rightDuty   = 30; // keep right constant but change left
              T0 = millis();
              Follow();
              Odometry(left_cnt, right_cnt);
            }
          Serial.println("Follow");
        
      }
      else if (Crash() && Wall()){ // Make an inside turn
          Inside();
          Serial.println("Inside");
      }
      else if (!Crash() && !Wall()) //Make outside turn
      {
        Outside();
        Serial.println("Outside");
      }
      else{
        MotorGo(FWD, 10, 10);
       Serial.println("Nothing");
      }
  }
}  
