#ifndef	GFXBUFFER
#define	GFXBUFFER

#define	GFXBUFFER_ERROR_BASIC	0
#define	GFXBUFFER_NO_ERROR	1

#define	GFXBUFFER_DEPTH_RGB32	4

struct tga_header
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

struct rgba_pixel
{
	unsigned char	redValue;
	unsigned char	greenValue;
	unsigned char	blueValue;
	unsigned char	alphaValue;
};

/*
class pixel
{
public:
	float	redValue:
	float	greenValue;
	float	blueValue;
	float	alphaValue;

	pixel();
	pixel(float, float, float);
 	pixel(float, float, float, float);
	~pixel();

	//	class friend gfxBuffer;
}
*/

class	gfxBuffer
{
	public:
		gfxBuffer(int, int);
		~gfxBuffer();

		rgba_pixel		*getRGBAPixelPointer(int , int );
		void			putRGBAPixel(int, int, rgba_pixel);
		rgba_pixel		getRGBAPixel(int, int);

		int				getBufferSizeX();
		int				getBufferSizeY();

		int				saveBuffer(char *);

	private:
		rgba_pixel		*buffer;
		int				size_x, size_y;

};

#endif