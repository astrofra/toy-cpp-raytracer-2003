// render.cpp

#include <memory.h>
#include <stdio.h>

#include "math.h"
#include "list.h"
#include "render.h"

//-------- RrenderContext ------------------------

RrenderContext::RrenderContext()
{
	memset(this, 0, sizeof(Rrenderer));
}

RrenderContext::~RrenderContext()
{
}

//-------- Rrenderer ------------------------

//--------------------
Rrenderer::Rrenderer()
//--------------------
{
	memset(this, 0, sizeof(Rrenderer));
}


//----------------------------------
Rrenderer::Rrenderer(int sx, int sy)
//----------------------------------
{
	float	ratio;

	pixel_size_x = sx;
	pixel_size_y = sy;

	if (sx > sy)
		ratio = (float)sx;
	else
		ratio = (float)sy;

	frame_left		= (float)sx / (-2.0f * ratio) ;
	frame_right		= (float)sx / (2.0f * ratio);
	frame_top		= (float)sy / (-2.0f * ratio);
	frame_bottom	= (float)sy / (2.0f * ratio);

	frame_buffer = new gfxBuffer(pixel_size_x, pixel_size_y);

	printf("Rrenderer::Rrenderer(%i, %i)\n", pixel_size_x, pixel_size_y);

	meshes_list = 0;

	ray_poly_hit = ray_poly_missed = 0;
}

//---------------------
Rrenderer::~Rrenderer()
//---------------------
{
	//delete frame_buffer;
	//delete []meshes_list;
}

//------------------------------------------------
int		Rrenderer::loadFiles(Rlist &filename_list)
//------------------------------------------------
{
	Rmesh	*new_mesh;
	int	i = 0;
	if (meshes_list == 0)
		meshes_list = new Rlist();

	filename_list.gotoListHead();

	while(filename_list.gotoNextItem())
	{
		i++;
		new_mesh = new Rmesh();
		(*new_mesh).loadFileWavefront((char *)filename_list.getContent());
		(*meshes_list).appendItem(new_mesh);
	}
	
	printf("Rrenderer::loadFiles(), loaded %i file(s)\n", i);

	return 1;
}

//----------------------------
int		Rrenderer::saveFiles()
//----------------------------
{
	Rmesh	*mesh;
	char	str[1024];
	int		i = 0;

	memset(str,0,sizeof(str));

	(*meshes_list).gotoListHead();

	while((*meshes_list).gotoNextItem())
	{
		mesh = (Rmesh *)(*meshes_list).getContent();
		if (i < 9) { 
			sprintf(str,"dump_0%i.obj\0",i + 1); }
		else {
			sprintf(str,"dump_%i.obj\0",i + 1); }

		(*mesh).saveFileWavefront(&str[0]);
		i++;
	}

	printf("Rrenderer::saveFiles(), saved %i file(s)\n", i);

	return 1;
}	

//------------------------------
void Rrenderer::computeNormals()
//------------------------------
{
	Rmesh	*mesh;
	(*meshes_list).gotoListHead();

	int i = 0;

	while((*meshes_list).gotoNextItem())
	{
		i++;
		mesh = (Rmesh *)(*meshes_list).getContent();
		(*mesh).computeNormals();
	}

	printf("Rrenderer::computeNormals(), %i mesh(es)\n", i);
	
}

//--------------------------------------
void Rrenderer::computeSmoothedNormals()
//--------------------------------------
{
	// create a table to store each point's poly-list 
	
	// for each poly 
	{
		// for each point of this poly
		{
			// add polygon normal to the point list
		}
	}

	// for each point
	{
		// for each poly using this point
		{

		}
	}
}

//------------------------------------
void Rrenderer::computeBoundingBoxes()
//------------------------------------
{
	Rmesh	*mesh;
	(*meshes_list).gotoListHead();

	int i = 0;

	while((*meshes_list).gotoNextItem())
	{
		i++;
		mesh = (Rmesh *)(*meshes_list).getContent();
		(*mesh).computeBoundingBox();
	}

	printf("Rrenderer::computeBoundingBoxes(), %i mesh(es)\n", i);
	
}

//------------------------------------
void Rrenderer::printBoundingBoxes()
//------------------------------------
{
	Rmesh	*mesh;
	(*meshes_list).gotoListHead();

	int i = 0;

	while((*meshes_list).gotoNextItem())
	{
		i++;
		mesh = (Rmesh *)(*meshes_list).getContent();
		(*mesh).printBoundingBox();
	}	
}

//----------------------------------------------------
void Rrenderer::fitScene(float max_bounding_distance)
//----------------------------------------------------
{
	Rmesh	*mesh;
	Rpoint	scene_bounding_box_min = Rpoint(0.0f),
			scene_bounding_box_max = Rpoint(0.0f);

	float	bounding_distance, resize_factor;

	(*meshes_list).gotoListHead();

	// evaluate bounding box surrounding the scene
	while((*meshes_list).gotoNextItem())
	{
		mesh = (Rmesh *)(*meshes_list).getContent();

		if (scene_bounding_box_min.x > (*mesh).bounding_box_min.x) {
			scene_bounding_box_min.x = (*mesh).bounding_box_min.x; }
		if (scene_bounding_box_min.y > (*mesh).bounding_box_min.y) {
			scene_bounding_box_min.y = (*mesh).bounding_box_min.y; }
		if (scene_bounding_box_min.z > (*mesh).bounding_box_min.z) {
			scene_bounding_box_min.z = (*mesh).bounding_box_min.z; }
		
		if (scene_bounding_box_max.x < (*mesh).bounding_box_max.x) {
			scene_bounding_box_max.x = (*mesh).bounding_box_max.x; }
		if (scene_bounding_box_max.y < (*mesh).bounding_box_max.y) {
			scene_bounding_box_max.y = (*mesh).bounding_box_max.y; }
		if (scene_bounding_box_max.z < (*mesh).bounding_box_max.z) {
			scene_bounding_box_max.z = (*mesh).bounding_box_max.z; }
	}

	// reset BB origin & get its largest dimension
	scene_bounding_box_max = scene_bounding_box_max - scene_bounding_box_min;

	bounding_distance = MAX_VALUE(scene_bounding_box_max.x, scene_bounding_box_max.y);
	bounding_distance = MAX_VALUE(scene_bounding_box_max.z, bounding_distance);

	if (max_bounding_distance > bounding_distance)
		resize_factor = bounding_distance / max_bounding_distance;
	else
		resize_factor = max_bounding_distance / bounding_distance;

	(*meshes_list).gotoListHead();

	while((*meshes_list).gotoNextItem())
	{
		mesh = (Rmesh *)(*meshes_list).getContent();
		(*mesh).scale(resize_factor);
	}

	printf("Rrenderer::fitScene(%f), scale scene by (%f)\n", max_bounding_distance, resize_factor);
	
}


//------------------------------
void	Rrenderer::renderScene()
//------------------------------
{

	int	x,y;
	RrenderContext	projection_screen;

	projection_screen.P.z = 0.0;
	projection_screen.I.x = projection_screen.I.y = 0.0;
	projection_screen.I.z = 50.0;

	printf("Rrenderer::renderScene(), rendering ... ");

	for(y = 0; y < pixel_size_y; y++)
	{
		printf("line %6i", y);

		projection_screen.P.y = ((float)y / (float)pixel_size_y) + frame_top;

		for(x = 0; x < pixel_size_x; x++)
		{
			projection_screen.P.x = ((float)x / (float)pixel_size_x) + frame_left;
			(*frame_buffer).putPixel(x, y, Trace(projection_screen));
			
		}

		printf("\b\b\b\b\b\b\b\b\b\b\b");
	}
	printf("\n");

	printf("Rrenderer::renderScene(), %i ray/polygon hit, %i ray/poly missed\n",ray_poly_hit,ray_poly_missed);
	printf("Rrenderer::renderScene(), ray casting accuracy : %f %% \n", ((float)ray_poly_hit * 100.0f) / (float)ray_poly_missed);
}

//-----------------------------
void	Rrenderer::saveRender()
//-----------------------------
{
	(*frame_buffer).saveFileTarga("out.tga");
}


//----------------------------------------------
Rcolor	Rrenderer::Trace(RrenderContext& context)
//----------------------------------------------
{
	Rmesh		*current_mesh = 0,
				*object_hit = 0;

	Rpolygon	*current_polygon = 0;
	
	int			i;
	float		z_hit, z_BB_hit, 
				z_hit_min = INTERSECTION_INFINITE; // INTERSECTION_EPSILON

	//Rcolor		trace_result;

	(*meshes_list).gotoListHead();
	while((*meshes_list).gotoNextItem())
	{
		current_mesh = (Rmesh *)(*meshes_list).getContent();

		// if ray hits object's bouding box
		if ((*current_mesh).RayIntersectBoundingBox(context.P, context.I, z_BB_hit))
		{
			// for every polygons
			for(i = 0; i < (*current_mesh).polygon_count; i++)
			{
				// if ray hits polygon
				if ((*current_mesh).RayIntersectPoly(context.P, context.I, i, z_hit))
				{
					ray_poly_hit++;

					// if intersection is clother to camera than previous one
					if (z_hit < z_hit_min)
					{
						z_hit_min = z_hit;
						object_hit = current_mesh;
					}

				}
				else
				{
					ray_poly_missed++;
				}

			}
		}
	}

	if (object_hit != 0)
	{
		// call shader
		return Rcolor(1.0);
	}
	else
	{
		return Rcolor(BACKGROUND_COLOR);
	}
}





