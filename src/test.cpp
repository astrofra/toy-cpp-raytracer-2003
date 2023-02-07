// test.c

#include <stdio.h>

#include "gfxBuffer.h"
#include "trace.h"
#include "test.h"
#include "itemList.h"

//----------------------
void	linkedListTest()
//----------------------
{
	int			i;
	char		str[1024];	
	itemList	buffer_list;
//	item		*tmp;
	gfxBuffer	*temp_buffer;

	// List items creation
	for(i = 1; i <= 16; i++)
	{
		temp_buffer	= new gfxBuffer(i * 40, i * 30);
		buffer_list.insertItem(temp_buffer);
		fillBuffer(temp_buffer, i * 128);
	}


	i = 0;
	buffer_list.gotoListHead();
	while(buffer_list.gotoNextItem())
	{
		sprintf(str, "J:\\temp\\out_%i.tga", i + 10);

		temp_buffer = (gfxBuffer *)buffer_list.getContent();
		temp_buffer->saveBuffer(str);
		i++;
	}

	
	while(buffer_list.gotoPrevItem())
	{
		i--;
		sprintf(str, "J:\\temp\\out_reverse_%i.tga", i + 10);

		temp_buffer = (gfxBuffer *)buffer_list.getContent();
		temp_buffer->saveBuffer(str);
	}


}

//------------------
void	fillBuffer(gfxBuffer *graphic_buffer, int fill_seed)
//------------------
{
	rgba_pixel pixel;
	int	x,y, size_x, size_y;

	size_x = graphic_buffer->getBufferSizeX(), 
	size_y = graphic_buffer->getBufferSizeY();

	//graphic_buffer = new gfxBuffer(RENDER_BUFFER_SIZE_X, RENDER_BUFFER_SIZE_Y);
	// Fill Buffer

	for(y = 0; y < size_y; y++)
	{
		for(x = 0; x < size_x; x++)
		{
			pixel.redValue = (unsigned char)(fill_seed + (y * 255) / size_y);
			pixel.greenValue = (unsigned char)(fill_seed + (x * y * 255) / (size_x * size_y));
			pixel.blueValue = (unsigned char)(fill_seed + (x * 255) / size_x);
			pixel.alphaValue = 255;
			graphic_buffer->putRGBAPixel(x,y, pixel);
		}
	}

	//graphic_buffer->saveBuffer("f:\\out.tga");

	//delete graphic_buffer;
}