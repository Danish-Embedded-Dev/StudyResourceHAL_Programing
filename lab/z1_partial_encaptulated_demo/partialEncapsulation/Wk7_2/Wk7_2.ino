#include "Concurrent.h"


/////////////////////////////////////////////////////////
// Example demonstrating how to drive multiple output
// lines simultaneously
/////////////////////////////////////////////////////////

// The LEDs are located on Port D.
// LED1 is connected to Port D Bit 7 (Digital Pin 7)
// LED2 is connected to Port D Bit 6 (Digital Pin 6)
// LED3 is connected to Port D Bit 5 (Digital Pin 5)
// LED4 is connected to Port D Bit 4 (Digital Pin 4)
// LED5 is connected to Port D Bit 3 (Digital Pin 3)
// LED6 is connected to Port D Bit 2 (Digital Pin 2)

#define LEDS_OFF        B00000000
#define LED_1           B10000000
#define LED_2           B01000000
#define LED_3           B00100000
#define LED_4           B00010000
#define LED_5           B00001000
#define LED_6           B00000100


Concurrent sequencer;


unsigned long sequencerFSM()
{
  static int state = 0;
  unsigned long module_delay;

  // FSM for module 0.
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
  return module_delay;
}

void setup() {
  DDRD |= 0b11111100; // Pins PD7-PD2 as outputs
  sequencer.setModuleDelay(50);
  sequencer.setRunning(true);
}

void loop() {
  // put your main code here, to run repeatedly:


  if (sequencer.actionTask())
  {
    unsigned long module_delay;
    module_delay = sequencerFSM();
    sequencer.setModuleDelay(module_delay);
  }

}
