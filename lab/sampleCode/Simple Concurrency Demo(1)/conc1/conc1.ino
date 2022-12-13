/************************************************************/
/* bmconc.ino                                               */
/*                                                          */
/* Concurrency demo                                         */
/* Dr M A Oliver, October 2022                              */
/************************************************************/

#include "hal.h"

bool init_module0_clock;
bool init_module1_clock;
bool init_module2_clock;


void setup() {
  HAL_gpioInit();
  init_module0_clock = true;
  init_module1_clock = true;
  init_module2_clock = true;
}

void loop() {
  // put your main code here, to run repeatedly:

  { // module 0
    static unsigned long module_time, module_delay;
    static bool module_doStep;
    static unsigned char state; // state variable for module 0
    
    if (init_module0_clock) {
      module_delay = 500;
      module_time = millis();
      module_doStep = false;
      init_module0_clock = false;
      state=0;
    }
    else {
      unsigned long m = millis();
      if ( (m - module_time) > module_delay ) {
        module_time = m; 
        module_doStep = true;
      }
      else module_doStep = false;
    }

    if (module_doStep)
    {
      switch(state)
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

  { // module 1
    static unsigned long module_time, module_delay;
    static bool module_doStep;
    static unsigned char state; // state variable for module 1
    
    if (init_module1_clock) {
      module_delay = 300;
      module_time = millis();
      module_doStep = false;
      init_module1_clock = false;
      state=0;
    }
    else {
      unsigned long m = millis();
      if ( (m - module_time) > module_delay ) {
        module_time = m; 
        module_doStep = true;
      }
      else module_doStep = false;
    }

    if (module_doStep)
    {
      switch(state)
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

  { // module 2
    static unsigned long module_time, module_delay;
    static bool module_doStep;
    static unsigned char state; // state variable for module 2
    
    if (init_module2_clock) {
      module_delay = 500;
      module_time = millis();
      module_doStep = false;
      init_module2_clock = false;
      state=0;
    }
    else {
      unsigned long m = millis();
      if ( (m - module_time) > module_delay ) {
        module_time = m; 
        module_doStep = true;
      }
      else module_doStep = false;
    }

    if (module_doStep)
    {
      switch(state)
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
