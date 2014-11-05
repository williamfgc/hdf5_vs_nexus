#include <iostream>
#include "timer.h"

namespace common {
Timer::Timer() : m_begin(0) { this->reset(); }

void Timer::reset() { m_begin = clock(); }

double Timer::elapsed_ms() const {
  double diffticks = clock() - m_begin;
  double diffms = (diffticks * 1000) / CLOCKS_PER_SEC;
  return diffms;
}
void Timer::print_elapsed_ms() const {
  std::cout << this->elapsed_ms() << std::endl;
}
}
