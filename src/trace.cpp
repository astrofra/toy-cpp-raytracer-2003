// Trace.cpp 
//

#undef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN

#include <stdio.h>

#include "trace.h"
#include "gfxBuffer.h"

#define		RENDER_BUFFER_SIZE_X	800
#define		RENDER_BUFFER_SIZE_Y	600

// #include "gfxBuffer.h"

int main(int argc, char* argv[])
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
			pixel.redValue = (y * 255) / RENDER_BUFFER_SIZE_Y;
			pixel.greenValue = (x * y * 255) / (RENDER_BUFFER_SIZE_X * RENDER_BUFFER_SIZE_Y);
			pixel.blueValue = (x * 255) / RENDER_BUFFER_SIZE_X;
			pixel.alphaValue = 255;
			graphic_buffer->putRGBAPixel(x,y, pixel);
		}
	}

	graphic_buffer->saveBuffer("c:\\out.tga");

	delete graphic_buffer;

	return 0;
}

