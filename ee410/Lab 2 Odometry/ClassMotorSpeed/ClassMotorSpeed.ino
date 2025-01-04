/*                     CLASS MotorSpeed
 *                    9 January 2023
 *  Program finds the number of left and right motor encoder counts
 *   for a five second motor run at various duty cycles.
 *   The encoders produce 8400 counts/wheel rev.
 *   For a wheel diameter of 8 cm, the distance traveled is Cm = 0.00299199 cm
 *   times the number of counts
 *   The speed is the distance divided by five seconds.
*/  
#define  FWD     1      
#define  REV     2
#define  CCW     3
#define  CW      4
 
//  encoder variables
volatile long left_cnt = 0; 
volatile long right_cnt = 0;

int leftINA_pin  = 4;
int leftINB_pin  = 5;
int leftPWM_pin  = 6;
int rightINA_pin = 7;
int rightINB_pin = 8;
int rightPWM_pin = 9; 

int leftDuty;
int rightDuty;

float LtSpeed;
float RtSpeed;
float Cm;           //distance traveled/encoder count  (cm/count)

long T0;

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


//initialize motor speeds to equal values;
  leftDuty    = 90;
  rightDuty   = 90; 
  left_cnt    =  0;
  right_cnt   =  0;  
}
  
void loop() {
  T0 = millis();
  MotorGo(FWD, leftDuty, rightDuty);  
  
//  run motors for 5 seconds
  while ((millis()- T0) <= 5000) {
  }

// print time, left and right encoder counts to logomatic
  Serial1.print(millis() - T0);
  Serial1.println("   sec ");
  Serial1.println("   ");
  Serial1.print(left_cnt);
  Serial1.write(9);
  Serial1.print(right_cnt);  
  Serial1.println(  "  L/R counts");
  Serial1.println("  ");
  
//   Stop  
    MotorStop();
    Serial1.println(" Stopped ");    
    delay(500);

//  calculate and print motor speeds to logomatic
    Cm = 0.00299199;                //  cm/encoder count
    LtSpeed = Cm*left_cnt/5;        //divide by 5 for a 5 sec run
    RtSpeed = Cm*right_cnt/5;
    Serial1.print(left_cnt);
    Serial1.write(9);
    Serial1.print(right_cnt);
    Serial1.println("   L/R  counts ");
    Serial1.println("  ");

    Serial1.print(LtSpeed);
    Serial1.write(9);
    Serial1.print(RtSpeed); 
    Serial1.println(" L/R  cm/s ");
    Serial1.println("  ");
    

    while(1) {          //prevent loop from continuing and dump logomatic buffer
      Serial1.println("idle");
      delay(20);
    }
}  
