#include <stdlib.h>
#include <stdio.h>
#include "ppm_aos.h"
#define COLORS 255

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} RGB;

/*
  create an image with given dimensions (and some calculated pattern)
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
    img->data = malloc(img->nx*img->ny*sizeof(RGBFLOAT));
    if (!img->data) {
       fprintf(stderr, "Unable to allocate image data\n");
       exit(1);
    } 
    for (i=0;i<img->ny;i++) {
      for (j=0;j<img->nx;j++) {
        img->data[i*img->nx+j].r = (float) (i % 256);
        img->data[i*img->nx+j].g = (float) (j % 256);
        img->data[i*img->nx+j].b = (float) (i*j % 256);
      }
    }
    return img;
}
/*
  read an image from file
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

    img->data = malloc(img->nx*img->ny*sizeof(RGBFLOAT));
    if (!img->data) {
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
      img->data[i].r = (float) prgb[i].r*fact;
      img->data[i].g = (float) prgb[i].g*fact;
      img->data[i].b = (float) prgb[i].b*fact;
    }
    free (prgb);
    fclose(fp);
    return img;
}
/*
  save image to file
*/
void saveimage(const IMAGE *img, char *filename) {
    int i;
    FILE *fp = fopen(filename, "wb"); 
    fprintf(fp, "P6\n%d %d\n255\n", img->nx,img->ny);
    
    RGB *prgb = 
      (RGB *) malloc(img->nx * img->ny * sizeof(RGB));
    if (!prgb) {
       fprintf(stderr, "Unable to allocate rgb buffer\n");
       exit(1);
    } 

    for (i=0; i< img->nx*img->ny; i++) {
      prgb[i].r = (int) (img->data[i].r*COLORS);
      prgb[i].g = (int) (img->data[i].g*COLORS);
      prgb[i].b = (int) (img->data[i].b*COLORS);
    }
    fwrite(prgb, 3 * img->nx, img->ny, fp);
    free(prgb);
    fclose(fp);
}
/*
  free image data in image
*/
void freeimage(IMAGE *img) {
   free(img->data);
   img->data=0;
   img->nx=0;
   img->ny=0;
}
