// Trace.cpp 
//

#undef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN

#include <memory.h>
#include <stdio.h>
#include <math.h>

#include "trace.h"
#include "itemList.h"
#include "gfxBuffer.h"
#include "test.h"
#include "tools.h"

// #include "gfxBuffer.h"

//------------------------------
int main(int argc, char* argv[])
//------------------------------
{
	
	targaInputOutputTest();
	//linkedListTest();
	rawTrace();
	return 0;
}


//----------------
void	rawTrace()
//----------------
{
	// 2D Datas
	gfxBuffer *graphic_buffer;
	hdr_pixel pixel, sub_pixel;
	int		x,y, i;
	const int	sampling_rate = 16;
	const float	sub_pixel_offset = 0.95f, sub_pixel_weight = 1.0f / sampling_rate;

	// 3D datas
	vector	ray;
	itemList	*sphere_list;
	sphere		*new_sphere;

	// init render buffer
	graphic_buffer = new gfxBuffer(RENDER_BUFFER_SIZE_X, RENDER_BUFFER_SIZE_Y);

	// create various spheres
	sphere_list = new itemList();

	new_sphere = new sphere; // sphere #1
	new_sphere->center.x	= 150.0f;
	new_sphere->center.y	= 0.0f;
	new_sphere->center.z	= 80.0f;
	new_sphere->radius		= 80.0f;
	new_sphere->diffuse_color.redValue		= 1.0f;
	new_sphere->diffuse_color.greenValue	= 0.25f;
	new_sphere->diffuse_color.blueValue		= 0.15f;
	new_sphere->diffuse_color.alphaValue	= 1.0f;
	sphere_list->insertItem(new_sphere);

	new_sphere = new sphere; // sphere #2
	new_sphere->center.x	= 0.0f;
	new_sphere->center.y	= 0.0f;
	new_sphere->center.z	= 80.0f;
	new_sphere->radius		= 120.0f;
	new_sphere->diffuse_color.redValue		= 0.8f;
	new_sphere->diffuse_color.greenValue	= 0.2f;
	new_sphere->diffuse_color.blueValue		= 1.0f;
	new_sphere->diffuse_color.alphaValue	= 1.0f;
	sphere_list->insertItem(new_sphere);

	new_sphere = new sphere; // sphere #3
	new_sphere->center.x	= -150.0f;
	new_sphere->center.y	= 0.0f;
	new_sphere->center.z	= 80.0f;
	new_sphere->radius		= 100.0f;
	new_sphere->diffuse_color.redValue		= 0.15f;
	new_sphere->diffuse_color.greenValue	= 0.25f;
	new_sphere->diffuse_color.blueValue		= 1.0f;
	new_sphere->diffuse_color.alphaValue	= 1.0f;
	sphere_list->insertItem(new_sphere);

	{
		sphere	*st;

		sphere_list->gotoListHead();
		while(sphere_list->gotoNextItem())
		{
			st = (sphere *)sphere_list->getContent();

			printf("%f, ",st->radius);
		}
	}

	// start raytrace
	for(x = -RENDER_BUFFER_SIZE_X / 2; x < RENDER_BUFFER_SIZE_X / 2; x++)
	{
		for(y = -RENDER_BUFFER_SIZE_Y / 2; y < RENDER_BUFFER_SIZE_Y / 2; y++)
		{
			memset(&pixel, 0, sizeof(hdr_pixel));
			for (i = 0; i <= sampling_rate; i++)
			{
				ray.origin.x = (float)0;
				ray.origin.y = (float)0;
				ray.origin.z = (float)-250;
				ray.direction.x = (float)x + RAND(sub_pixel_offset) - RAND(sub_pixel_offset);
				ray.direction.y = (float)y + RAND(sub_pixel_offset) - RAND(sub_pixel_offset);
				ray.direction.z = (float)250;
				sub_pixel = traceRay(ray, sphere_list);

				pixel.redValue		+=	sub_pixel.redValue * sub_pixel_weight;
				pixel.greenValue	+=	sub_pixel.greenValue * sub_pixel_weight;
				pixel.blueValue		+=	sub_pixel.blueValue * sub_pixel_weight;
				pixel.alphaValue	+=	sub_pixel.alphaValue * sub_pixel_weight;
			}
			graphic_buffer->putHdrPixel(x + RENDER_BUFFER_SIZE_X / 2, y + RENDER_BUFFER_SIZE_Y / 2, &pixel);
		}
	}

	graphic_buffer->saveFileTarga("trace.tga");

	graphic_buffer->filterBoxBlur(8);

	graphic_buffer->saveFileTarga("trace_blured.tga");

	delete graphic_buffer;

}

//---------------------------
hdr_pixel	traceRay(vector	I, itemList *object_list)
//---------------------------
{
	float		d; //, z_hit;

	sphere		*object_hit;

	hdr_pixel	trace_result;

	object_list->gotoListHead();

	//z_hit = 0.0f;

	while(object_list->gotoNextItem())
	{
		d = sphereIntersect(I, (sphere *)object_list->getContent());

		if (d > 0.0f)
		{
			//printf("%f\n",d);
			object_hit = (sphere *)object_list->getContent();
			break;
		}

	}

	if (d > 0.0f)
	{	
		// shading
		/*
		N.origin.x = sphere_center.x;
		N.origin.y = sphere_center.y;
		N.origin.z = sphere_center.z;

		N.direction.x = sphere_center.x;
		N.direction.y = sphere_center.y;
		N.direction.z = sphere_center.z;
		*/
		//d = qSQR(d);
		d = 3.0f * d - 2.0f;
		trace_result.redValue	= object_hit->diffuse_color.redValue * d;
		trace_result.greenValue	= object_hit->diffuse_color.greenValue * d;
		trace_result.blueValue	= object_hit->diffuse_color.blueValue * d;
		trace_result.alphaValue	= object_hit->diffuse_color.alphaValue * d;
	}
	else
	{
		// background
		trace_result.redValue = 0.0f;
		trace_result.greenValue = 0.0f;
		trace_result.blueValue = 0.0f;
		trace_result.alphaValue = 0.0f;
	}

	return (trace_result);

}


//-------------------------------------------------------------------------
float	sphereIntersect(vector	ray, sphere *tested_sphere)
//-------------------------------------------------------------------------
{
	float	a,b,c,d, t1, t2, t;
	float	spherex, spherey, spherez, radius;

	spherex = tested_sphere->center.x;
	spherey = tested_sphere->center.y;
	spherez = tested_sphere->center.z;
	radius	= tested_sphere->radius;

   a = qSQR( ray.direction.x ) + qSQR( ray.direction.y ) + qSQR( ray.direction.z );
   b = 2 * ( ray.direction.x * ( ray.origin.x - spherex ) +
             ray.direction.y * ( ray.origin.y - spherey ) +
             ray.direction.z * ( ray.origin.z - spherez ) );
   c = ( qSQR( (ray.origin.x - spherex) ) + qSQR( (ray.origin.y - spherey) ) 
       + qSQR( (ray.origin.z - spherez) ) - qSQR(radius) );
   d = qSQR(b) - 4 * a * c;

	if (d > 0)
	{
		t1 = (float)(-b + sqrt(d)) / (2 * a);
		t2 = (float)(-b - sqrt(d)) / (2 * a);
		t = t1 < t2 ? t1 : t2; // should be : t = t1 > t2 ? t1 : t2;

		//printf("Intersection sphere/ray found. Depth = %f\n",t);
		return	t;
	}
	else
	{
		//printf("No Intersection sphere/ray found\n");
		return	-1.0;
	}


}


