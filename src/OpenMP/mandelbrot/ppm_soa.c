#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "ppm_soa.h"

#define COLORS 255
#define NALIGN 32

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} RGB;

void hsv2rgb(float h, float s, float v, float *r, float *g, float *b);
void rgb2hsv(float r, float g, float b, float *h, float *s, float *v);

/*
  create a hsv image with given dimensions (and some calculated pattern)
*/
IMAGE *makeimage(int nx, int ny) {
    IMAGE *img;
    img = (IMAGE *) malloc(sizeof(IMAGE));
    if (!img) {
       fprintf(stderr, "Unable to allocate image\n");
       exit(1);
    } 
    int i,j;
    img->nx = nx;
    img->ny = ny;
    int nsize=img->nx*img->ny;
    posix_memalign((void**) &(img->data_rh),NALIGN,nsize*sizeof(float));
    posix_memalign((void**) &(img->data_gs),NALIGN,nsize*sizeof(float));
    posix_memalign((void**) &(img->data_bv),NALIGN,nsize*sizeof(float));

    if ((!img->data_rh) || (!img->data_gs) || (!img->data_bv)) {
       fprintf(stderr, "Unable to allocate image data\n");
       exit(1);
    } 
    for (i=0;i<img->ny;i++) {
      for (j=0;j<img->nx;j++) {
        img->data_rh[i*img->nx+j] = (j*360)/((float) img->nx);
        img->data_gs[i*img->nx+j] = 1.0;
        img->data_bv[i*img->nx+j] = 1.0;
      }
    }
    img->cspace=TYPE_HSV;
    return img;
}
/*
  read a rgb image from file
*/
IMAGE *readimage(char *filename) {
    IMAGE *img;
    int i;
    float fact=1.0;
    img = (IMAGE *) malloc(sizeof(IMAGE));
    if (!img) {
       fprintf(stderr, "Unable to allocate image\n");
       exit(1);
    } 
    img->cspace = TYPE_RGB; // from file always rgb
    int depth;
    FILE *fp = fopen(filename, "rb"); 
    if (!fp) {
       fprintf(stderr, "Unable to open file '%s'\n", filename);
       exit(1);
    }
    char buff[256];
    if (!fgets(buff, sizeof(buff), fp)) {
       perror(filename);
       exit(1);
    }
    if (buff[0] != 'P' || buff[1] != '6') {
       fprintf(stderr, "Invalid image format %c%c\n",buff[0],buff[1]);
       exit(1);
    }
    do {
      if (!fgets(buff, sizeof(buff), fp)) {
        perror(filename);
        exit(1);
      }
    } while (buff[0]=='#');

    if (sscanf(buff, "%u %u", &img->nx, &img->ny) != 2) {
         fprintf(stderr, "Invalid image size (%s '%s')\n", buff, filename);
         exit(1);
    }
    if ((fscanf(fp, "%d", &depth) != 1) || (depth!=COLORS)) {
         fprintf(stderr, "Invalid rgb component ('%s')\n", filename);
         exit(1);
    }
    while (fgetc(fp) != '\n') ;

    int nsize=img->nx*img->ny;
    posix_memalign((void**) &(img->data_rh),NALIGN,nsize*sizeof(float));
    posix_memalign((void**) &(img->data_gs),NALIGN,nsize*sizeof(float));
    posix_memalign((void**) &(img->data_bv),NALIGN,nsize*sizeof(float));

    if ((!img->data_rh) || (!img->data_gs) || (!img->data_bv)) {
       fprintf(stderr, "Unable to allocate image data\n");
       exit(1);
    } 

    RGB *prgb = 
      (RGB *) malloc(img->nx * img->ny * sizeof(RGB));
    if (!prgb) {
       fprintf(stderr, "Unable to allocate rgb buffer\n");
       exit(1);
    } 

    if (fread(prgb, 3 * img->nx, img->ny, fp) != img->ny) {
         fprintf(stderr, "Invalid image data ('%s')\n", filename);
         exit(1);
    }
    fact=1.0/COLORS;
    for (i=0; i< img->nx*img->ny; i++) {
      img->data_rh[i] = (float) prgb[i].r*fact;
      img->data_gs[i] = (float) prgb[i].g*fact;
      img->data_bv[i] = (float) prgb[i].b*fact;
    }
    free (prgb);
    fclose(fp);
    return img;
}
/*
  save image to file (converts output pixels to rgb if necessary)
*/
void saveimage(const IMAGE *img, char *filename) {
    int i;
    float r,g,b;
    FILE *fp = fopen(filename, "wb"); 
    fprintf(fp, "P6\n%d %d\n255\n", img->nx,img->ny);
    
    RGB *prgb = 
      (RGB *) malloc(img->nx * img->ny * sizeof(RGB));
    if (!prgb) {
       fprintf(stderr, "Unable to allocate rgb buffer\n");
       exit(1);
    } 
    for (i=0; i< img->nx*img->ny; i++) {
      if (img->cspace == TYPE_HSV) {
        hsv2rgb(img->data_rh[i],img->data_gs[i],img->data_bv[i],
                &r,&g,&b);
        prgb[i].r = (int) (r*COLORS);
        prgb[i].g = (int) (g*COLORS);
        prgb[i].b = (int) (b*COLORS);
      } else {
        prgb[i].r = (int) (img->data_rh[i]*COLORS);
        prgb[i].g = (int) (img->data_gs[i]*COLORS);
        prgb[i].b = (int) (img->data_bv[i]*COLORS);
      }
    }
    fwrite(prgb, 3 * img->nx, img->ny, fp);
    free(prgb);
    fclose(fp);
}
/*
  convert image to hsv
*/
void image2hsv(IMAGE *img) {
    int i;
    if (img->cspace==TYPE_HSV) 
      return;
    for (i=0; i< img->nx*img->ny; i++) {
      rgb2hsv(img->data_rh[i],img->data_gs[i],img->data_bv[i],
              &img->data_rh[i],&img->data_gs[i],&img->data_bv[i]);
    }
    img->cspace=TYPE_HSV;
    return;
}
/**
 * convert HSV to RGB
 */
void hsv2rgb(float h, float s, float v, float *r, float *g, float *b)
{
    float      hh, p, q, t, ff;
    long        i;

    if(s <= 0.0) {       // < is bogus, just shuts up warnings
        *r = v;
        *g = v;
        *b = v;
        return;
    }
    hh = h;
    if(hh >= 360.0) hh = 0.0;
    hh /= 60.0;
    i = (long)hh;
    ff = hh - i;
    p = v * (1.0 - s);
    q = v * (1.0 - (s * ff));
    t = v * (1.0 - (s * (1.0 - ff)));

    switch(i) {
    case 0:
        *r = v;
        *g = t;
        *b = p;
        break;
    case 1:
        *r = q;
        *g = v;
        *b = p;
        break;
    case 2:
        *r = p;
        *g = v;
        *b = t;
        break;

    case 3:
        *r = p;
        *g = q;
        *b = v;
        break;
    case 4:
        *r = t;
        *g = p;
        *b = v;
        break;
    case 5:
    default:
        *r = v;
        *g = p;
        *b = q;
        break;
    }
    return;     
}
/**
 * convert rgb to hsv
 */
void rgb2hsv(float r, float g, float b, float *h, float *s, float *v)
{
    float min,max,delta;

    min = r < g ? r : g;
    min = min  < b ? min  : b;

    max = r > g ? r : g;
    max = max  > b ? max  : b;

    *v = max;                                // v
    delta = max - min;
    if (delta < 0.00001)
    {
        *s = 0;
        *h = 0; // undefined, maybe nan?
        return;
    }
    if( max > 0.0 ) { 
        *s = (delta / max);                  // s
    } else {
        // if max is 0, then r = g = b = 0              
        // s = 0, v is undefined
        *s = 0.0;
        *h = NAN;                            // its now undefined
        return;
    }
    if( r >= max )                    
        *h = ( g - b ) / delta;        // between yellow & magenta
    else
    if( g >= max )
        *h = 2.0 + ( b - r ) / delta;  // between cyan & yellow
    else
        *h = 4.0 + ( r - g ) / delta;  // between magenta & cyan

    *h *= 60.0;                        // degrees

    if( *h < 0.0 )
        *h += 360.0;

    return;
}

/*
  free image data in image
*/
void freeimage(IMAGE *img) {
   free(img->data_rh);
   free(img->data_gs);
   free(img->data_bv);
   img->nx=0;
   img->ny=0;
}
