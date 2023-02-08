// main.cpp

#include "render.h"
#include "geometry.h"
#include "math.h"

void main(int argc, char* argv[])
{

	Rrenderer	*renderer;
	Rlist	filename_list;

	// setup list of objects files ("scene")
	/*
	filename_list.appendItem("I:\\fra\\DEV\\datas\\hi_obj_01.obj");
	filename_list.appendItem("I:\\fra\\DEV\\datas\\hi_obj_02.obj");
	filename_list.appendItem("I:\\fra\\DEV\\datas\\hi_obj_03.obj");
	filename_list.appendItem("I:\\fra\\DEV\\datas\\hi_obj_04.obj");
	filename_list.appendItem("I:\\fra\\DEV\\datas\\hi_obj_05.obj");
	*/

	filename_list.appendItem("I:\\fra\\DEV\\datas\\lo_head.obj");

	// create renderer space
	renderer = new Rrenderer(512,512);

	// load files to new objects
	(*renderer).loadFiles(filename_list);

	(*renderer).computeNormals();
	(*renderer).computeBoundingBoxes();
	(*renderer).fitScene(0.75f);
	//(*renderer).translate(Rpoint(0.0, -0.15f, 0.0));
	(*renderer).computeBoundingBoxes();

	(*renderer).addLight(Rpoint(5.0f, 3.0f, 0.0f));
	(*renderer).addLight(Rpoint(-5.0f, 5.0f, -2.5f), Rcolor(0.15f, 0.45f, 0.75f), 0.8f);
	(*renderer).addLight(Rpoint(0.0f, -0.5f, 2.5f), Rcolor(1.0f, 0.65f, 0.2f), 0.35f);
	
	// render objects
	(*renderer).renderScene(32,0.2f);

	(*renderer).saveRender();

	//(*renderer).saveFiles();

	return;
};
