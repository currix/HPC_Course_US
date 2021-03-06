#include "data_aligned.h"

/**
 * va = a*va + b
 */
inline void scale(int n, REAL a, 
                  REAL * __restrict__ va, REAL * __restrict__ vb) {
  int i;
  for(i=0; i < n; i++) {
    va[i] = a * va[i] + vb[i];
  }
}

