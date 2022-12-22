

/************************************************************/
/* bitbagging.cpp                                           */
/*                                                          */
/* serial to parallet shift register handling               */
/* Name / P-number / Date                                   */
/************************************************************/
#include "hal.h"
#include "bitbagging.h"

bitbagging::bitbagging(bool val){ 
  init_clock = val;
}

void  bitbagging::setclock(bool val){
   init_clock = val;
}

void bitbagging::toggleLatch()
{
  // Pull the LATCH line high
  HAL_PullLatchHIGH;
  // Pull the LATCH line low
  HAL_PullLatchLOW;
}

void bitbagging::toggleCLK()
{
  // Pull the CLOCK line high
  HAL_PullClockHIGH;
  // Pull the CLOCK line low
  HAL_PullClockLOW;
}

void bitbagging::shiftBit(bool data)
{ 

   if(data)
  HAL_PullDataLineHIGH;
  else
  HAL_PullDataLineLOW;
  
//   on the value of data
  toggleCLK();
}

void bitbagging::writeToShiftRegister(unsigned char value)
{
  unsigned char mask = B10000000; // use mask to select the bits
  // in value one at a time
  // Create a loop to send all 8 bits of value to the shift
  // register. Use the value and mask variables to determine
  // whether each bit is high or low. Use shiftBit() to clock
  // each bit into the shift register
  for (byte i = 0; i < 8; i++) {
    shiftBit(bool(value & (mask >> i))); 
  } 
  // Once complete, call toggleLatch() to transfer the shifted
  // data to the outside world
  toggleLatch();
}

/*
 * there are two argument in this function
 * count = show the value on the lcd 
 * en_count = true;  enable the counter and disable accelerator
 * en_count = false; disable the counter and enable accelerator
 */

void bitbagging::process(byte count,bool en_count)
{
  // Only process the finite state machine on a 'tick' / 'step'
  if (actionTask())
  {
    // FSM belongs here
    switch (state)
    {
      case 0:
        if(en_count){
          count = count & 0x0F; //mask lower 4-bit 
        }
        writeToShiftRegister(digitTable[count]);         
        state = 1;
        break;
      case 1:
        if(en_count){
          count = count & 0x0F; //mask lower 4-bit
        }
        count = digitTable[count] | 0x80; //set MSB for dot blink
        writeToShiftRegister(count);   
        state = 0;
        break;
    }
  }
}

bool bitbagging::actionTask()
{
  if (init_clock) {
    module_delay = 500;
    module_time = millis();
    module_doStep = false;
    init_clock = false;
    state = 0;
  }
  else {
    unsigned long m = millis();
    if ( (m - module_time) > module_delay ) {
      module_time = m;
      module_doStep = true;
    }
    else module_doStep = false;
  }
  
  return module_doStep;
} 
