/************************************************************/
/* Accelerometer.h                                           */
/*                                                          */
/* Class library for blinking the Green LED.                */
/*                                                          */
/* ENGD2103, November 2022                                  */
/************************************************************/

#ifndef _Accelerometer_h_
#define _Accelerometer_h_


#include <Wire.h>
#include "hal.h" 
#include "Concurrent.h"         // Base class


class Accelerometer : public Concurrent {
  public:
                     Accelerometer(); 
    void             update_val();
    void             process(byte &accel_seg);
    void             start();
    
    int              get_AccX();
    int              get_AccY();
    int              get_AccZ(); 

  private:
    int              state;
    int             AccX,AccY,AccZ;
};

#endif
