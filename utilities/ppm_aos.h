/**
 * Image format in AoS (array of structure) format
 * A color can be expressed as a rgb triplet, each value
 * being a float value in the image structure.
 *
 * The file format itself is standard PPM in RGB (24bit), so
 * information is lost on saving!
 */

typedef struct {
    float r;
    float g;
    float b;
} RGBFLOAT;

typedef struct {
    int nx;
    int ny;
    RGBFLOAT *data;
} IMAGE;

IMAGE *makeimage(int nx, int ny);
IMAGE *readimage(char *filename); 
void saveimage(const IMAGE *img, char *filename);
void freeimage(IMAGE *img);
