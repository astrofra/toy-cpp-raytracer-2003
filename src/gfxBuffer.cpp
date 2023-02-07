#include <memory.h>
#include <string>
#include <stdio.h>

#include "gfxBuffer.h"
#include "tools.h"

//--------------------
gfxBuffer::gfxBuffer()
//--------------------
{	
	size_x = -1;
	size_y = -1;
	buffer = 0;
}

//--------------------
gfxBuffer::gfxBuffer(int req_size_x,int req_size_y)
//--------------------
{	
	size_x = req_size_x;
	size_y = req_size_y;
	buffer = new hdr_pixel[size_x * size_y];
}

//--------------------
gfxBuffer::~gfxBuffer()
//--------------------
{

	if (buffer)	delete []buffer;
}

//----------------------------------------------------
inline hdr_pixel *gfxBuffer::getHdrPixelPointer(int x, int y)
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
void	gfxBuffer::putHdrPixel(int x, int y, hdr_pixel *pixel)
//-----------------------------------------------------------
{
	hdr_pixel *tmp;
	tmp = getHdrPixelPointer(x,y);

	tmp->redValue = pixel->redValue;
	tmp->greenValue = pixel->greenValue;
	tmp->blueValue = pixel->blueValue;
	tmp->alphaValue = pixel->alphaValue;
}

//----------------------------------------------
hdr_pixel	gfxBuffer::getHdrPixel(int x, int y)
//----------------------------------------------
{
	hdr_pixel pixel;
	hdr_pixel *tmp;
	tmp = getHdrPixelPointer(x,y);

	pixel.redValue = tmp->redValue;
	pixel.greenValue = tmp->greenValue;
	pixel.blueValue = tmp->blueValue;
	pixel.alphaValue = tmp->alphaValue;

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
	memcpy(temp_buffer->buffer, buffer, sizeof(hdr_pixel) * size_x * size_y);
	
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
	hdr_pixel	read_pixel, blured_pixel;
	gfxBuffer	*temp_buffer;

	if (blur_radius > GFXBUFFER_MAX_BLUR_RADIUS)
	{
		printf("gfxBuffer::filterGaussianBlur : MAX_BLUR_RADIUS exceeded\n");
		blur_radius = GFXBUFFER_MAX_BLUR_RADIUS;
	}

	// create temp buffer as un-blured reference
	temp_buffer = duplicateBuffer();

	blur_weight = (float)(1.0f / (4.0f * (float)blur_radius * (float)blur_radius));

	printf("gfxBuffer::filterBoxBlur : blur_radius = %i, blur_weight = %f.\n", blur_radius, blur_weight);

	// image loop
	for (y = 0; y < size_y; y++)
	{
		for(x = 0; x < size_x; x++)
		{
			// clear blured pixel
			memset(&blured_pixel,0,sizeof(hdr_pixel));

			// BoxBlur loop
			for (kernel_y = y - blur_radius; kernel_y < y + blur_radius; kernel_y++)
			{
				bounded_y = BOUND_VALUE(kernel_y, 0, size_y - 1);
				for (kernel_x = x - blur_radius; kernel_x < x + blur_radius; kernel_x++)
				{
					bounded_x = BOUND_VALUE(kernel_x, 0, size_x - 1);
					read_pixel = temp_buffer->getHdrPixel(bounded_x, bounded_y);

					blured_pixel.redValue	+=	read_pixel.redValue * blur_weight;
					blured_pixel.greenValue	+=	read_pixel.greenValue * blur_weight;
					blured_pixel.blueValue	+=	read_pixel.blueValue * blur_weight;
					blured_pixel.alphaValue	+=	read_pixel.alphaValue * blur_weight;
				}
			}
			// loop end, write down blured pixel
			putHdrPixel( x, y, &blured_pixel);
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
	ldr_pixel	*ldr_buffer, *ldr_pt;
	hdr_pixel	*hdr_pt;
	int	x,y;

	// prepare 32bits int. buffer
	ldr_buffer = new ldr_pixel[size_x * size_y];

	//copy hdr buffer to ldr buffer
	for(y = 0; y < size_y; y++)
	{
		for (x = 0; x < size_x; x++)
		{
			ldr_pt = &ldr_buffer[x + y * size_x];
			hdr_pt = getHdrPixelPointer(x,y);
			ldr_pt->redValue	=	floatToUnsignedChar( hdr_pt->redValue );
			ldr_pt->greenValue	=	floatToUnsignedChar( hdr_pt->greenValue );
			ldr_pt->blueValue	=	floatToUnsignedChar( hdr_pt->blueValue );
			ldr_pt->alphaValue	=	floatToUnsignedChar( hdr_pt->alphaValue );
		}
	}

	fp = fopen( fname, "wb" );

	if( !fp )
	{
	   printf("gfxBuffer::saveFileTarga : file open error on %s.\n", fname );
	   return GFXBUFFER_ERROR;
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
	fclose( fp );

	delete header;
	delete []ldr_buffer;

	return GFXBUFFER_NO_ERROR;
}


//------------------------------------
int gfxBuffer::loadFileTarga(char *fname)
//------------------------------------
{

	FILE *fp;
	targa_header *header;
	ldr_pixel	*ldr_buffer, *ldr_pt;
	hdr_pixel	*hdr_pt;
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
	ldr_buffer = new ldr_pixel[size_x * size_y];

	// allocate the main hdr buffer
	buffer = new hdr_pixel[size_x * size_y],

	// get image datas
	fread(ldr_buffer, size_x * size_y * GFXBUFFER_DEPTH_RGB32, 1, fp );

	//copy ldr buffer to hdr buffer
	for(y = 0; y < size_y; y++)
	{
		for (x = 0; x < size_x; x++)
		{
			ldr_pt = &ldr_buffer[x + y * size_x];
			hdr_pt = getHdrPixelPointer(x,y);

			hdr_pt->redValue	=	unsignedCharToFloat( ldr_pt->redValue );
			hdr_pt->greenValue	=	unsignedCharToFloat( ldr_pt->greenValue );
			hdr_pt->blueValue	=	unsignedCharToFloat( ldr_pt->blueValue );
			hdr_pt->alphaValue	=	unsignedCharToFloat( ldr_pt->alphaValue );
		}
	}

	// Clear stuff
	fclose( fp );

	delete header;
	delete []ldr_buffer;

	return GFXBUFFER_NO_ERROR;
}
