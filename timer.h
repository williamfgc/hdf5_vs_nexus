/*
 * timer.h
 *
 *  Created on: 3 Nov 2014
 *      Author: spu92482
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <time.h>

namespace common {

class Timer {
private:
  clock_t m_begin;

public:
  Timer();

  void reset();

  double elapsed_ms() const;

  void print_elapsed_ms() const;
};
}

#endif /* TIMER_H_ */
