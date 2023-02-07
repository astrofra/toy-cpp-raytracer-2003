#include "tools.h"

#ifndef	GFXBUFFER
#define	GFXBUFFER

#define	GFXBUFFER_ERROR		0
#define	GFXBUFFER_NO_ERROR	1

#define	GFXBUFFER_DEPTH_RGB32	4

#define	GFXBUFFER_MAX_BLUR_RADIUS	64

//-------- pixels ------------------------

struct ldr_pixel
{
	unsigned char	redValue;
	unsigned char	greenValue;
	unsigned char	blueValue;
	unsigned char	alphaValue;
};

struct hdr_pixel
{
	float	redValue;
	float	greenValue;
	float	blueValue;
	float	alphaValue;
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

		void			putHdrPixel(int, int, hdr_pixel *);
		hdr_pixel		getHdrPixel(int, int);

		gfxBuffer		operator+= (gfxBuffer *);
		gfxBuffer		operator+= (hdr_pixel);
		gfxBuffer		operator*= (gfxBuffer *);
		gfxBuffer		operator*= (hdr_pixel);

		// buffer filtering
		void			filterBoxBlur(int); // blur_radius
		void			filterBloom(float, int); // bloom_threshold, bloom_radius
		void			filterInvertRGB();
		void			filterInvertAlpha();

		// file in/out
		int				saveFileTarga(char *);
		int				loadFileTarga(char *);

	private:
		hdr_pixel		*buffer;
		int				size_x, size_y;

		hdr_pixel		*getHdrPixelPointer(int , int );

};

#endif