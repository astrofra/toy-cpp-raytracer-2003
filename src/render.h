// render.h

#include "gfxBuffer.h"
#include "list.h"
#include "math.h"
#include "geometry.h"

#ifndef RENDERER
#define RENDERER

//-------- RrenderContext ------------------------

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


//-------- Rrenderer ------------------------

class Rrenderer
{
public:
	Rrenderer();
	Rrenderer(int, int);
	~Rrenderer();

	// scene setup
	int			loadFiles(Rlist&);
	int			saveFiles();
	void		computeNormals();
	void		computeSmoothedNormals();
	void		computeBoundingBoxes();
	void		fitScene(float );

	// render
	void		renderScene();
	void		saveRender();
	Rcolor		Trace(RrenderContext);

	// render datas (size, frame buffer)
	gfxBuffer	*frame_buffer;
	int			pixel_size_x, pixel_size_y;
	float		frame_left, frame_right;
	float		frame_top, frame_bottom;

	// scene datas
	Rlist		*meshes_list;
	int			ray_poly_hit,ray_poly_missed;
};

#endif