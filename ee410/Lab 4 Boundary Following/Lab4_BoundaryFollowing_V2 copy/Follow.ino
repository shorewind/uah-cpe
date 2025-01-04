/***************************************************************
 * The purpose of FOLLOW is to follow a wall at a desired set
 * point using a PD feedback control.
 * *************************************************************
 */

void Follow()
{
    //declare local variables
    float VWS, correctionP, correctionD, previousError;

 //-------------------- Perception Scheme ------------------------
      RightRange = SonarRange(RightSonar_pin);
      //Serial1.println("--------------");
      //Serial1.print("Distance:  ");
      //Serial1.println(RightRange);

 //--------------------- Motor Scheme ------------------------------

      //Step 1: Calculate the difference between current location and desired set point
            previousError = Error;
            //Serial1.print("Previous Error:  ");
            //Serial1.println(previousError);
      
            Error = offset - RightRange;
            //Serial1.print("New Error calc:  ");
            //Serial1.println(Error);
            
      //Step 2:  Use the value to calculate the PD Correction
            correctionP = Error*proportionalK; 
            //Serial1.print("CorrectionP:  ");
            //Serial1.println(correctionP);
            
            //correctionD = (Error - previousError) / deltaT * differentialK;
            correctionD = (Error - previousError) * differentialK; //we don't need deltaT b/c running every 100 ms
            //Serial1.print("CorrectionD:  ");
            //Serial1.println(correctionD);
            
            //correction = correctionP; // just P term to determine best constant
            correction = -(correctionP + correctionD); // PD correction
            //Serial1.print("Correction:  ");
            //Serial1.println(correction);

      //Step 3:  Use the PD correction to calcualte the adjustment need to the variable wheel speed (VWS)
            //VWS = 40 - correction;
            VWS = 30 + 8 *correction;  // multiply correction by scalar 10
            //Serial1.print("VWS:  ");
            //Serial1.println(VWS);
            
      //Step 4:  Implement the calculated adjustment to the left duty motor
            if(VWS >= 20 && VWS <= 40)
            {
              //good range...go find the wall and follow 
              //Serial1.print("good range...set left duty to VWS: ");
              //Serial1.println(VWS);
                 
              leftDuty = VWS;
              MotorGo(FWD, leftDuty, rightDuty); 
            }
            else if(VWS < 20)
            {
              leftDuty = 20;
              //Serial1.print("reset left duty to 30: ");
              //Serial1.println(leftDuty);
              MotorGo(FWD, leftDuty, rightDuty); 
            }
            else 
            {
              leftDuty = 40;
              //Serial1.print("reset left duty to 50: ");
              //Serial1.println(leftDuty);
              MotorGo(FWD, leftDuty, rightDuty); 
            }
 }
