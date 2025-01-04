/***************************************************************
 * This purpose of WALL is to act as a releaser for the
 * boundary following behavior
 * 
 * WALL is TRUE if side wall is detected
 * WALL is FALSE if side wall is not detected
 * *************************************************************
 */
bool Wall(){
  RightRange = SonarRange(RightSonar_pin); //Distance in cm
  D = myLidarLite.distance(false); //get Lidar reading
  estimatedLidarDistance = RightRange/cos(lidarAngle);
  if(D >= estimatedLidarDistance+30) // no wall // plus sixteen bevause lidar not reaing correctly
  {
    return false;
  }
  else{
    return true;
  }
}
