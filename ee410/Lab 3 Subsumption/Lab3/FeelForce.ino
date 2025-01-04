/*                    FeelForce
 *  The purpose of feelforce is to create a repulsive force from the
 *  ranging sensors and calculate the net force and theta angle.
 *  
 *  The major perceptual scheme includes FeelForce
 */  
 
void FeelForce(float *sensorValues){
    //FrontSonar_pin, Left45Sonar_pin, Right45Sonar_pin, LeftSonar_pin, RightSonar_pin, RearRange
  float F1, F2, F3, F4, F5, F6;
  float k = 10000;
  float Fx, Fy;
  float pi = 3.1415926535;

  Ranging(sensorValues);
  
  F1 = -k/(sensorValues[0]*sensorValues[0]);
  F2 = -k/(sensorValues[1]*sensorValues[1]);
  F3 = -k/(sensorValues[2]*sensorValues[2]);
  F4 = -k/(sensorValues[3]*sensorValues[3]);
  F5 = -k/(sensorValues[4]*sensorValues[4]);
  F6 = -k/(sensorValues[5]*sensorValues[5]);
  float radtodegrees = pi/180;

  
  Fx = F1*cos(0) + F2*cos(-45*radtodegrees) + F3*cos(45*radtodegrees) + F4*cos(-90*radtodegrees) + F5*cos(90*radtodegrees) + F6*cos(180*radtodegrees);
  Fy = F1*sin(0) + F2*sin(-45*radtodegrees) + F3*sin(45*radtodegrees) + F4*sin(-90*radtodegrees) + F5*sin(90*radtodegrees) + F6*sin(180*radtodegrees);
  F = sqrt(Fx*Fx +Fy*Fy);
  theta = atan2(Fy, Fx);
  

}
