/*                     Avoid
 *  The purpose of the Avoid behavior is to combine the   
 *  repulsive and random heading directions to veer around
 *  obstacles while moving in the Wander.
 */  


void Avoid(){
  FeelForce(sensorValues);
  
  if(oldWander != randomDirection)
  {
    delay(100);
    FeelForce(sensorValues);
    Turn(randomDirection, 1);
    Forward(0);
    oldWander = randomDirection;
    FeelForce(sensorValues);
    Forward(0);
  }
  collision = DetectCollision(sensorValues, limit);
  if(collision){
      if(theta > 0)
      {
        Turn(6*pi/16+.1, 1);
      }
      else{
        Turn(-6*pi/16-.1, 1);        
      }
      FeelForce(sensorValues);
    }
  if ((F <= 7.5)) {       // an object < 20 cm (~8")
    Forward(1);
    return; 
  }
  else{
    Turn(theta*theta*theta/25 , 1);
  }
  
}
