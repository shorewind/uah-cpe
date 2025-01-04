/*                   Circle for the Red Team
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

  leftDuty  = 35;                    //Because of the ratio between the inner and outer motor, the out motor needs a speed of about 1.5 times higher than the inner, the value was adjusted through testing
  rightDuty = 20;                    //right motor set at a constant speed of 20, thus when creating the circle the only adjustment needed was in the left duty cycle
  dist = 478;                        // The circumference is 314cm and the number was raised through testing
  Cm = 0.00299199;                  // cm/encoder count
  countMax  = dist/Cm/.99475;  //Changing distance based on Es value
  left_cnt  = 0;
  right_cnt = 0;  
}
  
void loop() {
/*  This program will turn the robot in a CW direction for a circle with a diamter of 1m
*/
    MotorGo(FWD,leftDuty, rightDuty); // Set duty determined from 
    while (left_cnt <= countMax)  {     //Run for entire circumference of the circle   
//        LogoPrint();     // diagostic print to logomatic    
      }
    }
//   Stop  
    MotorStop();
    delay(500); 
    
    while(1) {          //prevent loop from continuing and dump logomatic buffer
      Serial1.println("idle");
      delay(20);
    }
}  
