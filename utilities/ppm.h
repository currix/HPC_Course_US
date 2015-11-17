typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} RGB;

typedef struct {
    int nx;
    int ny;
    RGB *imagedata;
} IMAGE;

IMAGE *makeimage(int nx, int ny);
IMAGE *readimage(char *filename);
void saveimage(const IMAGE *img, char *filename);
void freeimage(IMAGE *img);
