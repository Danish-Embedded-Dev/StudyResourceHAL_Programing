/************************************************************/
/* Sequencer.cpp                                             */
/*                                                          */
/* Sequencer Class library.                                  */
/*                                                          */
/* ENGD2103, November 2022                                  */
/************************************************************/

#include "Sequencer.h"
#include "hal.h"


#define LEDS_OFF B00000000
#define LED_1 B10000000
#define LED_2 B01000000
#define LED_3 B00100000
#define LED_4 B00010000
#define LED_5 B00001000
#define LED_6 B00000100


//--------------------------------------------------------------
// Constructor
// Puts class into a sane state whenever an instance of the
// class is declared.
//--------------------------------------------------------------

Sequencer::Sequencer()
{
  isRunning = false;
  module_delay = 50;
  state = 0;
}


//--------------------------------------------------------------
// process()
//
// Member function that processes timed activity. It takes care
// of timeouts, running / not running etc.
// Returns: nothing
//--------------------------------------------------------------

void Sequencer::process()
{
  // Only process the finite state machine on a 'tick' / 'step'
  if (actionTask())
  {
    switch (state)
    {
      case 0:
        PORTD = LED_1 | LED_6;
        module_delay = 1600;
        state = 1;
        break;
      case 1:
        PORTD = LED_2 | LED_5;
        module_delay = 1200;
        state = 2;
        break;
      case 2:
        PORTD = LED_3 | LED_4;
        module_delay = 800;
        state = 3;
        break;
      case 3:
        PORTD = LEDS_OFF;
        module_delay = 400;
        state = 0;
        break;
      default:
        state = 0;
    }
  }
}
