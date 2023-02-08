// geometry.cpp

#include <memory.h>
#include <string>
#include <stdio.h>

#include "list.h"
#include "math.h"
#include "geometry.h"
#include "trace.h"

//-------- Rpolygon ------------------------

Rpolygon::Rpolygon()
{
	memset(this, 0, sizeof(Rpolygon));
	this->Cs = Rcolor(1.0f);
}

Rpolygon::~Rpolygon() {}

//-------- Rmesh ------------------------

//------------
Rmesh::Rmesh()
//------------
{
	memset(this, 0, sizeof(Rmesh));
}


//-------------
Rmesh::~Rmesh()
//-------------
{
	/*
	if (polygon_table != 0)
		delete []polygon_table;

	if (point_table != 0)
		delete []point_table;
	*/
}

//---------------------------------
void	Rmesh::computeBoundingBox()
//---------------------------------
{
	bounding_box_min = Rpoint(INTERSECTION_INFINITE);
	bounding_box_max = Rpoint(-INTERSECTION_INFINITE);

	// for every point
	for(int i = 0; i < this->point_count; i++)
	{
		// search for min & max
		bounding_box_min.x = MIN_VALUE(this->point_table[i].x, bounding_box_min.x);
		bounding_box_min.y = MIN_VALUE(this->point_table[i].y, bounding_box_min.y);
		bounding_box_min.z = MIN_VALUE(this->point_table[i].z, bounding_box_min.z);

		bounding_box_max.x = MAX_VALUE(this->point_table[i].x, bounding_box_max.x);
		bounding_box_max.y = MAX_VALUE(this->point_table[i].y, bounding_box_max.y);
		bounding_box_max.z = MAX_VALUE(this->point_table[i].z, bounding_box_max.z);
	}

}

//---------------------------------
void	Rmesh::printBoundingBox()
//---------------------------------
{
	printf("Rmesh::printBoundingBox()\n   min(%f, %f, %f) / max(%f, %f, %f)\n", 
		bounding_box_min.x, bounding_box_min.y, bounding_box_min.z,
		bounding_box_max.x, bounding_box_max.y, bounding_box_max.z);
}

//-----------------------------
void	Rmesh::computeNormals()
//-----------------------------
{
	Rpolygon	*current_poly;
	Rpoint		v1,v2, n;
	// for every polygon
	for (int i = 0; i < this->polygon_count; i++)
	{
		current_poly = &(this->polygon_table[i]);
		v1 = this->point_table[(*current_poly).points[1]] - this->point_table[(*current_poly).points[0]];
		v2 = this->point_table[(*current_poly).points[2]] - this->point_table[(*current_poly).points[0]];
		
		v1.normalize();
		v2.normalize();
		n = v1 % v2;
		n.normalize();

		(*current_poly).N = n;
	}
}


//--------------------------------------
void	Rmesh::scale(float scale_factor)
//--------------------------------------
{
	// for every point
	if (scale_factor != 1.0){
		for(int i = 0; i < this->point_count; i++){
			point_table[i] *= scale_factor;	
		}
	}

}

//-------------------------------------------------------
void	Rmesh::translate(Rpoint& T)
//-------------------------------------------------------
{
	// for every point
	for(int i = 0; i < this->point_count; i++){
		point_table[i] += T;	
	}

}


//-------------------------------------------------------
void	Rmesh::rotateX(Rpoint& T, float x_angle)
//-------------------------------------------------------
{
}


//-------------------------------------------
int		Rmesh::loadFileWavefront(char *fname)
//-------------------------------------------
// load simplified lightwave's obj export (no vertex normal, no uv coords)
{
	// create vertex & polygons lists
	Rlist		*point_list,
				*polygon_list;

	Rpoint		*new_point;
	Rpolygon	*new_polygon;

	int		point_per_face, i;

	char	str[1024], x[256], y[256], z[256];

	memset(str,0,sizeof(str));

	// open Wavefront .obj file
	FILE *fp;

	fp = fopen( fname, "ra" );

	if( !fp )
	{
	   printf("Rmesh::loadFileWavefront() : file open error on %s.\n", fname );
	   return 0;
	}


	point_list = new Rlist;
	polygon_list = new Rlist;

	// seek for first vertex line
	while(str[0] != 'v') {
		fgets(str, sizeof(str), fp); }

	// for every point found
	while(str[0] == 'v')
	{
		switch (str[1])
		{
		case ' ' :
			sscanf(str,"v %s %s %s", &x, &y, &z); // &(new_point->x), &(new_point->y), &(new_point->z));
			new_point = new Rpoint(atof(x), atof(y), atof(z));
			point_list->appendItem(new_point);
			break;

		case 't' : // uv coords, skip
			break;

		default : 
			break;
		}

		// read next line
		fgets(str, sizeof(str), fp);
		//printf("%s", str);
	}

	// seek for first poly line
	while(str[0] == 'g') {
		fgets(str, sizeof(str), fp); }

	while(!feof(fp))
	{
		switch (str[0])
		{
		case 'f' :
				// how many points for this face ?
				point_per_face = 0;
				for(i = 0; (str[i] != '\n') && (str[i] != '\0'); i++) {
					if (str[i] == ' ') point_per_face++; }

				switch (point_per_face)
				{
				case 3 :
					new_polygon = new Rpolygon();
					sscanf(str,"f %i %i %i %i", &(new_polygon->points[0]), &(new_polygon->points[1]), &(new_polygon->points[2]), &i);
					(new_polygon->points[0])--;
					(new_polygon->points[1])--;
					(new_polygon->points[2])--;
					polygon_list->appendItem(new_polygon);
					break;

				case 4 :
					new_polygon = new Rpolygon();
					sscanf(str,"f %i %i %i %i", &(new_polygon->points[0]), &(new_polygon->points[1]), &(new_polygon->points[2]), &i);
					(new_polygon->points[0])--;
					(new_polygon->points[1])--;
					(new_polygon->points[2])--;
					polygon_list->appendItem(new_polygon);

					new_polygon = new Rpolygon();
					sscanf(str,"f %i %i %i %i", &(new_polygon->points[0]), &i, &(new_polygon->points[1]), &(new_polygon->points[2]));
					(new_polygon->points[0])--;
					(new_polygon->points[1])--;
					(new_polygon->points[2])--;
					polygon_list->appendItem(new_polygon);
					break;

				default : 
					break;
						
				}
			break;

		default : 
			break;


		}
		// read next line
		fgets(str, sizeof(str), fp);
	}

	// build point table from point list
	point_count = point_list->itemCount();
	point_table = new Rpoint[point_count];

	point_list->gotoListHead();
	for(i = 0; i < point_count; i++)
	{
		point_list->gotoNextItem();
		new_point = (Rpoint *)point_list->getContent();
		point_table[i] = (*new_point);
	}

	// build polygon table from polygon list
	polygon_count = polygon_list->itemCount();
	polygon_table = new Rpolygon[polygon_count];

	printf("Rmesh::loadFileWavefront() found %i points, %i triangles\n", point_count, polygon_count);

	polygon_list->gotoListHead();
	for(i = 0; i < polygon_count; i++)
	{
		polygon_list->gotoNextItem();
		new_polygon = (Rpolygon *)polygon_list->getContent();
		polygon_table[i].points[0] = (*new_polygon).points[0];
		polygon_table[i].points[1] = (*new_polygon).points[1];
		polygon_table[i].points[2] = (*new_polygon).points[2];
	}

	delete polygon_list;
	delete point_list;

	fclose(fp);

	return true;
};

// dump geometry to an extremelly simplified obj file
//-------------------------------------------
int		Rmesh::saveFileWavefront(char *fname)
//-------------------------------------------
{
	// open Wavefront .obj file
	FILE *fp;
	int	i;

	fp = fopen( fname, "wa" );

	if( !fp )
	{
	   printf("Rmesh::loadFileWavefront() : file open error on %s.\n", fname );
	   return 0;
	}

	// object #1
	fprintf(fp, "o 1\n");

	// write down vertices
	for(i = 0; i < this->point_count; i++)
	{
		fprintf(fp,"v %f %f %f\n", this->point_table[i].x, this->point_table[i].y, this->point_table[i].z);
	}

	// write down polygons
	for(i = 0; i < this->polygon_count; i++)
	{
		fprintf(fp, "g\n");
		if (i == 0) { fprintf(fp, "usemtl Default\n"); }
		fprintf(fp, "f %i %i %i\n", this->polygon_table[i].points[0] + 1, this->polygon_table[i].points[1] + 1, this->polygon_table[i].points[2] + 1);
	}

	fclose(fp);

	return true;
}
