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

void YellowBlinker::process()
{
  // Only process the finite state machine on a 'tick' / 'step'
  if (actionTask())
  {
    // FSM belongs here
    switch (state)
    {  
        case 0:
          HAL_ledYellow1Off; 
          HAL_ledYellow2Off; 
          state = 1;
          break;
        case 1:
          HAL_ledYellow1On; 
          HAL_ledYellow2Off; 
          state = 2;
          break;
        case 2:
          HAL_ledYellow1Off; 
          HAL_ledYellow2Off; 
          module_delay = 5000;
          state = 3;
          break;
        case 3:
          HAL_ledYellow1On; 
          HAL_ledYellow2Off; 
          module_delay = 1000;
          state = 4;
          break;
        case 4:
          HAL_ledYellow1Off; 
          HAL_ledYellow2Off; 
          state = 5;
          break;
        case 5:
          HAL_ledYellow1Off; 
          HAL_ledYellow2On; 
          state = 6;
          break;
        case 6:
          HAL_ledYellow1Off; 
          HAL_ledYellow2Off; 
          module_delay = 3000;
          state = 7;
          break;
        case 7:
          HAL_ledYellow1Off; 
          HAL_ledYellow2On; 
          module_delay = 1000;
          state = 0;
    } 
  }
}
