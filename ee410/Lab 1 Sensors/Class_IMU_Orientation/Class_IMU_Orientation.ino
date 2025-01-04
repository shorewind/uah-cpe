 //                     Class IMU Orientation
//                     30 November 2021

// Program measures and prints Euler Angles
//  Move robot by hand to demo Euler Angle measurements

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

Adafruit_BNO055 bno = Adafruit_BNO055(55);

void setup() {
Serial.begin(9600);
Serial.println("Orientation Sensor Test");
Serial.println("");

// Initialize the sensor
if(!bno.begin())  {
      //There was a problem detecting the BNO055 .. check connections
      Serial.print("Ooops, no BNO055 detected ..  Check wiring or I2C address");
      while(1);
  }
  delay(1000);
  bno.setExtCrystalUse(true);
  delay(500);
}

void loop() {
// Get a new sensor event
  sensors_event_t event;
  bno.getEvent(&event);

  // Display the floating point data
  Serial.print("Theta: ");
  Serial.println(event.orientation.x,1);
//  Serial.print("\tY: ");
//  Serial.print(event.orientation.y,1);
//  Serial.print("\tZ: ");
//  Serial.print(event.orientation.z,1);
  Serial.println("");

  delay(100);
}
