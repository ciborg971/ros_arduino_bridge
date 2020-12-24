/* *************************************************************
   Encoder driver function definitions - by James Nugen
   ************************************************************ */
   
   
#ifdef ARDUINO_ENC_COUNTER
  //below can be changed, but should be PORTD pins; 
  //otherwise additional changes in the code are required
  #define LEFT_ENC_PIN_A PD2  //pin 2
  #define LEFT_ENC_PIN_B PD3  //pin 3
  
  //below can be changed, but should be PORTC pins
  #define RIGHT_ENC_PIN_A PC4  //pin A4
  #define RIGHT_ENC_PIN_B PC5   //pin A5
#endif

#ifdef ARDUINO_ENC_COUNTER2
  #include "Encoder.h";
  #define LEFT_ENC_PIN_A 53
  #define LEFT_ENC_PIN_B 51  
  
  #define RIGHT_ENC_PIN_A 47
  #define RIGHT_ENC_PIN_B 45

  Encoder encoder_l(LEFT_ENC_PIN_A, LEFT_ENC_PIN_B);
  Encoder encoder_r(RIGHT_ENC_PIN_A, RIGHT_ENC_PIN_B);
#endif
   
long readEncoder(int i);
void resetEncoder(int i);
void resetEncoders();

