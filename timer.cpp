#include "timer.h"

namespace common {
Timer::Timer() : m_begin(0), m_end(0) {}

void Timer::start() { m_begin = clock(); }

void Timer::stop() { m_end = clock(); }

double Timer::elapsed_ms() const {
  double diffticks = m_end - m_begin;
  double diffms = (diffticks * 1000) / CLOCKS_PER_SEC;
  return diffms;
}
}
