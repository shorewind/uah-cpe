/***************************************************************
 * This code is reused from earlier labs
 * *************************************************************
 */
 
void setupInfrared()  {
  pinMode(LeftIR_pin, INPUT);
  pinMode(FrontIR_pin,INPUT);
  pinMode(RightIR_pin,INPUT);
}
  //LeftIRange = IRange(LeftIR_pin);
  //FrontIRange = IRange(FrontIR_pin);
  //RightIRange = IRange(RightIR_pin);

float IRange(int IR_pin)  {
int IRbits;
float IRvolts;
  IRbits = analogRead(IR_pin);
  IRvolts = 5.0*IRbits/1023.0;
  return IRvolts;
}  
