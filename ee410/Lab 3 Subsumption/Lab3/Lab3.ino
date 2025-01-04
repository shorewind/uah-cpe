 
//   Red Team Sumation Level 0

#define  FWD     1      
#define  REV     2
#define  CCW     3
#define  CW      4

int leftDuty = 40;
int rightDuty = 44;

bool collision;
bool level;

//  encoder variables
volatile long left_cnt = 0; 
volatile long right_cnt = 0;

const float pi = 3.14159;
const float radToDeg = 180/pi;

// Motor Connections
int leftINA_pin  = 4;
int leftINB_pin  = 5;
int leftPWM_pin  = 6;
int rightINA_pin = 7;
int rightINB_pin = 8;
int rightPWM_pin = 9; 

int FrontSonar_pin    = 38;
int Left45Sonar_pin   = 39;
int LeftSonar_pin     = 40;
int RearSonar_pin     = 41;
int RightSonar_pin    = 42;
int Right45Sonar_pin  = 43; 
int buzzer_pin        = 11;


float FrontRange;
float Left45Range;
float LeftRange;
float RearRange;
float RightRange;
float Right45Range;

float theta, F;
float sensorValues[6]; 
int limit = 4;  // max distance in cm before detecting collision
float wandering;

unsigned long T0; 
unsigned long T;
bool beeped;
float randomDirection;
float oldWander = 100;
float wandered;



void setup()  {
  Serial.begin(9600);
  InterruptSetup(); 
  
//setup motor control pins  
  pinMode(rightINA_pin, OUTPUT);
  pinMode(rightINB_pin, OUTPUT);
  pinMode(rightPWM_pin, OUTPUT);
  pinMode(leftINA_pin, OUTPUT);
  pinMode(leftINB_pin, OUTPUT);
  pinMode(leftPWM_pin, OUTPUT);  
  
  pinMode(buzzer_pin, OUTPUT);
  pinMode(FrontSonar_pin, OUTPUT);
  pinMode(Left45Sonar_pin, OUTPUT);
  pinMode(LeftSonar_pin, OUTPUT);
  pinMode(RearSonar_pin, OUTPUT);
  pinMode(RightSonar_pin, OUTPUT);
  pinMode(Right45Sonar_pin, OUTPUT); 

  leftDuty  = 25; 
  rightDuty = 26;  
  delay(1000);    

  T0 = millis();
  Forward(0);           // Begin stopped
  
  level = 1;
  limit = 30;
  beeped = 0;
  randomDirection = 0;

}

void loop() {
  collision = DetectCollision(sensorValues, limit);
  if (S(level) == 0){ //Level 0
    RunAway();
  }
  else if (S(level) == 1){ //Level 1
    Wander();
    Avoid();
    
  }
  
}
