/*                     CLASS IMUTurnArray
 *                    13 May 2020
 *  Program Rotates Robot from current orientation angle to a new orientation
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

int leftINA_pin  = 4;
int leftINB_pin  = 5;
int leftPWM_pin  = 6;
int rightINA_pin = 7;
int rightINB_pin = 8;
int rightPWM_pin = 9; 
int leftDuty;
int rightDuty;
int dir;

float angleArray[] = {270, 0, 90, 0, 180};
float current_angle;
float angle;

void setup() {
  Serial.begin(9600);
  Serial1.begin(19200);

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
  current_angle  = 0;
  angle = 0;  
  delay (500);
}
  
void loop() {   

for (int i = 0; i < 5; i++) { 

  MotorStop();
  delay(250);  
  
   angle = angleArray[i];
Serial1.print(i);
Serial1.write(9);
Serial1.println(angle);   
//------------------------------------------       
 // Determine which way to turn 
  if (current_angle < angle) {
    if (angle > (current_angle + 180)) {
     dir = CCW;
     angle = angleArray[i];  // + angle_bias;
    }
    else {
      dir = CW;
      angle = angleArray[i];  // - angle_bias;
    }
  }

  if (current_angle > angle) {
    if (current_angle > (angle + 180)) {
      dir = CW;
      angle = angleArray[i];  // - angle_bias;
    }
    else {
      dir = CCW;
      angle = angleArray[i];  // + angle_bias;
    }
  }
//------------------------------------------- 
   if (angle < 0)
    angle += 360;
   if (angle > 360)
    angle -= 360;
      
    Serial1.print(angle);
    Serial1.write(9);
    Serial1.print(current_angle);
    Serial1.write(9);
    Serial1.println(dir);
    Serial1.println(" ");  

    MotorGo(dir, 127, 127);   //Change rotation direction here 
  
  while (abs(angle - current_angle) >= 5) { 
// Get a new IMU sensor event 
    sensors_event_t event;
    bno.getEvent(&event);  
    current_angle = event.orientation.x; 
     
    Serial1.println(current_angle);    
  }
 
//   Stop  
    MotorStop();


// Get a new IMU sensor event    
    sensors_event_t event;
    bno.getEvent(&event);
    current_angle = event.orientation.x;
    Serial1.print(" Stopped ");     
    Serial1.write(9);  
    Serial1.print(current_angle);    
    Serial1.println(" ");  
  }
  
    while(1) {          //prevent loop from continuing and dump logomatic buffer
      Serial1.println("idle");
      delay(20);
    }
}  
