// render.h

#include "gfxBuffer.h"
#include "list.h"
#include "math.h"
#include "geometry.h"

#ifndef RENDERER
#define RENDERER

#define	BACKGROUND_COLOR	Rcolor(0.5f)

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
	void		translate(Rpoint &);

	void		addLight(Rpoint position = Rpoint(0.0f, 100.0f, 0.0f), 
						Rcolor color = Rcolor(1.0f), float intensity = 1.0, 
						float falloff = -1.0, float radius = 0.0, int type = 1.0);
	void		addAmbiantLight(Rcolor color = Rcolor(0.2f), float intensity = 1.0);

	void		printBoundingBoxes();

	// render
	void		renderScene(const int sampling_rate = 4, const float sampling_threshold = 0.1f, SDL_Surface *sdl_buffer = 0);
	void		saveRender();
	void		displayRender(SDL_Surface *);
	int			traceRay(RrenderContext&, RrenderContext&, bool);
	Rcolor		shadePoint(RrenderContext &);

	// render datas (size, frame buffer)
	gfxBuffer	*frame_buffer;
	int			pixel_size_x, pixel_size_y;
	float		frame_left, frame_right;
	float		frame_top, frame_bottom;

	// scene datas
	Rlist		*meshes_list;
	Rlist		*lights_list;

	int			ray_poly_hit,ray_poly_missed;
};

#endif