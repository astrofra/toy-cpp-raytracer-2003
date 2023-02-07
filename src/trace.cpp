// Trace.cpp 
//

#undef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN

#include <stdio.h>
#include <math.h>

#include "trace.h"
#include "gfxBuffer.h"
#include "test.h"

// #include "gfxBuffer.h"

//------------------------------
int main(int argc, char* argv[])
//------------------------------
{
	
	linkedListTest();
	// rawTrace();
	return 0;
}


//----------------
void	rawTrace()
//----------------
{
	// 2D Datas
	gfxBuffer *graphic_buffer;
	rgba_pixel pixel;
	int	x,y;

	// 3D datas
	vector	ray;

	// init render buffer
	graphic_buffer = new gfxBuffer(RENDER_BUFFER_SIZE_X, RENDER_BUFFER_SIZE_Y);
	
	// start raytrace
	for(x = -RENDER_BUFFER_SIZE_X / 2; x < RENDER_BUFFER_SIZE_X / 2; x++)
	{
		for(y = -RENDER_BUFFER_SIZE_Y / 2; y < RENDER_BUFFER_SIZE_Y / 2; y++)
		{
			ray.origin.x = (float)0;
			ray.origin.y = (float)0;
			ray.origin.z = (float)-256;
			ray.direction.x = (float)x;
			ray.direction.y = (float)y;
			ray.direction.z = (float)256;
			pixel = traceRay(ray);
			graphic_buffer->putRGBAPixel(x + RENDER_BUFFER_SIZE_X / 2, y + RENDER_BUFFER_SIZE_Y / 2, pixel);
		}
	}

		graphic_buffer->saveBuffer("f:\\trace.tga");

	delete graphic_buffer;

}

//---------------------------
rgba_pixel	traceRay(vector	I)
//---------------------------
{
	float	d;
	point	sphere_center;
	rgba_pixel	trace_result;
	//vector	N;

	sphere_center.x = 64.0;
	sphere_center.y = 0.0;
	sphere_center.z = 1024.0;

	d = sphereIntersect(I, sphere_center, 50);

	if (d > 0)
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

		trace_result.redValue = 255;
		trace_result.greenValue = 255;
		trace_result.blueValue = 255;
		trace_result.alphaValue = 255;
	}
	else
	{
		// background
		trace_result.redValue = 0;
		trace_result.greenValue = 0;
		trace_result.blueValue = 0;
		trace_result.alphaValue = 0;
	}

	return (trace_result);

}


//-------------------------------------------------------------------------
float	sphereIntersect(vector	ray, point	sphere_center, float sphere_radius)
//-------------------------------------------------------------------------
{
	float	a,b,c,d, t1, t2, t;
	float	spherex, spherey, spherez;

	spherex = sphere_center.x;
	spherey = sphere_center.y;
	spherez = sphere_center.z;

   a = qSQR( ray.direction.x ) + qSQR( ray.direction.y ) + qSQR( ray.direction.z );
   b = 2 * ( ray.direction.x * ( ray.origin.z - spherex ) +
             ray.direction.y * ( ray.origin.y - spherey ) +
             ray.direction.z * ( ray.origin.z - spherez ) );
   c = ( qSQR( (ray.origin.x - spherex) ) + qSQR( (ray.origin.y - spherey) ) 
       + qSQR( (ray.origin.z - spherez) ) - qSQR(sphere_radius) );
   d = b*b - 4*a*c;

	if (d > 0)
	{
		t1 = (float)(-b + sqrt(d)) / (2*a);
		t2 = (float)(-b - sqrt(d)) / (2*a);
		t = t1 > t2 ? t1 : t2;

		//printf("Intersection sphere/ray found. Depth = %f\n",t);

		return	t;
	}
	else
	{
		//printf("No Intersection sphere/ray found\n");
		return	-1;
	}


}


