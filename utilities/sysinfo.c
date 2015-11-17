#include <time.h>
#include "sysinfo.h"
#include "timer64.h"
#include <unistd.h>

struct sysinfo info;
int sysinfo_set = 0;
/*
 * return total installed ram
 */
unsigned long get_totalram() { 
  if (!sysinfo_set) {
    if (0==sysinfo(&info)) {
      sysinfo_set=1; 
    }
  }
  if (sysinfo_set)
    return info.totalram*info.mem_unit; 
  else
    return -1;
}
/*
 * return free ram
 */
unsigned long get_freeram() {
  // always call sysinfo as free ram changes
  if (0 == sysinfo(&info)) 
    sysinfo_set = 1;
  else
    sysinfo_set = 0;
  
  if (sysinfo_set)
    return info.freeram*info.mem_unit;
  else
    return -1;
}

/*
 * memory unit 
 */
unsigned long get_mem_unit() { 
  if (!sysinfo_set) {
    if (0==sysinfo(&info)) {
      sysinfo_set=1; 
    }
  }
  if (sysinfo_set)
    return info.mem_unit; 
  else
    return -1;
}
/*
 * get approx value for cpu speed in ghz
 */
double get_cpu_speed() {
  ticks tks;
  tks = ticks_start();
  usleep(100000); // 1/10 of a second
  tks = ticks_stop()-tks;
  double ghz=tks*1.0e-8;
  return ghz; 
}
