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
  module_delay = 10;
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
          HAL_ledGreen1On;
          module_delay = 600;
          state = 1;
          break;
        case 1:
          HAL_ledGreen1Off;
          module_delay = 450;
          state = 2;
          break;
        case 2:
          HAL_ledGreen1On;
          module_delay = 1800;
          state = 3;
          break;
        case 3:
          HAL_ledGreen1Off;
          module_delay = 1200;
          state = 0;
          break;
      }

    }
  }
}
