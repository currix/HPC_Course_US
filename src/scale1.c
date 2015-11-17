#include "scale1.h"

/**
 * va = a*va + b
 */
void scale(int n, REAL a, REAL *va, REAL *vb) {
  int i;
  for(i=0; i < n; i++) { 
    va[i] = a * va[i] + vb[i];
  }
}
