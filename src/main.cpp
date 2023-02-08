// --------- SDL INCLUDES ---
#include <stdlib.h>
#if defined(_MSC_VER)
#include "SDL.h"
#else
#include "SDL/SDL.h"
#endif

// --------- 3D RENDER INCLUDES ---
#include "render.h"
#include "geometry.h"
#include "math.h"

void render(SDL_Surface*);
Rrenderer	*renderer;

// Entry point
int main(int argc, char *argv[])
{

	SDL_Surface *screen;

	// Initialize SDL's subsystems - in this case, only video.
	if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) 
	{
		fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
		exit(1);
	}

	// Register SDL_Quit to be called at exit; makes sure things are
	// cleaned up when we quit.
	atexit(SDL_Quit);
    
	// Attempt to create a 640x480 window with 32bit pixels.
	screen = SDL_SetVideoMode(512, 512, 32, SDL_SWSURFACE);
  
	// If we fail, return error.
	if ( screen == NULL ) 
	{
		fprintf(stderr, "Unable to set 512x512 video: %s\n", SDL_GetError());
		exit(1);
	}

	render(screen);

	while (1)
	{
		// Render stuff
		//surface_render();
		(*renderer).displayRender(screen);

		// Poll for events, and handle the ones we care about.
		SDL_Event event;
		while (SDL_PollEvent(&event)) 
		{
			switch (event.type) 
			{
				case SDL_KEYDOWN:
					break;
				case SDL_KEYUP:
					// If escape is pressed, return (and thus, quit)
					if (event.key.keysym.sym == SDLK_ESCAPE)
					return 0;
					break;
				case SDL_QUIT:
					return(0);
			}
		}
  }

  return 0;
}

// ----------------- 3D Render -------
void render(SDL_Surface *sdl_buffer)
{
	Rlist	filename_list;

	// setup list of objects files ("scene")	
	filename_list.appendItem("F:\\fra\\DEV\\datas\\lo_head.obj");
	

	// create renderer space
	renderer = new Rrenderer(512,512);

	// load files to new objects
	(*renderer).loadFiles(filename_list);

	(*renderer).computeNormals();
	(*renderer).computeBoundingBoxes();
	(*renderer).fitScene(0.75f);
	//(*renderer).translate(Rpoint(0.0, -0.15f, 0.0));
	(*renderer).computeBoundingBoxes();

	(*renderer).addLight(Rpoint(0.0f, 5.0f, 2.5f), Rcolor(1.0f), 0.5f);
	(*renderer).addLight(Rpoint(-5.0f, 5.0f, -2.5f), Rcolor(0.15f, 0.45f, 0.75f), 0.8f);
	//(*renderer).addLight(Rpoint(0.0f, -0.5f, 2.5f), Rcolor(1.0f, 0.65f, 0.2f), 0.35f);

	(*renderer).addAmbiantLight(Rcolor(0.8f,0.2f,0.0f), 0.5f);
	
	// render objects
	(*renderer).renderScene(2 ,0.8f, sdl_buffer);

	(*renderer).saveRender();

	//(*renderer).saveFiles();

	return;
};
