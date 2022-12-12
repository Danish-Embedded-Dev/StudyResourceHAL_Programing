/************************************************************/
/* hal.cpp                                                  */
/*                                                          */
/* Hardware Adaption Layer (HAL) implementation             */
/* Name / P-number / Date                                   */
/************************************************************/

#include "hal.h"

void HAL_gpioInit()
{
  pinMode(HAL_RED1, OUTPUT);
  pinMode(HAL_YELLOW1, OUTPUT);
  pinMode(HAL_GREEN1, OUTPUT);

  pinMode(HAL_SW1, INPUT_PULLUP);
}
