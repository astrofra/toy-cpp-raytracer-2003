// render.h
#include "list.h"
#include "math.h"
#include "geometry.h"

#ifndef RENDERER
#define RENDERER

//-------- Rrenderer ------------------------

class Rrenderer
{
public:
	Rrenderer();
	~Rrenderer();

	void	loadFiles(Rlist *);

	void	renderScene();

	float	bufferToRendererX(int );
	float	bufferToRendererY(int );

	int		pixel_size_x, pixel_size_y;
	float	frame_left, frame_right;
	float	frame_top, frame_bottom;

	Rlist	*meshes_list;
};

//-------- RrenderContext ------------------------

/*
class	RrenderContext
{
public:
	RrenderContext();
	~RrenderContext();  

	Rcolor	Cs;		//	surface color

	Rpoint	P;		//	surface position
	Rpoint	I;		//	direction of ray hitting surface point (generaly from cam.)
	Rpoint	N;		//	surface geometric normal (for flat shading purpose only)

};
*/

#endif