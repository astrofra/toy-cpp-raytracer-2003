#include <memory.h>
#include <string>
#include <stdio.h>

#include "gfxBuffer.h"
#include "math.h"

//-------- gfxBuffer ------------------------

//--------------------
gfxBuffer::gfxBuffer()
//--------------------
{	
	size_x	= 0;
	size_y	= 0;
	buffer	= 0;
}

//--------------------
gfxBuffer::gfxBuffer(int req_size_x,int req_size_y)
//--------------------
{	
	size_x = req_size_x;
	size_y = req_size_y;
	buffer = new Rcolor[size_x * size_y];
}

//--------------------
gfxBuffer::~gfxBuffer()
//--------------------
{

	if (buffer)	delete []buffer;
}

//----------------------------------------------------
inline Rcolor *gfxBuffer::getPixelPointer(int x, int y)
//----------------------------------------------------
{
	return (&buffer[x + y * size_x]);
}


//-----------------------------
int gfxBuffer::getBufferSizeX()
//-----------------------------
{
	return (size_x);
}

//-----------------------------
int gfxBuffer::getBufferSizeY()
//-----------------------------
{
	return (size_y);
}

//----------------------
int	gfxBuffer::isEmpty()
//----------------------
{
	if (buffer == 0)
		return 1;
	else
		return 0;
}


//-----------------------------------------------------------
void	gfxBuffer::putPixel(int x, int y, Rcolor pixel)
//-----------------------------------------------------------
{
	Rcolor *tmp;
	tmp = getPixelPointer(x,y);

	tmp->r	= pixel.r;
	tmp->g	= pixel.g;
	tmp->b	= pixel.b;
	// tmp->alpha	= pixel.alpha;
}

//----------------------------------------------
Rcolor	gfxBuffer::getPixel(int x, int y)
//----------------------------------------------
{
	Rcolor pixel;
	Rcolor *tmp;
	tmp = getPixelPointer(x,y);

	pixel.r	= tmp->r;
	pixel.g	= tmp->g;
	pixel.b	= tmp->b;
	//pixel.alpha	= tmp->alpha;

	return (pixel);
}

//---------------------------------------
gfxBuffer	*gfxBuffer::duplicateBuffer()
//---------------------------------------
{
	gfxBuffer	*temp_buffer;

	// create blank buffer
	temp_buffer = new gfxBuffer(size_x, size_y);

	// copy buffer datas 
	memcpy(temp_buffer->buffer, buffer, sizeof(Rcolor) * size_x * size_y);
	
	temp_buffer->size_x = getBufferSizeX();
	temp_buffer->size_y = getBufferSizeY();

	return (temp_buffer);
}

//----------------------------------------------------
void	gfxBuffer::filterBoxBlur(int blur_radius)
//----------------------------------------------------
{
	int			x,y;
	int			kernel_x, kernel_y, bounded_x, bounded_y;
	float		blur_weight;
	Rcolor	read_pixel, blur_pixel;
	gfxBuffer	*temp_buffer;

	// create temp buffer as un-blur reference
	temp_buffer = duplicateBuffer();

	if (blur_radius <=0)
		return;

	if (blur_radius > GFXBUFFER_MAX_BLUR_RADIUS)
	{
		printf("gfxBuffer::filterBoxBlur : MAX_BLUR_RADIUS exceeded\n");
		blur_radius = GFXBUFFER_MAX_BLUR_RADIUS;
	}

	blur_weight = (float)(1.0f / (4.0f * (float)blur_radius * (float)blur_radius));
	printf("gfxBuffer::filterBoxBlur : blur_radius = %i, blur_weight = %f.\n", blur_radius, blur_weight);

	// image loop
	for (y = 0; y < size_y; y++)
	{
		for(x = 0; x < size_x; x++)
		{
			// clear blur pixel
			memset(&blur_pixel,0,sizeof(Rcolor));

			// BoxBlur loop
			for (kernel_y = y - blur_radius; kernel_y < y + blur_radius; kernel_y++)
			{
				bounded_y = BOUND_VALUE(kernel_y, 0, size_y - 1);
				for (kernel_x = x - blur_radius; kernel_x < x + blur_radius; kernel_x++)
				{
					bounded_x = BOUND_VALUE(kernel_x, 0, size_x - 1);
					read_pixel = temp_buffer->getPixel(bounded_x, bounded_y);

					blur_pixel.r	+=	read_pixel.r * blur_weight;
					blur_pixel.g	+=	read_pixel.g * blur_weight;
					blur_pixel.b	+=	read_pixel.b * blur_weight;
					//blur_pixel.alpha	+=	read_pixel.alpha * blur_weight;
				}
			}
			// loop end, write down blur pixel
			putPixel( x, y, blur_pixel);
		}
		//printf("gfxBuffer::filterGaussianBlur : line %i done.\n",y);
	}
	// image end
	
	// delete temp buffer
	delete temp_buffer;
	

}

//------------------------------------
int gfxBuffer::saveFileTarga(char *fname)
//------------------------------------
{
	FILE *fp;
	targa_header *header;
	rgba	*ldr_buffer, *ldr_pt;
	Rcolor	*hdr_pt;
	int	x,y;

	// prepare 32bits int. buffer
	ldr_buffer = new rgba[getBufferSizeX() * getBufferSizeY()];

	if (ldr_buffer == 0)
	{
		printf("gfxBuffer::saveFileTarga : Cannot allocate RGBA buffer\n");
		return (GFXBUFFER_ERROR);
	}

	//copy hdr buffer to ldr buffer
	for(y = 0; y < size_y; y++)
	{
		for (x = 0; x < size_x; x++)
		{
			ldr_pt = &ldr_buffer[x + y * size_x];
			hdr_pt = getPixelPointer(x,y);
			ldr_pt->r	=	floatToUnsignedChar( hdr_pt->r );
			ldr_pt->g	=	floatToUnsignedChar( hdr_pt->g );
			ldr_pt->b	=	floatToUnsignedChar( hdr_pt->b );
			ldr_pt->a	=	1.0;
		}
	}

	fp = fopen( fname, "wb" );

	if( !fp )
	{
	   printf("gfxBuffer::saveFileTarga : file open error on %s.\n", fname );
	   return (GFXBUFFER_ERROR);
	}

	// Create file header
	header = new targa_header;

	// Feed file header
	header->identsize		= 0;
	header->colourmaptype	= 0;
	header->imagetype		= 2;
	
	memset(header->pad,0,5);

	header->xstart			= 0;
	header->ystart			= 0;
	header->width			= getBufferSizeX();
	header->height			= getBufferSizeY();
	header->bits			= 2 << GFXBUFFER_DEPTH_RGB32;
	header->descriptor		= 0;

	// Write down file header
	fwrite( header, sizeof( targa_header ), 1, fp );
	// Write down whole rgba buffer 
	fwrite(ldr_buffer, size_x * size_y * GFXBUFFER_DEPTH_RGB32, 1, fp );

	// Clear stuff
	//fclose( fp );

	delete header;
	delete []ldr_buffer;
	//free(ldr_buffer);

	return GFXBUFFER_NO_ERROR;
}


//------------------------------------
int gfxBuffer::loadFileTarga(char *fname)
//------------------------------------
{

	FILE *fp;
	targa_header *header;
	rgba	*ldr_buffer, *ldr_pt;
	Rcolor	*hdr_pt;
	int	x,y;

	// open the targa file
	fp = fopen( fname, "rb" );

	if( !fp )
	{
	   printf("File open error on %s.\n", fname );
	   return GFXBUFFER_ERROR;
	}

	// Create file header
	header = new targa_header;

	// get the file header
	fread( header, sizeof( targa_header ), 1, fp );

	// check Targa RGBA format
	header->imagetype		= 2;

	if (header->imagetype != 2)
	{
		printf("gfxBuffer::loadFileTarga : Cannot handle targa file % as it appears to be in wrong type.\n", fname);
		return GFXBUFFER_ERROR;
	}

	if (header->bits != (2 << GFXBUFFER_DEPTH_RGB32))
	{
		printf("gfxBuffer::loadFileTarga : Cannot handle targa file %s as it appears to be %i bits encoded.\n", fname, header->bits );
		return GFXBUFFER_ERROR;
	}

	// get & check image dimensions (x / y)
	size_x = header->width;
	size_y = header->height;

	if (size_x <= 0 || size_y <= 0)
	{
		printf("gfxBuffer::loadFileTarga : Targa file % : wrong image size.\n", fname);
		return GFXBUFFER_ERROR;
	}
	
	// allocate a 32bits int. buffer
	ldr_buffer = new rgba[size_x * size_y];

	// allocate the main hdr buffer
	buffer = new Rcolor[size_x * size_y],

	// get image datas
	fread(ldr_buffer, size_x * size_y * GFXBUFFER_DEPTH_RGB32, 1, fp );

	//copy ldr buffer to hdr buffer
	for(y = 0; y < size_y; y++)
	{
		for (x = 0; x < size_x; x++)
		{
			ldr_pt = &ldr_buffer[x + y * size_x];
			hdr_pt = getPixelPointer(x,y);

			hdr_pt->r	=	unsignedCharToFloat( ldr_pt->r );
			hdr_pt->g	=	unsignedCharToFloat( ldr_pt->g );
			hdr_pt->b	=	unsignedCharToFloat( ldr_pt->b );
			// hdr_pt->alpha	=	unsignedCharToFloat( ldr_pt->alpha );
		}
	}

	// Clear stuff
	fclose( fp );

	delete header;
	delete []ldr_buffer;

	return GFXBUFFER_NO_ERROR;
}
