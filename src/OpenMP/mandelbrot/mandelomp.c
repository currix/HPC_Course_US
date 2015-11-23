#include <stdio.h>
#include "ppm_soa.h"
#include <omp.h>

#define REAL float

// set color in pixel (i,j) of img

void color_pixel(IMAGE *img, int i, int j, int niters, int maxiters) {
  img->data_rh[j*img->nx+i]=240.0-(niters*360.0)/maxiters;
  img->data_gs[j*img->nx+i]=1.0;
  img->data_bv[j*img->nx+i] = (niters == maxiters) ? 0.0 : 1.0;
}

// do the iteration that determines if a point is in the set

int iterate(REAL cr, REAL ci, int nmax) {
  REAL zr=cr;
  REAL zi=ci;
  REAL tr2=zr*zr;
  REAL ti2=zi*zi;
  int count = 0;
  while ((++count < nmax) && (tr2+ti2 < 4.0)) {
         zi = 2.0*zr*zi + ci;
         zr = tr2-ti2 + cr;
         tr2=zr*zr;
         ti2=zi*zi;
  }
  return count;
}

// calculate all image pixels

double mandelbrot(IMAGE *img, int maxiters, 
                  REAL x1, REAL x2, REAL y1, REAL y2) { 
  int i,j,count;
  REAL dx = (x2-x1)/img->nx, dy = (y2-y1)/img->ny;
  REAL x,y;
  double flops=0;
#pragma omp parallel for reduction(+:flops)
  for (j = 0; j < img->ny; ++j) {
    for (i = 0; i < img->nx; ++i) {
      x = x1+dx*i;
      y = y1+dy*j;
      count = iterate(x,y,maxiters);
      color_pixel(img,i,j,count,maxiters);
      flops += 4+count*8;
    }
  }
  img->cspace=TYPE_HSV;
  return flops;
}

/**
 * Calculate the mandelbrot set
 * standard: flops=mandelbrotX(img,4096,-2.0,1.0,1.5,-1.5);
 */
int main(void) {
  double secs,flops;
  IMAGE *img=makeimage(1024,1024);
  //start_timer();
  double start = omp_get_wtime();
  flops=mandelbrot(img,4096,-1.2,-0.7,0.5,0.0);
  double end = omp_get_wtime();
  secs = end-start;
  //secs = stop_timer();
  printf("%10.3e %10.3e %10.3e\n",secs,flops,1.0e-9*flops/secs);
  saveimage(img,"mandel_omp.ppm");
  return 0;
}
