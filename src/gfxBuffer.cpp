#include <memory.h>
#include <string>
#include <stdio.h>

#include "gfxBuffer.h"

//--------------------
gfxBuffer::gfxBuffer(int req_size_x,int req_size_y)
//--------------------
{	
	size_x = req_size_x;
	size_y = req_size_y;
	buffer = new rgba_pixel[size_x * size_y];
}

//--------------------
gfxBuffer::~gfxBuffer()
//--------------------
{

	if (buffer)	delete []buffer;
}

//----------------------------------------------------
rgba_pixel *gfxBuffer::getRGBAPixelPointer(int x, int y)
//----------------------------------------------------
{
	return (&buffer[x + y * size_x]);
}

//-----------------------------------------------------------
void	gfxBuffer::putRGBAPixel(int x, int y, rgba_pixel pixel)
//-----------------------------------------------------------
{
	rgba_pixel *tmp;
	tmp = getRGBAPixelPointer(x,y);

	tmp->redValue = pixel.redValue;
	tmp->greenValue = pixel.greenValue;
	tmp->blueValue = pixel.blueValue;
	tmp->alphaValue = pixel.alphaValue;
}

//----------------------------------------------
rgba_pixel	gfxBuffer::getRGBAPixel(int x, int y)
//----------------------------------------------
{
	rgba_pixel pixel;
	rgba_pixel *tmp;
	tmp = getRGBAPixelPointer(x,y);

	pixel.redValue = tmp->redValue;
	pixel.greenValue = tmp->greenValue;
	pixel.blueValue = tmp->blueValue;

	return (pixel);
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

//------------------------------------
int gfxBuffer::saveBuffer(char *fname)
//------------------------------------
{
	FILE *fp;
	tga_header *header;
	//int	tmp = 64;

	fp = fopen( fname, "wb" );

	if( !fp )
	{
	   printf("file open error on %s.\n", fname );
	   return GFXBUFFER_ERROR_BASIC;
	}

	// Create file header
	header = new tga_header;

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
	fwrite( header, sizeof( tga_header ), 1, fp );
	// Write down whole rgba buffer 
	fwrite( buffer, getBufferSizeX() * getBufferSizeY() * GFXBUFFER_DEPTH_RGB32, 1, fp );

	// Clear stuff
	fclose( fp );

	delete header;

	return GFXBUFFER_NO_ERROR;
}
