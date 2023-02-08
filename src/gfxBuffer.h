// #include "tools.h"
#include "math.h"

#ifndef	GFXBUFFER
#define	GFXBUFFER

#define	GFXBUFFER_ERROR		0
#define	GFXBUFFER_NO_ERROR	1

#define	GFXBUFFER_DEPTH_RGB32	4

#define	GFXBUFFER_MAX_BLUR_RADIUS	64

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

//-------- colors ------------------------

struct rgba
{
public:
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;
};

//-------- gfxBuffer ------------------------

class	gfxBuffer
{
	public:
		gfxBuffer();
		gfxBuffer(int, int);
		~gfxBuffer();

		// general handling
		int				isEmpty();
		int				getBufferSizeX();
		int				getBufferSizeY();

		gfxBuffer		*duplicateBuffer();

		void			putPixel(int, int, Rcolor&);
		Rcolor			getPixel(int, int);

		gfxBuffer		operator+= (gfxBuffer&);
		gfxBuffer		operator+= (Rcolor&);
		gfxBuffer		operator*= (gfxBuffer&);
		gfxBuffer		operator*= (Rcolor&);

		// buffer filtering
		void			filterBoxBlur(int); // blur_radius
		void			filterBloom(float, int); // bloom_threshold, bloom_radius
		void			filterInvertRGB();
		void			filterInvertAlpha();

		// file in/out
		int				saveFileTarga(char *);
		int				loadFileTarga(char *);

	private:
		Rcolor			*buffer;
		int				size_x, size_y;

		Rcolor			*getPixelPointer(int , int );

};

#endif