#include <stdio.h>
#include "sysinfo.h"
#include "timer64.h"
#include "timing.h"

int main() {
  ticks tks;
  unsigned long mem;
  double secs;
  // system ram
  mem=get_totalram();
  printf("\nRAM installed: %ld",mem);
  mem=get_freeram();
  printf("\nRAM available: %ld",mem);
  // cpu speed
  tks = ticks_start();
  start_timer();
  double speed = get_cpu_speed();
  tks = ticks_stop()-tks;
  secs=stop_timer();
  printf("\nCPU-speed (GHz): %f",speed);
  printf("\nTicks for call: %ld",(long)tks);
  printf("\nSecs for call: %f",secs);
  printf("\n");
}

