/*                     Wander
 *  The purpose of the Wander behavior is to periodically provide   
 *  a random heading direction.
 *  
 *  The new heading is passed to Avoid behavior.  Recommended values of 
 *  5 to 10 seconds are appropriate for the size of the arena.
 */  

void Wander(){
   T = millis();
   
  //------------------------- Perceptual Scheme --------------------------
  
 



  //-------------------------- Motor Scheme ------------------------------
  if(T - T0 >= 5000){ //If 5 seconds have passed change direction
    randomDirection = random(-pi, pi);
    T0 = millis(); //Reset start time
    Serial.println("wander change");
    tone(buzzer_pin, 1000);
    delay(100);
    noTone(buzzer_pin);
    delay(100);
    tone(buzzer_pin, 1000);
    delay(100);
    noTone(buzzer_pin);
  }
  
}
