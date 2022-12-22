/************************************************************/
/* RedBlinker.h                                             */
/*                                                          */
/* Class library for blinking the RED LED.                  */
/*                                                          */
/* ENGD2103, November 2022                                  */
/************************************************************/

#ifndef _RedBlinker_h_
#define _RedBlinker_h_

#include "Concurrent.h"         // Base class


class RedBlinker : public Concurrent {
  public:
    void             process();
    RedBlinker();

  private:
    int              state;
};

#endif
