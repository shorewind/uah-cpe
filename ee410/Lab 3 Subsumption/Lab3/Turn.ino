/*                    Turn
 *  The purpose of Turn functions is to use angles from 
 *  RunAway or Avoid to orinet the robot away from obstacles
 *  Turn also sends either a stop or go parameter to Forward.
 */  
 
void Turn(float turnAngle, bool moveForward) {
//  with wheel base of 226 mm and wheel diameter of 80 mm
// turning about one wheel, there are 1884 encoder counts/rad
// moveForward = 1 then 0 in RunAway, = 1 in Avoid
  

  if(moveForward == 0) {           // Stop
    Forward(0);        
    return;
  }
  else {
    if(turnAngle != 0) {          
      if (turnAngle > 2*pi)       //turn right or left <= pi deg.
        turnAngle -= 2*pi;
      if (turnAngle < -2*pi)
        turnAngle += 2*pi;

      right_cnt = 0;
      left_cnt  = 0;

//  positive angles, turn CW
      if((turnAngle >= 0) && (turnAngle <= pi))  {
        MotorGo(CW,20,20);
    
        while(left_cnt <= 3600*turnAngle) {
        }
//   Turn complete, Stop        
        Forward(0);
      }

// negative angles, turn CCW
      else {
        turnAngle = -turnAngle;         
        MotorGo(CCW, 20,20);    
        
        while(right_cnt <= 3600*turnAngle) {
        }
        Forward(0);
      }
    }
//    move forward 
    Forward(1);                  
  }
}
