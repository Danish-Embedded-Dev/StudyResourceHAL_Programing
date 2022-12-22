/************************************************************/
/* bitbagging.h                                            */
/*                                                          */
/* Class library for bitbagging operation.                  */
/*                                                          */
/* ENGD2103, November 2022                                  */
/************************************************************/

#ifndef _bitbagging_h_
#define _bitbagging_h_

/* Digit table for the 7-segment display */
const uint8_t digitTable[] = {
  0b00111111,       //display 0 
  0b00000110,       //display 1
  0b01011011,       //display 2
  0b01001111,       //display 3
  0b01100110,       //display 4
  0b01101101,       //display 5
  0b01111101,       //display 6
  0b00000111,       //display 7
  0b01111111,       //display 8
  0b01101111,       //display 9
  0b01110111,       //display A
  0b01111100,       //display b
  0b00111001,       //display C
  0b01011110,       //display D
  0b01111001,       //display E
  0b01110001,       //display F
  0b00111000,       //display L
  0b00111110,       //display U
  0b10011000,       //display |
  0b1010000,        //display r
};

//------------------------------------------------------------------------------
// Public functions:

//-----------------------------------------------------------------------------
class bitbagging{
  public:
    void             process(byte count,bool en_count);
    bitbagging(bool val);   //constructor
    void setclock(bool val);
  
  private: 
    
    bool init_clock;
    int state; 
    unsigned long module_time, module_delay, debounce_count;
    bool module_doStep; 
    
    void writeToShiftRegister(unsigned char value);
    void toggleLatch();
    void toggleCLK();
    void shiftBit(bool data);
    bool actionTask();
};

 

#endif
