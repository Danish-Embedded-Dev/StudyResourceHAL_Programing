/************************************************************/
/* GreenBlinker.cpp                                         */
/*                                                          */
/* Class library for blinking the Green LED.                */
/*                                                          */
/* ENGD2103, November 2022                                  */
/************************************************************/

#include "GreenBlinker.h"
#include "hal.h"

//--------------------------------------------------------------
// Constructor
// Puts class into a sane state whenever an instance of the
// class is declared.
//--------------------------------------------------------------

GreenBlinker::GreenBlinker()
{
  isRunning = false;
  module_delay = 1000;
  state = 0;
}


//--------------------------------------------------------------
// process()
//
// Member function that processes timed activity. It takes care
// of timeouts, running / not running etc.
// Returns: nothing
//--------------------------------------------------------------

void GreenBlinker::process()
{
  // Only process the finite state machine on a 'tick' / 'step'
  if (actionTask())
  {
    // FSM belongs here
    {

      switch (state)
      {
        case 0:
          HAL_ledGreen1Off; 
          HAL_ledGreen2Off; 
          state = 1;
          break;
        case 1:
          HAL_ledGreen1Off; 
          HAL_ledGreen2Off; 
          state = 2;
          break;
        case 2:
          HAL_ledGreen1On; 
          HAL_ledGreen2Off; 
          module_delay = 5000;
          state = 3;
          break;
        case 3:
          HAL_ledGreen1Off; 
          HAL_ledGreen2Off; 
          module_delay = 1000;
          state = 4;
          break;
        case 4:
          HAL_ledGreen1Off; 
          HAL_ledGreen2Off; 
          state = 5;
          break;
        case 5:
          HAL_ledGreen1Off; 
          HAL_ledGreen2Off; 
          state = 6;
          break;
        case 6:
          HAL_ledGreen1Off; 
          HAL_ledGreen2On; 
          module_delay = 3000;
          state = 7;
          break;
        case 7:
          HAL_ledGreen1Off; 
          HAL_ledGreen2Off; 
          module_delay = 1000;
          state = 0;
      }

    }
  }
}
