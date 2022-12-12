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


RedBlinker     redBlinkControl;
YellowBlinker  yellowBlinkControl;
GreenBlinker   greenBlinkControl;



void setup() {
  HAL_gpioInit();

  // Initialize the red LED module
  redBlinkControl.setRunning(true);

  // Initialize the yellow LED module
  yellowBlinkControl.setRunning(true);
  
  // Initialize the green LED module
  greenBlinkControl.setRunning(true);

}


void loop() {
  // Let the modules do their thing.
  redBlinkControl.process();
  yellowBlinkControl.process();
  greenBlinkControl.process();
}
