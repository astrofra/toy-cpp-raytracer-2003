// render.cpp

#include <memory.h>
#include <stdio.h>

#include "math.h"
#include "light.h"
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
	lights_list = 0;
	ray_poly_missed = ray_poly_hit = 0;
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

//----------------------------------
void Rrenderer::translate(Rpoint &T)
//----------------------------------
{
	Rmesh	*mesh;
	
	(*meshes_list).gotoListHead();

	while((*meshes_list).gotoNextItem())
	{
		mesh = (Rmesh *)(*meshes_list).getContent();
		(*mesh).translate(T);
	}
	printf("Rrenderer::translate(%f,%f,%f)\n", T.x,
		T.y, T.z);
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

	// evaluate the global bounding box
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

//------------------------------------------------------------------------------------------------------
void	Rrenderer::addLight(Rpoint position, Rcolor color, float intensity, float falloff, float radius)
//------------------------------------------------------------------------------------------------------
{
	Rlight	*new_light;

	if (lights_list == 0)
		lights_list = new Rlist();

	new_light = new Rlight(position);

	(*new_light).setColor(color);
	(*new_light).setIntensity(intensity);
	(*new_light).setFalloff(falloff);
	(*new_light).setRadius(radius);

	(*lights_list).appendItem(new_light);
}

//------------------------------
void	Rrenderer::renderScene(const int sampling_rate, const float sampling_threshold)
//------------------------------
{

	int		x,y,i;
	float	xx, yy, last_pixel_luminance = 0.0f;
	Rcolor	pixel;

	float	sub_pixel_offset = 0.0025f, sub_pixel_weight = 1.0f / (float)sampling_rate;

	RrenderContext	projection_screen,
					trace_result;

	projection_screen.P.z = 0.0f;
	
	projection_screen.I.x = 0.0f;
	projection_screen.I.y = 0.0f;
	projection_screen.I.z = -1.0f;

	printf("Rrenderer::renderScene(), rendering ... ");

	for(y = 0; y < pixel_size_y; y++)
	{
		printf("line %6i", y);

		yy = ((float)y / (float)pixel_size_y) + frame_top;

		for(x = 0; x < pixel_size_x; x++)
		{
			xx = ((float)x / (float)pixel_size_x) + frame_left;
			
			memset(&pixel, 0, sizeof(pixel));

			for(i = 0; i <= sampling_rate; i++)
			{
				projection_screen.P.x = xx + RAND(sub_pixel_offset) - RAND(sub_pixel_offset);
				projection_screen.P.y = yy + RAND(sub_pixel_offset) - RAND(sub_pixel_offset);

				if (traceRay(projection_screen,trace_result, false))
				{
					pixel += shadePoint(trace_result);
				}
				else
				{
					pixel += BACKGROUND_COLOR;
				}

				if ((i > 0) && (ABS_VALUE(last_pixel_luminance - pixel.luminance()) < sampling_threshold))
				{
					break;
				}
			}

			if (i > 1)
			{	pixel *= sub_pixel_weight; }
			else
			{	pixel.r *= (float)0.5f; 	pixel.g *= (float)0.5f; 	pixel.b *= (float)0.5f; }

			last_pixel_luminance = pixel.luminance();
			(*frame_buffer).putPixel(x, y, pixel);
			
		}

		printf("\b\b\b\b\b\b\b\b\b\b\b");
	}
	printf("\n");

	printf("Rrenderer::renderScene(), %i ray/polygon hit, %i ray/poly missed\n",ray_poly_hit,ray_poly_missed);
	printf("Rrenderer::renderScene(), ray casting accuracy : %f %% \n", ((float)ray_poly_hit * 100.0f) / (float)ray_poly_missed);
}


//------------------------------------------------------------------------------------------
int	Rrenderer::traceRay(RrenderContext& context, RrenderContext& result, bool is_shadow_ray)
//------------------------------------------------------------------------------------------
{
	Rmesh		*current_mesh = 0,
				*object_hit = 0;

	Rpolygon	*current_polygon = 0;
	
	int			i, polygon_hit = 0;
	float		z_hit, z_BB_hit, 
				z_hit_min = INTERSECTION_INFINITE; // INTERSECTION_EPSILON

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
						polygon_hit = i;
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
		if (is_shadow_ray == false)
		{
			result.Cs	= (*object_hit).polygon_table[polygon_hit].getCs();
			result.N	= (*object_hit).polygon_table[polygon_hit].getN();

			result.P	= context.I;
			result.P	*= z_hit;
		}

		return 1;
	}
	else
	{
		return 0;
	}
}

//----------------------------------------------------
Rcolor	Rrenderer::shadePoint(RrenderContext &context)
//----------------------------------------------------
{
	Rlight	*current_light;
	float	Cl;
	Rcolor	Ci = Rcolor(0.0f), Ct;
	// initialise Color buffer

	(*lights_list).gotoListHead();

	// for each light
	while((*lights_list).gotoNextItem())
	{
		current_light = (Rlight *)(*lights_list).getContent();

		// diffusion pass
		Cl = context.N * (*current_light).getLightDirection(context.P);
		
		if (Cl > 0.0f)
		{
			Ct = context.Cs;
			Ct *= (*current_light).getColor();
			Ct *= (*current_light).getIntensity();
			Ct *= Cl;

			// shadow pass

			// Add to Color Buffer
			Ci += Ct;
		}
	}

	return Ci;
}

//-----------------------------
void	Rrenderer::saveRender()
//-----------------------------
{
	(*frame_buffer).saveFileTarga("out.tga");
}





