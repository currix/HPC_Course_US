#include<stdio.h>
#include<math.h>
#include "../utilities/timing.h"

//include file "SCALE".h (SCALE is defined by -D compiler arg)
#define str(s) #s
#define xstr(s) str(s)
#include xstr(SCALE.h)

#define LOOP_COUNT ARRAY_SIZE 
#define ITERATIONS 100000000
#define FLOPS (ITERATIONS*2.0)*LOOP_COUNT

/**
 * Sum[x^i,{i,0,n}]
 */
double powsum(REAL x, int n) {
  int i;
  if (x!=1.0)
    return (pow(x,n+1)-1)/(x-1.0);
  else
    return n+1;
}

int main() { 
    int i,j,k;
    REAL a = 1.00000001;
    REAL expected=0,err=0;
    double secs;
    // initialize
    for(i=0; i < LOOP_COUNT; i++) {
        data.va[i] = (REAL)i*0.25;
        data.vb[i] = (REAL)i;
    }	
    // main iteration loop
    start_timer();
    for(j=0; j < ITERATIONS; j++) { 
      scale(LOOP_COUNT,a,data.va,data.vb);
    }
    secs=stop_timer();
    // print results
    expected = pow((double)a,(double) ITERATIONS)*(LOOP_COUNT-1)*0.25
              + data.vb[LOOP_COUNT-1]*powsum(a,ITERATIONS-1);
    err = fabs(data.va[LOOP_COUNT-1]-expected)/expected; 
    printf("%10.3e %10.3e # %3d %3d %s %s %s\n",
            FLOPS/secs, err,
            ((long int)data.va)%32,((long int)data.vb)%32,
            xstr(SCALE),xstr(REAL),xstr(FLAGS));
    return 0;
}
