/************************************************************/
/* YellowBlinker.cpp                                        */
/*                                                          */
/* Class library for blinking the Yellow LED.               */
/*                                                          */
/* ENGD2103, November 2022                                  */
/************************************************************/

#include "YellowBlinker.h"
#include "hal.h"

//--------------------------------------------------------------
// Constructor
// Puts class into a sane state whenever an instance of the
// class is declared.
//--------------------------------------------------------------

YellowBlinker::YellowBlinker()
{
  isRunning = false;
  module_delay = 300;
  state = 0;
}


//--------------------------------------------------------------
// process()
//
// Member function that processes timed activity. It takes care
// of timeouts, running / not running etc.
// Returns: nothing
//--------------------------------------------------------------

void YellowBlinker::process()
{
  // Only process the finite state machine on a 'tick' / 'step'
  if (actionTask())
  {
    // FSM belongs here
    switch (state)
    {
    case 0:
      HAL_ledYellow1On;
      state = 1;
      break;
    case 1:
      HAL_ledYellow1Off;
      state = 0;
      break;
    } 
  }
}
