/************************************************************/
/* YellowBlinker.h                                          */
/*                                                          */
/* Class library for blinking the Yellow LED.               */
/*                                                          */
/* ENGD2103, November 2022                                  */
/************************************************************/

#ifndef _YellowBlinker_h_
#define _YellowBlinker_h_

#include "Concurrent.h"         // Base class


class YellowBlinker : public Concurrent {
  public:
    void             process();
    YellowBlinker();

  private:
    int              state;
};

#endif
