// test.c

#include "gfxBuffer.h"
#include "trace.h"
#include "test.h"

//------------------
void	bufferTest()
//------------------
{
	gfxBuffer *graphic_buffer;
	rgba_pixel pixel;
	int	x,y;

	graphic_buffer = new gfxBuffer(RENDER_BUFFER_SIZE_X, RENDER_BUFFER_SIZE_Y);

	// Fill Buffer
	for(y = 0; y < RENDER_BUFFER_SIZE_Y; y++)
	{
		for(x = 0; x < RENDER_BUFFER_SIZE_X; x++)
		{
			pixel.redValue = (unsigned char)((y * 255) / RENDER_BUFFER_SIZE_Y);
			pixel.greenValue = (unsigned char)((x * y * 255) / (RENDER_BUFFER_SIZE_X * RENDER_BUFFER_SIZE_Y));
			pixel.blueValue = (unsigned char)((x * 255) / RENDER_BUFFER_SIZE_X);
			pixel.alphaValue = 255;
			graphic_buffer->putRGBAPixel(x,y, pixel);
		}
	}

	graphic_buffer->saveBuffer("f:\\out.tga");

	delete graphic_buffer;
}