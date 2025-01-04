void Odometry(long left, long right) {
float delX;
float delY;
float delU; 
float delUleft;
float delUright;
float delTheta;
  
  leftDelta  = (left - lastLeft);
  rightDelta = (right - lastRight);
  lastLeft   = left;
  lastRight  = right; 

  delUleft  = CmStar*leftDelta;
  delUright = CmStar*rightDelta;      
  delU = (delUleft + delUright)/2;

  if(ODO == true) {
    delTheta = (delUright - delUleft)/base;   
    theta += delTheta;
  }
  else {
    theta = IMU()/RadToDeg;  //  Odometry() uses angles in radians; IMU in degrees  
  }
    
  delX  = delU*cos(theta);
  delY  = delU*sin(theta);
  x += delX;
  y += delY;
  U += delU;
}
