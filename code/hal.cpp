/************************************************************/
/* hal.cpp                                                  */
/*                                                          */
/* Hardware Adaption Layer (HAL) implementation             */
/* Name / P-number / Date                                   */
/************************************************************/

#include "hal.h"

void HAL_gpioInit()
{
 //make output for traffic lights
   DDRD |= HAL_RED1;
   DDRD |= HAL_YELLOW1;
   DDRD |= HAL_GREEN1;
   DDRD |= HAL_RED2;
   DDRD |= HAL_YELLOW2;
   DDRD |= HAL_GREEN2;

 //make input pullup
   DDRC &= ~(HAL_SW_1|HAL_SW_1); // PC.0 and PC.1 becomes an input
   PORTC |= (HAL_SW_1|HAL_SW_1); // with pullup. 

 //make output for seven segment
 
  // Make the DATA line an output
  DDRB |= DATA;
  // Make the CLOCK line an output
  DDRB |= CLOCK;
  // Make the LATCH line an output 
  DDRB   |= LATCH;
  
  // Pull the LATCH line low
  HAL_PullLatchLOW;
  
  // Pull the CLOCK line low 
  HAL_PullClockLOW;
}
