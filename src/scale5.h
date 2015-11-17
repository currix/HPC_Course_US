#include "data_aligned.h"
#include <immintrin.h>
/**
 * va = a*va + b
 */
inline void scale(int n, REAL a, 
                  REAL * __restrict__ va, REAL * __restrict__ vb) {
  int i;
//  if (n % 8 != 0) {
//    printf("Fatal error: loop count must be divisibe by 8!\n");
//    exit(-1);
//  }
#ifdef USE_DOUBLE
  __m256d vrega = _mm256_set1_pd(a);
#else
  __m256 vrega = _mm256_set1_ps(a);
#endif

  for(i=0; i < n; i+=8) {

#ifdef USE_DOUBLE
    __m256d vregva1 = _mm256_load_pd (&va[i]);
    __m256d vregva2 = _mm256_load_pd (&va[i+4]);
    __m256d vregvb1 = _mm256_load_pd (&vb[i]);
    __m256d vregvb2 = _mm256_load_pd (&vb[i+4]);
  #ifdef __AVX2__
    vregva1 =  _mm256_fmadd_pd (vrega, vregva1, vregvb1);
    vregva2 =  _mm256_fmadd_pd (vrega, vregva2, vregvb2);
  #else
    vregva1 = _mm256_mul_pd(vrega,vregva1);  
    vregva1 = _mm256_add_pd(vregva1,vregvb1);
    vregva2 = _mm256_mul_pd(vrega,vregva2);  
    vregva2 = _mm256_add_pd(vregva2,vregvb2);
  #endif
    _mm256_store_pd (&va[i], vregva1);
    _mm256_store_pd (&va[i+4], vregva2);
#else
    __m256 vregva1 = _mm256_load_ps (&va[i]);
    __m256 vregvb1 = _mm256_load_ps (&vb[i]);
  #ifdef __AVX2__
    vregva1 =  _mm256_fmadd_ps (vrega, vregva1, vregvb1);
  #else
    vregva1 = _mm256_mul_ps(vrega,vregva1);  
    vregva1 = _mm256_add_ps(vregva1,vregvb1);
  #endif
    _mm256_store_ps (&va[i], vregva1);
#endif

  }
}
