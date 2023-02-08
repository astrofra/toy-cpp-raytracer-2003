// geometry.cpp

#include <memory.h>
#include <string>
#include <stdio.h>

#include "list.h"
#include "math.h"
#include "geometry.h"

//-------- Rpolygon ------------------------

//-------------------------------
void	Rpolygon::computeNormal()
//-------------------------------
{
	Rpoint a,b;

	a = points[0] - points[1]; // get 2 arbitrary vectors from polygon
	b = points[0] - points[2];

	a.normalize();
	b.normalize();

	N = a % b; // cross product to get normal
}

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
	// for every point
	for(int i = 0; i <= this->point_count; i++)
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

//-----------------------------
void	Rmesh::computeNormals()
//-----------------------------
{
	// for every polygon
	for (int i = 0; i <= this->polygon_count; i++)
		this->polygon_table[i].computeNormal(); //current_poly.computeNormal();
}


//--------------------------------------
int		Rmesh::loadFileWavefront(char *fname)
//--------------------------------------
{
	// create vertex & polygons lists
	Rlist	*point_list,
			*polygon_list;

	char	str[1024];

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

	while(str[0] != 'v')// seek for first vertex line
	{
		// read line
		fgets(str, sizeof(str), fp);
		//printf("%s", str);
	}

	float	x,y,z;




	// for every point found
	while(str[0] == 'v')
	{
		switch (str[1])
		{
		case ' ' :
			// get point datas
			sscanf(str,"v %f %f %f", &x, &y, &z);
			printf("found vertex (%f, %f, %f) \n", x, y, z);
			// add each point
			//point_list->appendItem("new_poly");
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
	{
		// read line
	}

	// for every polygon found
	{
		// get poly datas, atoi()

		// how many points for this face ?
		//switch (point_count)
		{
			//3 :
			//	poly_list = poly;
			
			//4 :
			{
				// add (point[0],point[1],point[2]) to poly_list;
				// add (point[2],point[3],point[4]) tp poly_list;
			}

			// >4
			{
				// skip it :'(
			}

			// add poly_list;

				
		}
		// read next line
	}

	/*
	point_count = point_list->itemCount();
	point_table = new Rpoint[point_count];

	polygon_count = polygon_list->itemCount();
	polygon_table = new Rpolygon[polygon_count];
	*/

	return true;
};

