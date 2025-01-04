/*                     CLASS ENCODER/IMU
 *                        9 January 2023
 *  Program compares IMU measured and Encoder calculated turn angles
 *  
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

int AvgCount;
int nTurns;
int leftDuty;
int rightDuty;

float wheelBase;
float Es;
float Cm;
float CmStar;
float theta;
float encoderAngle;

unsigned long countMax;

void setup() {
  Serial.begin(9600);
  Serial1.begin(19200);

  InitInterrupt();          // this function sets up the port interrupts and starts the timer interrupt  

// Initialize the IMU
if(!bno.begin())  {
      //There was a problem detecting the BNO055 .. check connections
      Serial.print("Ooops, no BNO055 detected ..  Check wiring or I2C address");
      while(1);
  }
  delay(1000);
  
  bno.setExtCrystalUse(true);  

//setup motor control pins  
  pinMode(rightINA_pin, OUTPUT);
  pinMode(rightINB_pin, OUTPUT);
  pinMode(rightPWM_pin, OUTPUT);
  pinMode(leftINA_pin, OUTPUT);
  pinMode(leftINB_pin, OUTPUT);
  pinMode(leftPWM_pin, OUTPUT);  

//initialize motor speeds to equal values;
  leftDuty  = 100;         // slow speeds for turns
  rightDuty = 100;
  encoderAngle =  0;
  
// ********* set turn angle here
  theta = 90;
  nTurns = int((360/theta) + 0.5);

// ********* set actual wheelBase in cm here
  wheelBase = 22.5;   //actual value varies slightly for different robots

//  ******** set actual value of Es here  
  Es = .99475;
  Cm = 0.00299199;
  CmStar = Es*Cm;
  left_cnt  = 0;
  right_cnt = 0;
  AvgCount  = 0;
 
// counts/theta deg = (wheel base/2)*pi/180*N(counts/cm)*theta 
//                  = (pi/180)*(wheelBase/2)*(1/CmStar)*theta
  countMax  = int((0.0087266*wheelBase/CmStar)*theta);    //set count for turn angle of theta in deg 
  delay (500);
}
  
void loop() {
/*  while loop attempts to compensate for motor speed differences  
    using the encoder counts furnished by interrupts.  The loop is initially
    set up to go straight for 12720 counts, keeping left motor speed constant
    and adjusting the right motor speed.
*/
  
//  Make four successive turns
for (int i = 0; i < nTurns; i++) {   
  MotorGo(CW,leftDuty, rightDuty);    // choose turn direction
  while (AvgCount <= countMax) {
    AvgCount = abs((left_cnt - right_cnt)/2);     
  }
 
//   Stop  
    MotorStop();
    delay(250);
        
// Get a new IMU sensor event    
    sensors_event_t event;
    bno.getEvent(&event);  

    encoderAngle += theta;
    Serial1.print(" encoder angle =  "); 
    Serial1.print(encoderAngle); 
    Serial1.write(9);
    Serial1.print(" IMUAngle = ");   
    Serial1.write(9);  
    Serial1.println(event.orientation.x, 0); 
    Serial1.println(" ");

    left_cnt  = 0;
    right_cnt = 0;   
    AvgCount  = 0;
}
    while(1) {          //prevent loop from continuing and dump logomatic buffer
      Serial1.println("idle");
      delay(20);
    }
}  
