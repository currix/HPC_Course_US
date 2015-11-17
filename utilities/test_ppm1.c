#include "ppm.h"

int main(void) {

  // make an image and save
  IMAGE *img=makeimage(500,800);
  saveimage(img,"image1.ppm");
  // free image memory
  freeimage(img);
  // read and save
  img=readimage("image1.ppm");
  saveimage(img,"image1c.ppm");
  return 0;
}
