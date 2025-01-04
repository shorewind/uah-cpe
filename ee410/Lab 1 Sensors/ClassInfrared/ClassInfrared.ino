//                      Class Infrared
//                      30 November 2021

// Programs reads Infrared sensor; returns signal level in volts
// Arduino pin assignments
int FrontIR_pin = A0;
int LeftIR_pin  = A1;  
int RightIR_pin = A5;

float LeftIRange; 
float FrontIRange;
float RightIRange;

void setup()  {
  delay(1000);
  Serial.begin(9600);
  pinMode(LeftIR_pin, INPUT);
  pinMode(FrontIR_pin,INPUT);
  pinMode(RightIR_pin,INPUT);
}

void loop() {

  for(int i = 0; i<100; i++) {
  LeftIRange = IRange(LeftIR_pin);
  Serial.print("LeftIRvolts =  ");
  Serial.println(LeftIRange);

  FrontIRange = IRange(FrontIR_pin);
  Serial.print("FrontIRvolts =  ");
  Serial.println(FrontIRange);   

  RightIRange = IRange(RightIR_pin);
  Serial.print("RightIRvolts =  ");
  Serial.println(RightIRange);
  Serial.println("  ");

  delay(35);   
  } 
}

float IRange(int IR_pin)  {
int IRbits;
float IRvolts;
  IRbits = analogRead(IR_pin);
  IRvolts = 5.0*IRbits/1023.0;
  return IRvolts;
}  
