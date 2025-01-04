/*                    Forward
 *  The purpose of feelforce is to create a repulsive force from the
 *  ranging sensors and calculate the net force and theta angle.
 *  
 *  The major perceptual scheme includes FeelForce.
 */  
 
void Forward(int moveStatus)  {
//  moveStatus:   0 - Stop,  1 - Forward
  
  if (moveStatus == 0) {
    MotorStop();   
  }
  else if (moveStatus == 1)   {
    MotorGo(FWD,leftDuty, rightDuty);  
  }
}
