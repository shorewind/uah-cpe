/*                   RunAway
 *                     
 *  The purpose of Run Away is to turn the robot and move away 
 *  for about 1 sec.  
 *  
 *  At level 0:  Run Away takes a repulsive vector from feelforce and
 *  if the magnitude exceeds a threshold (and collision flag is false) it
 *  turns the robot appox 180 degrees and move away for approximately 1 sec.
 *  
 *  At Level 1:  Run Away takes a repulsive vector from feelforce and
 *  if the magnitude exceeds a threshold (and collision flag is false), sends 
 *  the angle and magnitude to turn and forward.
 */  
 
void RunAway() {

//------------------------- Perceptual Scheme ---------------------------
  FeelForce(sensorValues);  
  collision = DetectCollision(sensorValues, limit);
  if ((F <= 20) && (collision == false)) {       // an object < 20 cm (~8")
    return; 
  }
//----------------------------- Motor Scheme ----------------------------
    Turn(theta, 1);     // turn AND go forward
    Serial.println("Turning");
    delay(1000);          // for 3/4 second
    Turn(0,0);            // stop    
}
