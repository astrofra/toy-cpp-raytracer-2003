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

		// pixel filtering
		void			filterBoxBlur(int);
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