/************************************************************/
/* Accelerometer.cpp                                         */
/*                                                          */
/* Class library for blinking the Green LED.                */
/*                                                          */
/* ENGD2103, November 2022                                  */
/************************************************************/

#include "Accelerometer.h"
#include "hal.h"

//--------------------------------------------------------------
// Constructor
// Puts class into a sane state whenever an instance of the
// class is declared.
//--------------------------------------------------------------

Accelerometer::Accelerometer()
{
  isRunning = false;
  module_delay = 333;
  state = 0;
}

//setup and to start the accelerometer
void Accelerometer::start(){
  // Set-up the I2C for Accelerometer / Gyro
  Wire.begin();
  //Put the MPU6050 IC into the correct operating mode
  Wire.beginTransmission(MPU_6050);
  Wire.write(PWR_MGMT_1); // Power Management 1 Register
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}

//update the accelerometer value
void Accelerometer::update_val(){
  // Tell the MPU-6050 that its data registers need to be
  // read, commencing with MSB of the Z-component
  // of acceleration
  Wire.beginTransmission(MPU_6050);
  Wire.write(ACCEL_XOUT_HI);
  Wire.endTransmission(false);
  // Attempt to read 2 consecutive bytes from the MPU6050.
  // From above, these will be the MSB of the Z-component of
  // acceleration followed by its LSB.
  Wire.requestFrom(MPU_6050, 6 , true); // request 6 registers
  if (Wire.available() >= 2)
  {
    // Two 8-bit reads to give 16-bit result
    AccX = Wire.read() << 8; // Read and shift MSB
    AccX |= Wire.read(); // Append the LSB

    AccY = Wire.read() << 8; // Read and shift MSB
    AccY |= Wire.read(); // Append the LSB

    AccZ = Wire.read() << 8; // Read and shift MSB
    AccZ |= Wire.read(); // Append the LSB  
  } 
  
}


//return AccX
int Accelerometer::get_AccX(){
  return AccX;
}

//return AccY
int Accelerometer::get_AccY(){
  return AccY;
}

//return AccZ
int Accelerometer::get_AccZ(){
  return AccZ;
}


//--------------------------------------------------------------
// process()
//
// Member function that processes timed activity. It takes care
// of timeouts, running / not running etc.
// Returns: nothing
//--------------------------------------------------------------

void Accelerometer::process(byte &accel_seg)
{
//  update_val();  //update latest value
  // Only process the finite state machine on a 'tick' / 'step'
  if (actionTask())
  { 
    accel_seg = 17;   //F
    //lying flat
    if(AccZ>AccX && AccZ>AccY){ 
      accel_seg = 15;   //F
    }
    
    //reverse Flat
    if(AccZ<AccX && AccZ<AccY){ 
      accel_seg = 11;  //b
     }

    //landscape
    if(AccX>AccZ && AccX>AccY){ 
       accel_seg = 16;  //L
    }

    //upside-down in landscape
    if(AccX<AccZ && AccX<AccY){ 
       accel_seg = 17;  //U
    }
    
    //portrait-left
    if(AccY>AccZ && AccY>AccX){ 
       accel_seg = 18;  //|_
    }

    //portrait-right
    if(AccY<AccZ && AccY<AccX){ 
      accel_seg = 19;  //r
    }
    
  }
}
