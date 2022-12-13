/************************************************************/
/* GreenBlinker.h                                           */
/*                                                          */
/* Class library for blinking the Green LED.                */
/*                                                          */
/* ENGD2103, November 2022                                  */
/************************************************************/

#ifndef _GreenBlinker_h_
#define _GreenBlinker_h_

#include "Concurrent.h"         // Base class


class GreenBlinker : public Concurrent {
  public:
    void             process();
    GreenBlinker();

  private:
    int              state;
};

#endif
