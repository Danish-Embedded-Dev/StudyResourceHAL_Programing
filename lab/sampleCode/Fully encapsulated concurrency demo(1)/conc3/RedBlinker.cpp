/************************************************************/
/* RedBlinker.h                                             */
/*                                                          */
/* Class library for blinking the RED LED.                  */
/*                                                          */
/* ENGD2103, November 2022                                  */
/************************************************************/

#include "RedBlinker.h"
#include "hal.h"

//--------------------------------------------------------------
// Constructor
// Puts class into a sane state whenever an instance of the
// class is declared.
//--------------------------------------------------------------

RedBlinker::RedBlinker()
{
  isRunning = false;
  module_delay = 500;
  state = 0;
}


//--------------------------------------------------------------
// process()
//
// Member function that processes timed activity. It takes care
// of timeouts, running / not running etc.
// Returns: nothing
//--------------------------------------------------------------

void RedBlinker::process()
{
  // Only process the finite state machine on a 'tick' / 'step'
  if (actionTask())
  {
    // FSM belongs here
    switch (state)
    {
    case 0:
      HAL_ledRed1On;
      state = 1;
      break;
    case 1:
      HAL_ledRed1Off;
      state = 0;
      break;
    } 
  }
}
