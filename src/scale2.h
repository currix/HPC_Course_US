#include "data.h"

/**
 * va = a*va + b
 */
inline void scale(int n, REAL a, REAL *va, REAL *vb) {
  int i;
  for(i=0; i < n; i++) {
    va[i] = a * va[i] + vb[i];
  }
}
