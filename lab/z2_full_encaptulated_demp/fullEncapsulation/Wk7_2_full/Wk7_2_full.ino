#include "Sequencer.h"

Sequencer sequencer;



void setup() {
  DDRD |= 0b11111100; // Pins PD7-PD2 as outputs
  sequencer.setRunning(true);
}

void loop() {
  sequencer.process();
}
