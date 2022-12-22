#ifndef  _Scheduler_h_
#define _Scheduler_h_

#include "Concurrent.h" // Base class
#include "Hal.h"

class Scheduler : public Concurrent {
  public: 
    void process(switch_state_t B2_state);  
    Scheduler();
    bool getRunRed();
    bool getRunYellow();
    bool getRunGreen();
    bool getRunAccel();
    bool getRunCounter();
  private: 
    int state;
    bool runRed, runYellow, runGreen,runAccel,runCounter;
};

#endif
