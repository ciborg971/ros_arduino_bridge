/***************************************************************
   Motor driver definitions
   
   Add a "#elif defined" block to this file to include support
   for a particular motor driver.  Then add the appropriate
   #define near the top of the main ROSArduinoBridge.ino file.
   
   *************************************************************/

#ifdef USE_BASE
   
#ifdef POLOLU_VNH5019
  /* Include the Pololu library */
  #include "DualVNH5019MotorShield.h"

  /* Create the motor driver object */
  DualVNH5019MotorShield drive;
  
  /* Wrap the motor driver initialization */
  void initMotorController() {
    drive.init();
  }

  /* Wrap the drive motor set speed function */
  void setMotorSpeed(int i, int spd) {
    if (i == LEFT) drive.setM1Speed(spd);
    else drive.setM2Speed(spd);
  }

  // A convenience function for setting both motor speeds
  void setMotorSpeeds(int leftSpeed, int rightSpeed) {
    setMotorSpeed(LEFT, leftSpeed);
    setMotorSpeed(RIGHT, rightSpeed);
  }
#elif defined POLOLU_MC33926
  /* Include the Pololu library */
  #include "DualMC33926MotorShield.h"

  /* Create the motor driver object */
  DualMC33926MotorShield drive;
  
  /* Wrap the motor driver initialization */
  void initMotorController() {
    drive.init();
  }

  /* Wrap the drive motor set speed function */
  void setMotorSpeed(int i, int spd) {
    if (i == LEFT) drive.setM1Speed(spd);
    else drive.setM2Speed(spd);
  }

  // A convenience function for setting both motor speeds
  void setMotorSpeeds(int leftSpeed, int rightSpeed) {
    setMotorSpeed(LEFT, leftSpeed);
    setMotorSpeed(RIGHT, rightSpeed);
  }
#elif defined L298_MOTOR_DRIVER
  void initMotorController() {
    digitalWrite(RIGHT_MOTOR_ENABLE, HIGH);
    digitalWrite(LEFT_MOTOR_ENABLE, HIGH);
  }
  
  void setMotorSpeed(int i, int spd) {
    unsigned char reverse = 0;
  
    if (spd < 0)
    {
      spd = -spd;
      reverse = 1;
    }
    if (spd > 255)
      spd = 255;
    
    if (i == LEFT) { 
      if      (reverse == 0) { analogWrite(RIGHT_MOTOR_FORWARD, spd); analogWrite(RIGHT_MOTOR_BACKWARD, 0); }
      else if (reverse == 1) { analogWrite(RIGHT_MOTOR_BACKWARD, spd); analogWrite(RIGHT_MOTOR_FORWARD, 0); }
    }
    else /*if (i == RIGHT) //no need for condition*/ {
      if      (reverse == 0) { analogWrite(LEFT_MOTOR_FORWARD, spd); analogWrite(LEFT_MOTOR_BACKWARD, 0); }
      else if (reverse == 1) { analogWrite(LEFT_MOTOR_BACKWARD, spd); analogWrite(LEFT_MOTOR_FORWARD, 0); }
    }
  }
  
  void setMotorSpeeds(int leftSpeed, int rightSpeed) {
    setMotorSpeed(LEFT, leftSpeed);
    setMotorSpeed(RIGHT, rightSpeed);
  }
#elif defined SMC_G2_MOTOR_DRIVER

  #include <DualG2HighPowerMotorShield.h>

  // Uncomment the version corresponding with the version of your shield.
  // DualG2HighPowerMotorShield24v14 md;
  DualG2HighPowerMotorShield18v18 md;
  // DualG2HighPowerMotorShield24v18 md;
  // DualG2HighPowerMotorShield18v22 md;

  void initMotorController() {
    md.init();
    md.calibrateCurrentOffsets();
    delay(10);
    md.enableDrivers();
    delay(1);
    // Uncomment to flip a motor's direction:
    //md.flipM1(true);
    //md.flipM2(true);
  }

  // M1 = left motor
  // M2 = right motor
  
  void setMotorSpeed(int i, int spd) {
    if(spd > 400)
      spd = 400;
    if(spd < -400)
      spd = -400;

    if (i == LEFT) { 
      md.setM1Speed(spd);
    }
    else /*if (i == RIGHT) //no need for condition*/ {
      md.setM2Speed(spd);
    }
    stopIfFault();
  }
  
  void setMotorSpeeds(int leftSpeed, int rightSpeed) {
    md.setSpeeds(leftSpeed, rightSpeed);
    stopIfFault();
  }

  void stopIfFault()
  {
    if (md.getM1Fault())
    {
      md.disableDrivers();
  	delay(1);
      Serial.println("M1 fault");
      while (1);
    }
    if (md.getM2Fault())
    {
      md.disableDrivers();
  	delay(1);
      Serial.println("M2 fault");
      while (1);
    }
  }
#else
  #error A motor driver must be selected!
#endif

#endif
