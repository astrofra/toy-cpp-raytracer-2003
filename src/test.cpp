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
	itemList	*buffer_list;
	item		*tmp;
	gfxBuffer	*temp_buffer;

	// List instance creation
	buffer_list = new itemList();

	// List items creation
	for(i = 0; i < 15; i++)
	{
		temp_buffer	= new gfxBuffer(i * 40, i * 30);
		buffer_list->insertItem(temp_buffer);
		fillBuffer(temp_buffer, i * 128);
	}

	tmp = buffer_list->getFirstItem();

	i = 0;
	while(true)
	{
		sprintf(str, "f:\\\\out_%i.tga", i + 10);
		temp_buffer = (gfxBuffer *)tmp->content;
		temp_buffer->saveBuffer(str);

		tmp = tmp->next;
		i++;
		if (tmp->next == 0) break;
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