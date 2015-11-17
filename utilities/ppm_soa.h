/**
 * Image format in SoA (structure of arrays) format
 * A color can be expressed as a rgb or as a hsv triplet, each value
 * being a float value in the image structure.
 *
 * The file format itself is standard PPM in RGB (24bit), so 
 * information is lost on saving!
 */

typedef enum {TYPE_RGB,TYPE_HSV} CSPACE;  // image type

typedef struct {
    int nx;              // width
    int ny;              // height
    float *data_rh;      // array with red / hue values
    float *data_gs;      // array with green / saturation values
    float *data_bv;      // array with blue / value values
    CSPACE cspace;
} IMAGE;

// create a hsv image with given dimensions (and some calculated pattern)
IMAGE *makeimage(int nx, int ny);

// read a rgb image from file
IMAGE *readimage(char *filename); 

// save image to file (converts output pixels to rgb if necessary)
void saveimage(const IMAGE *img, char *filename);

// convert image to hsv
void image2hsv(IMAGE *img);

// free image data in image
void freeimage(IMAGE *img);
