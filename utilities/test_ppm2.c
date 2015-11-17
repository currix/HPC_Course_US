#include "ppm_aos.h"

int main(void)
{
  // make and save
  IMAGE *img=makeimage(500,800);
  saveimage(img,"image2.ppm");
  freeimage(img);
  // read and save
  img=readimage("image2.ppm");
  saveimage(img,"image2c.ppm");
  return 0;
}
