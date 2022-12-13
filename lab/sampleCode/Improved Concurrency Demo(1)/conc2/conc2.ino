/************************************************************/
/* bmconc.ino                                               */
/*                                                          */
/* Bare metal / concurrency demo                            */
/* ENGD2103, November 2022                                  */
/************************************************************/

#include "hal.h"
#include "Concurrent.h"

Concurrent redControl;
Concurrent yellowControl;
Concurrent greenControl;

//-----------------------------------------------------
// redTask()
// Basic FSM to blink the red LED
//-----------------------------------------------------              

void redTask()
{
  static int state = 0;
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


//-----------------------------------------------------
// yellowTask()
// Basic FSM to blink the yellow LED
//-----------------------------------------------------              

void yellowTask()
{
  static int state = 0;
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


//-----------------------------------------------------
// greenTask()
// FSM to blink the green LED
// Note this function returns an updated module delay.
// This is an example of being able to change the
// timings on-the-fly
//-----------------------------------------------------              

unsigned long greenTask()
{
  unsigned long new_time;
  static char state = 0;
  switch(state)
  {
  case 0:
    HAL_ledGreen1On;
    new_time = 600;
    state = 1;
    break;
  case 1:
    HAL_ledGreen1Off;
    new_time = 450;
    state = 2;
    break;
  case 2:
    HAL_ledGreen1On;
    new_time = 1800;
    state = 3;
    break;
  case 3:
    HAL_ledGreen1Off;
    new_time = 1200;
    state = 0;
    break;
  }

  // Returning the new delay time.
  return new_time;
}  


void setup() {
  HAL_gpioInit();

  // Initialize the red LED module
  redControl.setModuleDelay(500);
  redControl.startRunning();

  // Initialize the yellow LED module
  yellowControl.setModuleDelay(300);
  yellowControl.startRunning();

  // Initialize the green LED module
  greenControl.setModuleDelay(600);
  greenControl.startRunning();
}


void loop() {
  // Check to see if the red LED's task needs
  // carrying out.
  if (redControl.actionTask())
  {
    redTask();
  }

  // Check to see if the yellow LED's task needs
  // carrying out.
  if (yellowControl.actionTask())
  {
    yellowTask();
  }

  // Check to see if the green LED's task needs
  // carrying out.
  if (greenControl.actionTask())
  {
    // When the task is carried out, the new required
    // module delay is returned from the FSM function. 
    unsigned long new_delay;
    new_delay = greenTask();
    greenControl.setModuleDelay(new_delay);   // Updating the module delay
  }

}
