/************************************************************/
/* bmconc.ino                                               */
/*                                                          */
/* Bare metal / concurrency demo                            */
/* ENGD2103, November 2022                                  */
/************************************************************/

#include "hal.h"
#include "RedBlinker.h"
#include "YellowBlinker.h"
#include "GreenBlinker.h"
#include "ButtonDebounce.h"
#include "bitbagging.h"
#include "Accelerometer.h"
#include "Scheduler.h"

//use to display the position of the accelerometer
byte accel_position=0;
byte counter = 0; //count number of pressed
bitbagging DP_Module(true);


ButtonDebounce switch_1(HAL_SW_1);
ButtonDebounce switch_2(HAL_SW_2);

RedBlinker     redBlinkControl;
YellowBlinker  yellowBlinkControl;
GreenBlinker   greenBlinkControl;

Accelerometer  accelerometer;
Scheduler      scheduler;


void setup() {
  
  HAL_gpioInit();

  // Initialize the Seven segment module sa display module
  DP_Module.setclock(true);

  // Initialize the button_1 module
  switch_1.setmodule(true);

  // Initialize the button_2 module
  switch_2.setmodule(true);
  
  // Initialize the red LED module
  redBlinkControl.setRunning(false);

  // Initialize the yellow LED module
  yellowBlinkControl.setRunning(false);

  // Initialize the green LED module
  greenBlinkControl.setRunning(false);

  // Initialize the accelerometer module  
  accelerometer.start();
  accelerometer.setRunning(false);

  
  // Initialize the scheduler
  scheduler.setRunning(true);
  
  Serial.begin(9600);

}


void loop() { 
  
  // Let the modules do their thing.
  redBlinkControl.process();
  yellowBlinkControl.process();
  greenBlinkControl.process();
  accelerometer.process(accel_position);

  
  // Acquire B2_state through debouncers
  counter = switch_1.process(counter); //it just pass counter and update new value
  switch_2.process(counter);    //it just pass counter but not update
  // Run the scheduler 
  scheduler.process(switch_2.getstate());

  
  
  // Turn modules on/off using
  // information from scheduler
  redBlinkControl.setRunning(scheduler.getRunRed());
  yellowBlinkControl.setRunning(scheduler.getRunYellow());
  greenBlinkControl.setRunning(scheduler.getRunGreen());
  accelerometer.setRunning(scheduler.getRunAccel());
  

  //display the 7-segment
  if(scheduler.getRunCounter()){
      DP_Module.process(counter,true); 
  }

  if(scheduler.getRunAccel()){
      DP_Module.process(accel_position,false); 
  }
   
}
