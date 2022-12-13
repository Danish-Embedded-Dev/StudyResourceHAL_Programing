/************************************************************/
/* hal.h                                                    */
/*                                                          */
/* Hardware Adaption Layer (HAL) definitions                */
/* Name / P-number / Date                                   */
/************************************************************/

#ifndef _HAL_H_
#define _HAL_H_

#include <Arduino.h>

#define HAL_RED1            2
#define HAL_YELLOW1         3
#define HAL_GREEN1          4
#define HAL_RED1            5
#define HAL_YELLOW1         6
#define HAL_GREEN1          7

#define HAL_ledRed1On       digitalWrite(HAL_RED1, HIGH)
#define HAL_ledRed1Off      digitalWrite(HAL_RED1, LOW)
#define HAL_ledYellow1On    digitalWrite(HAL_YELLOW1, HIGH)
#define HAL_ledYellow1Off   digitalWrite(HAL_YELLOW1, LOW)
#define HAL_ledGreen1On     digitalWrite(HAL_GREEN1, HIGH)
#define HAL_ledGreen1Off    digitalWrite(HAL_GREEN1, LOW)


#define HAL_SW1             B00000001
#define HAL_sw1Released     (PINC & HAL_SW1)
#define HAL_sw1Pressed      !HAL_sw1Released


void HAL_gpioInit();

#endif
