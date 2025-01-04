/*                   CLASS ENCODER Es
 *                    9 January 2023
 *  Program displays the number of left and right motor encoder counts
 *   using microcontroller interrupts for an input distance in cm.
 *   Nominal wheel size (8 cm) used to transform distance to encoder counts.
 *   Program used to find move robot forward for a distance, dist, cm.
 *   Es (= actual distance traveled/encoder calculated distance) can then be calculated
 *   from the actual distance the robot travels.
*/  
#define  FWD     1      
#define  REV     2
#define  CCW     3
#define  CW      4
 
//  encoder variables
volatile long left_cnt  = 0; 
volatile long right_cnt = 0;

int leftINA_pin  = 4;
int leftINB_pin  = 5;
int leftPWM_pin  = 6;
int rightINA_pin = 7;
int rightINB_pin = 8;
int rightPWM_pin = 9; 

int leftDuty;
int rightDuty;

int leftCntDel;          //change in encoder counts
int rightCntDel;
int leftCntPrev;         //previous encoder counts
int rightCntPrev;

float dist;
//float calcDist;
float Cm;              // distance traveled per encoder count (cm/count)

unsigned long countMax;
unsigned long T0;
unsigned long T;

void setup() {
  Serial.begin(9600);
  Serial1.begin(19200);

  InterruptSetup();          // this function sets up the port interrupts and starts the timer interrupt  

//setup motor control pins  
  pinMode(rightINA_pin, OUTPUT);
  pinMode(rightINB_pin, OUTPUT);
  pinMode(rightPWM_pin, OUTPUT);
  pinMode(leftINA_pin, OUTPUT);
  pinMode(leftINB_pin, OUTPUT);
  pinMode(leftPWM_pin, OUTPUT);  

  delay(1000);                   //delay 1 sec to give logomatic time to iinitialize  

//initialize motor speeds to equal values;
  leftDuty  = 40;                    //Slow speed prevents slipping
  rightDuty = 40;
  dist = 400;                        // 4m  run
  Cm = 0.00299199;                  // cm/encoder count
  countMax  = dist/Cm;  
  left_cnt  = 0;
  right_cnt = 0;  
  leftCntPrev    = left_cnt;
  rightCntPrev   = right_cnt;
  T0 = millis();  

  Serial1.println("LtCn   RtCnt   LtDel   RtDel  RtSpeed" );
  Serial1.println("  ");  
}
  
void loop() {
/*  while loop attempts to compensate for different motor speed differences  
    using the encoder counts furnished by interrupts.  The loop is initially
    set up to go straight for countMax counts, keeping left motor speed constant
    and adjusting the right motor speed.
*/
    MotorGo(FWD,leftDuty, rightDuty);
// run for encoder calculated distance of 400 cm    
    while (left_cnt <= countMax)  { 
      T = millis();
// use encoder counts every 100 ms to adjust right motor speed
      if(T >= T0 + 100) {              // Count encoder pulses every 100 ms and adjust motor speeds
        leftCntDel = left_cnt - leftCntPrev;
        rightCntDel = right_cnt - rightCntPrev;        
        leftCntPrev = left_cnt;   
        rightCntPrev = right_cnt;
       
        if(leftCntDel > rightCntDel)
          rightDuty = rightDuty + 1;
        else if (rightCntDel > leftCntDel)
          rightDuty = rightDuty - 1;  

        T0 = millis();
        MotorGo(FWD, leftDuty, rightDuty);
          
//        LogoPrint();     // diagostic print to logomatic    
      }
    }
//   Stop  
    MotorStop();
    delay(500);
    Serial1.println(" Stopped ");    
    delay(500);
    Serial1.print(left_cnt);
    Serial1.write(9);
    Serial1.print(right_cnt); 
    Serial1.write(9);
    Serial1.println(countMax);
    
    while(1) {          //prevent loop from continuing and dump logomatic buffer
      Serial1.println("idle");
      delay(20);
    }
}  
