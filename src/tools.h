// tools.h
#include <stdlib.h>

#ifndef COMMON_TOOLS
#define COMMON_TOOLS

#define	MIN_VALUE(V, MIN_VAL) (V < MIN_VAL ? MIN_VAL : V)
#define	MAX_VALUE(V, MAX_VAL) (V > MAX_VAL ? MAX_VAL : V)
#define	BOUND_VALUE(V, MIN_VAL, MAX_VAL) (MAX_VALUE(MIN_VALUE(V, MIN_VAL), MAX_VAL))

#define RAND(A)	(rand()%1000 / 1000.0f) * (A)

struct targa_header
{
    unsigned char  identsize;			// size of ID field that follows 18 byte header (0 usually)
    unsigned char  colourmaptype;		// type of colour map 0=none, 1=has palette
    unsigned char  imagetype;			// type of image 0=none,1=indexed,2=rgb,3=grey,+8=rle packed

	unsigned char  pad[5];

    unsigned short xstart;				// image x origin
    unsigned short ystart;				// image y origin
    unsigned short width;				// image width in pixels
    unsigned short height;				// image height in pixels
    unsigned char  bits;				// image bits per pixel 8,16,24,32
    unsigned char  descriptor;			// image descriptor bits (vh flip bits)

};

unsigned char	floatToUnsignedChar(float);

float			unsignedCharToFloat(unsigned char);

#endif