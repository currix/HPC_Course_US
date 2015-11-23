#include <time.h>
#include "timing.h"

double getSecs() {
  static struct timespec tp1;
  clock_gettime(CLOCK_REALTIME, &tp1);
  return  tp1.tv_sec + tp1.tv_nsec / 1e9;
}

void start_timer() {
  startSecs = getSecs();
  return;
}

double stop_timer() {
  return getSecs() - startSecs;
}    
