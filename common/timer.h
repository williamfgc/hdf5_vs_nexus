/*
 * timer.h
 *
 *  Created on: 3 Nov 2014
 *      Author: spu92482
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <time.h>


namespace common
{

  class Timer
  {
  private:

    clock_t m_begin;
    clock_t m_end;

  public:

    Timer();

    void start();

    void stop();

    double elapsed_ms() const;

  };


}




#endif /* TIMER_H_ */
