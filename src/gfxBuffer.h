#include "tools.h"

#ifndef	GFXBUFFER
#define	GFXBUFFER

#define	GFXBUFFER_ERROR		0
#define	GFXBUFFER_NO_ERROR	1

#define	GFXBUFFER_DEPTH_RGB32	4

#define	GFXBUFFER_MAX_BLUR_RADIUS	64

//-------- colors ------------------------

class Ccolor_4c
{
public:
	unsigned char	redValue;
	unsigned char	greenValue;
	unsigned char	blueValue;
	unsigned char	alphaValue;
};

class Ccolor_4f
{
public:
	Ccolor_4f();
	Ccolor_4f(float );
	Ccolor_4f(float ,float ,float);
	Ccolor_4f(float ,float ,float, float);

	~Ccolor_4f();

	Ccolor_4f		operator+= (Ccolor_4f&);
	Ccolor_4f		operator-= (Ccolor_4f&);
	Ccolor_4f		operator*= (Ccolor_4f&);

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

		void			putPixel(int, int, Ccolor_4f&);
		Ccolor_4f		getPixel(int, int);

		gfxBuffer		operator+= (gfxBuffer&);
		gfxBuffer		operator+= (Ccolor_4f&);
		gfxBuffer		operator*= (gfxBuffer&);
		gfxBuffer		operator*= (Ccolor_4f&);

		// buffer filtering
		void			filterBoxBlur(int); // blur_radius
		void			filterBloom(float, int); // bloom_threshold, bloom_radius
		void			filterInvertRGB();
		void			filterInvertAlpha();

		// file in/out
		int				saveFileTarga(char *);
		int				loadFileTarga(char *);

	private:
		Ccolor_4f		*buffer;
		int				size_x, size_y;

		Ccolor_4f		*getPixelPointer(int , int );

};

#endif