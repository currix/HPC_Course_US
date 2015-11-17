#ifdef USE_DOUBLE
#define REAL double
#else
#define REAL float
#endif

#define ARRAY_SIZE 64
/**
 * Our data structure
 */
struct
{
   char pad1;
   REAL va[ARRAY_SIZE];
   char pad2;
   REAL vb[ARRAY_SIZE];
   char pad3;
} data;

