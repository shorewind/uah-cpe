void InitializeVariables() {

  T0 = millis();
  
  left_cnt   = 0;
  right_cnt  = 0; 
  leftDelta  = 0;
  rightDelta = 0;
  lastLeft   = 0;
  lastRight  = 0;
  
  x     = 0.0;
  y     = 0.0;
  theta = 0.0;
  U     = 0.0;  
}

void InitializeSerialPorts() {
  Serial.begin(9600);
  Serial1.begin(19200);  
}

void InitializeIMU() {
if(!bno.begin())  {
      //There was a problem detecting the BNO055 .. check connections
      Serial.print("Ooops, no BNO055 detected ..  Check wiring or I2C address");
      while(1);
  }
  delay(1000);
  bno.setExtCrystalUse(true);      
}

void InitializePinModes() { 
  pinMode(rightINA_pin, OUTPUT);
  pinMode(rightINB_pin, OUTPUT);
  pinMode(rightPWM_pin, OUTPUT);
  pinMode(leftINA_pin , OUTPUT);
  pinMode(leftINB_pin,  OUTPUT);
  pinMode(leftPWM_pin,  OUTPUT);  
}
