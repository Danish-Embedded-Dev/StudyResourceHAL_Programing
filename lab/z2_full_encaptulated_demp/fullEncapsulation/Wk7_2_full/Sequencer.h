/************************************************************/
/* Sequencer.h                                              */
/*                                                          */
/* Sequencer Class library                                  */
/*                                                          */
/* ENGD2103, November 2022                                  */
/************************************************************/

#ifndef _Sequencer_h_
#define _Sequencer_h_

#include "Concurrent.h"         // Base class


class Sequencer : public Concurrent {
  public:
    void             process();
    Sequencer();

  private:
    int              state;
};

#endif
