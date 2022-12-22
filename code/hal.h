/************************************************************/
/* hal.h                                                    */
/*                                                          */
/* Hardware Adaption Layer (HAL) definitions                */
/* Name / P-number / Date                                   */
/************************************************************/

#ifndef _HAL_H_
#define _HAL_H_

#include <Arduino.h>


//for traffic lights
#define HAL_RED1            B00100000       //digital 5
#define HAL_YELLOW1         B01000000       //digital 6
#define HAL_GREEN1          B10000000       //digital 7

#define HAL_RED2            B00010000       //digital 4
#define HAL_YELLOW2         B00001000       //digital 3
#define HAL_GREEN2          B00000100       //digital 2


#define HAL_ledRed1On       PORTD |=  HAL_RED1
#define HAL_ledRed1Off      PORTD &= ~HAL_RED1
#define HAL_ledYellow1On    PORTD |=  HAL_YELLOW1
#define HAL_ledYellow1Off   PORTD &= ~HAL_YELLOW1
#define HAL_ledGreen1On     PORTD |=  HAL_GREEN1
#define HAL_ledGreen1Off    PORTD &= ~HAL_GREEN1

#define HAL_ledRed2On       PORTD |=  HAL_RED2
#define HAL_ledRed2Off      PORTD &= ~HAL_RED2
#define HAL_ledYellow2On    PORTD |=  HAL_YELLOW2
#define HAL_ledYellow2Off   PORTD &= ~HAL_YELLOW2
#define HAL_ledGreen2On     PORTD |=  HAL_GREEN2
#define HAL_ledGreen2Off    PORTD &= ~HAL_GREEN2
 
 
//for button input

//button states
typedef enum
{
  NOT_PRESSED,
  PARTIAL_PRESS,
  DEBOUNCED_PRESS
} switch_state_t;

// These definitions would belong in the HAL module with bare metal. 
#define HAL_SW_1    B00000001
#define HAL_SW_2    B00000010
#define HAL_SW_RELEASED(HAL_SW)        (PINC & HAL_SW)
#define HAL_SW_PRESSED(HAL_BUTTON)     !(PINC & HAL_SW) 


//for seven segment
#define DATA  B00000001       //digital_8 // DATA pin on the 595
#define CLOCK B00010000       //digital_12  // CLOCK pin on the 595
#define LATCH B00100000       //digital_13 // LATCH pin on the 595

#define HAL_PullDataLineHIGH  PORTB |=  DATA
#define HAL_PullDataLineLOW   PORTB &= ~DATA  
#define HAL_PullLatchHIGH     PORTB |=  LATCH
#define HAL_PullLatchLOW      PORTB &= ~LATCH 
#define HAL_PullClockHIGH     PORTB |=  CLOCK
#define HAL_PullClockLOW      PORTB &= ~CLOCK


//for accelerometer
#define MPU_6050 0x68 // TODO: Add I2C address of MPU6050
#define PWR_MGMT_1 0x6B // TODO: Add address of PWR_MGMT_1 register
#define ACCEL_XOUT_HI 0x3B// TODO: Add ACCEL_XOUT (MSB) register
#define ACCEL_YOUT_HI 0x3D// TODO: Add ACCEL_YOUT (MSB) register
#define ACCEL_ZOUT_HI 0x3F// TODO: Add ACCEL_ZOUT (MSB) register

void HAL_gpioInit();

#endif
