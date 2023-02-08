// main.cpp

#include "render.h"
#include "geometry.h"
#include "math.h"

main(int argc, char* argv[])
{
	/*
	Rrenderer	renderer;

	Rlist	*filename_list;

	// setup list of objects files (or what people call "scene")

	// load files to new objects
	renderer.loadFiles(filename_list);

	// render objects
	renderer.renderScene();
	*/

	Rmesh	my_mesh;

	my_mesh.loadFileWavefront("I:\\fra\\DEV\\datas\\head.obj");

	return;
};
