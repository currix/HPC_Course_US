#include "ppm_soa.h"

int main(void)
{
  // make and save
  IMAGE *img=makeimage(500,800);
  saveimage(img,"image3.ppm");
  freeimage(img);
  // read and save
  img=readimage("image3.ppm");
  image2hsv(img);
  saveimage(img,"image3c.ppm");
  return 0;
}
