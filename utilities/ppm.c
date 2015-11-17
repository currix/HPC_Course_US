#include <stdlib.h>
#include <stdio.h>
#include "ppm.h"
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
    img->imagedata = malloc(img->nx*img->ny*sizeof(RGB));
    if (!img->imagedata) {
       fprintf(stderr, "Unable to allocate image data\n");
       exit(1);
    } 
    for (i=0;i<img->ny;i++) {
      for (j=0;j<img->nx;j++) {
        img->imagedata[i*img->nx+j].r=i % 256;
        img->imagedata[i*img->nx+j].g=j % 256;
        img->imagedata[i*img->nx+j].b=i*j % 256;
      }
    }
    return img;
}
/*
  read an image from file
*/
IMAGE *readimage(char *filename) {
    IMAGE *img;
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
    char buff[16];
    if (!fgets(buff, sizeof(buff), fp)) {
       perror(filename);
       exit(1);
    }
    if (buff[0] != 'P' || buff[1] != '6') {
         fprintf(stderr, "Invalid image format %c%c\n",buff[0],buff[1]);
         exit(1);
    }
    if (fscanf(fp, "%d %d", &img->nx, &img->ny) != 2) {
         fprintf(stderr, "Invalid image size ('%s')\n", filename);
         exit(1);
    }
    if ((fscanf(fp, "%d", &depth) != 1) || (depth!=255)) {
         fprintf(stderr, "Invalid rgb component ('%s')\n", filename);
         exit(1);
    }
    while (fgetc(fp) != '\n') ;
    img->imagedata = malloc(img->nx*img->ny*sizeof(RGB));
    
    if (!img->imagedata) {
       fprintf(stderr, "Unable to allocate image data\n");
       exit(1);
    } 

    if (fread(img->imagedata, 3 * img->nx, img->ny, fp) != img->ny) {
         fprintf(stderr, "Invalid image data ('%s')\n", filename);
         exit(1);
    }
    fclose(fp);
    return img;
}
/*
  save image to file
*/
void saveimage(const IMAGE *img, char *filename) {
    //int i,j;
    FILE *fp = fopen(filename, "wb"); 
    fprintf(fp, "P6\n%d %d\n255\n", img->nx,img->ny);
    fwrite(img->imagedata, 3 * img->nx, img->ny, fp);
    fclose(fp);
}
/*
  free image data in image
*/
void freeimage(IMAGE *img) {
   free(img->imagedata);
   img->imagedata=0;
   img->nx=0;
   img->ny=0;
}
