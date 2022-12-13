/************************************************************/
/* Template.cpp                                             */
/*                                                          */
/* Template Class library.                                  */
/*                                                          */
/* ENGD2103, November 2022                                  */
/************************************************************/

#include "Template.h"
#include "hal.h"

//--------------------------------------------------------------
// Constructor
// Puts class into a sane state whenever an instance of the
// class is declared.
//--------------------------------------------------------------

Template::Template()
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

void Template::process()
{
  // Only process the finite state machine on a 'tick' / 'step'
  if (actionTask())
  {

  }
}