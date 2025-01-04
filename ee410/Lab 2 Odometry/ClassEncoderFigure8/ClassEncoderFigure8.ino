/*                   Red Team Figure 8
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

float dist;
//float calcDist;
float Cm;              // distance traveled per encoder count (cm/count)

unsigned long countMax;

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
  leftDuty  = 42;                    //Slow speed prevents slipping
  rightDuty = 20;                    //right speed set to 20 to provide a consistant ratio for the turn
  dist = 420;                        // A circle of diameter 75cm has circumfrence of 235cm and based on the speed calculations the distance needed to travel is about 420cm
  Cm = 0.00299199;                  // cm/encoder count
  countMax  = dist/Cm/.99475;       //adjusting distance based on Es
  left_cnt  = 0;
  right_cnt = 0;  
}
  
void loop() {
/*  Main loop has the robot move in a circle in clockwise direction diameter of 75cm then moves in a circle in a counter clockwise direction also of 75cm
*/
 //For the clockwise circle, the left needs to move faster
  MotorGo(FWD, 42, 20); // 
  while (left_cnt <= countMax)  {         
//        LogoPrint();     // diagostic print to logomatic    
      }
    MotorStop();
      
    MotorGo(FWD, 20, 75); // Counter clockwise circle thus the right needs to move faster
    left_cnt = 0;
 
 
//CCW Turn
    while (left_cnt <= countMax*.6825)  {    //Since the left encoder is going about half as fast and about half of what originally     
//        LogoPrint();     // diagostic print to logomatic    
      }
//   Stop  
    MotorStop();
    delay(500);
    
    while(1) {          //prevent loop from continuing and dump logomatic buffer
      Serial1.println("idle");
      delay(20);
    }
}  
