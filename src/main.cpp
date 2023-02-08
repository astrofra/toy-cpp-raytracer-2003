// main.cpp

#include "render.h"
#include "geometry.h"
#include "math.h"

void main(int argc, char* argv[])
{

	Rrenderer	*renderer;
	Rlist	filename_list;

	// setup list of objects files ("scene")
	filename_list.appendItem("I:\\fra\\DEV\\datas\\obj_01.obj");
	filename_list.appendItem("I:\\fra\\DEV\\datas\\obj_02.obj");
	filename_list.appendItem("I:\\fra\\DEV\\datas\\obj_03.obj");
	filename_list.appendItem("I:\\fra\\DEV\\datas\\obj_04.obj");
	filename_list.appendItem("I:\\fra\\DEV\\datas\\obj_05.obj");

	//filename_list.appendItem("I:\\fra\\DEV\\datas\\obj_2_01.obj");
	//filename_list.appendItem("I:\\fra\\DEV\\datas\\obj_2_02.obj");
	//filename_list.appendItem("I:\\fra\\DEV\\datas\\obj_2_03.obj");	

	// create renderer space
	renderer = new Rrenderer(400,400);

	// load files to new objects
	(*renderer).loadFiles(filename_list);

	(*renderer).computeNormals();

	(*renderer).computeBoundingBoxes();
	(*renderer).printBoundingBoxes();

	(*renderer).fitScene(0.75);
	(*renderer).computeBoundingBoxes();
	
	// render objects
	(*renderer).renderScene();

	(*renderer).saveRender();

	//(*renderer).saveFiles();

	return;
};
