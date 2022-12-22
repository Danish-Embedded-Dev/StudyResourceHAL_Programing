#include "Scheduler.h"
#include "hal.h"

Scheduler::Scheduler()
{
  isRunning = false;
  module_delay = 15;
  state = 0;
}

bool Scheduler::getRunRed()
{
  return runRed;
}

bool Scheduler::getRunYellow()
{
  return runYellow;
}

bool Scheduler::getRunGreen()
{
  return runGreen;
}
 
bool Scheduler::getRunAccel()
{
  return runAccel;
}


bool Scheduler::getRunCounter()
{
  return runCounter;
}
void Scheduler::process(switch_state_t B2_state) { // Only process the finite state machine on a 'tick' / 'step'
  if (actionTask())
  { // FSM belongs here
    switch(state)
    { 
    case 0:
      // Mode 1
      Serial.println("mode_1");
      runRed = true; // Red module running
      runYellow = true; // Yellow module running 
      runGreen = true; // Green module running
      runCounter = false; //counter module halted
      runAccel  =true;  //accelerometer module halted
//        runSW1    =false; //switch 1 module halted
     
      if (B2_state == DEBOUNCED_PRESS) state = 1;
      break;
    case 1: 
      //  wait for button to released 
       if (B2_state == NOT_PRESSED  ) state = 2;
      break; 
    case 2:
        Serial.println("mode_2:"); 
//      // Mode 2 
      runRed     = false; // Red module halted
      runYellow  = false;   //Yellow module halted 
      runGreen   = false;   //Green module halted
      runCounter = true;  //counter module running
      runAccel   = false;  //accelerometer module halted
//      runSW1     = true;  //switch 1 module running
      if (B2_state == DEBOUNCED_PRESS) state = 3;
      break; 
     case 3:
      //  wait for button to released
             if (B2_state == NOT_PRESSED  ) state = 4;
      break; 

      case 4:
      Serial.println("mode_3:"); 
//      // Mode 3
      runRed     = false;  //Red module halted
      runYellow  = false;  //Yellow module halted 
      runGreen   = false;  //Green module halted
      runCounter = true;   //counter module halted
      runAccel   = false;  //accelerometer module running
//      runSW1     = true;   //switch 1 module halted
      if (B2_state == DEBOUNCED_PRESS) state = 5;
      break; 
      case 5:
      //  wait for button to released
             if (B2_state == NOT_PRESSED  ) state = 6;
      break; 

      case 6:
      Serial.println("mode_4:"); 
//      // Mode 4
      runRed     = true;  //Red module running
      runYellow  = true;  //Yellow module running 
      runGreen   = true;  //Green module running
      runCounter = true;   //counter module running
      runAccel   = false;  //accelerometer module halted
//      runSW1     = true;   //switch 1 module running
      if (B2_state == DEBOUNCED_PRESS) state = 7;
      break; 
      case 7:
      //  wait for button to released
             if (B2_state == NOT_PRESSED  ) state = 8;
      break; 

      case 8:
      Serial.println("mode_5:"); 
//      // Mode 5
      runRed     = true;  //Red module running
      runYellow  = true;  //Yellow module running 
      runGreen   = true;  //Green module running
      runCounter = false; //counter module halted
      runAccel   = true;  //accelerometer module running
//      runSW1     = false; //switch 1 module halted
      if (B2_state == DEBOUNCED_PRESS) state = 9;
      break; 
      case 9:
      //  wait for button to released
             if (B2_state == NOT_PRESSED  ) state = 0;
      break;
      
        default: 
          state = 0; 
        break;
    }
  }
}
