/*                   Collide
 *                     
 *  The purpose of collide is to stop the robot if a forward collision is
 *  imminent.
 */  
 
bool DetectCollision(float *sensorValues, int limit)
{ 

  //------------------------- Perceptual Scheme --------------------------
  FeelForce(sensorValues);


  //-------------------------- Motor Scheme ------------------------------
  if (sensorValues[0] < limit)
   {
    Forward(0);
    if (collision == false){
      tone(buzzer_pin, 1000);
      delay(100);
      noTone(buzzer_pin);
      return true;
    }
    
   }
  else
  {
    return false;
  }
}
