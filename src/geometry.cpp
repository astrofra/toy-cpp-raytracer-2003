// geometry.cpp

#include <memory.h>
#include <string>
#include <stdio.h>

#include "list.h"
#include "math.h"
#include "geometry.h"

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

//------------------------------------------------------------------------
int		Rmesh::RayIntersectBoundingBox(Rpoint& P, Rpoint& I, float& z_hit)
//------------------------------------------------------------------------
{
    // calculate x planes interval
    float tmin = -INTERSECTION_INFINITE;
    float tmax = INTERSECTION_INFINITE;

    if (I.x>0) {

        float t = (-P.x+bounding_box_max.x) / I.x; //x max
        if (t<tmin) return 0;  if (t<tmax) tmax = t;
        t = (-P.x+bounding_box_min.x) / I.x; //x min
        if (t>tmax) return 0;  if (t>tmin) tmin = t;
            
    } else if (I.x!=0) {

        float t = (-P.x+bounding_box_min.x) / I.x; //x max
        if (t<tmin) return 0;  if (t<tmax) tmax = t;
        t = (-P.x+bounding_box_max.x) / I.x; //x min
        if (t>tmax) return 0;  if (t>tmin) tmin = t;
            
    } else {
        
        if (P.x<bounding_box_min.x || P.x>bounding_box_max.x ) return 0;
        
    }
        
    // calculate y planes interval
    if (I.y>0) {

        float t = (-P.y+bounding_box_max.y) / I.y; //y max
        if (t<tmin) return 0;  if (t<tmax) tmax = t;
        t = (-P.y+bounding_box_min.y) / I.y; //y min
        if (t>tmax) return 0;  if (t>tmin) tmin = t;
            
    } else if (I.y!=0) {

        float t = (-P.y+bounding_box_min.y) / I.y; //y max
        if (t<tmin) return 0;  if (t<tmax) tmax = t;
        t = (-P.y+bounding_box_max.y) / I.y; //y min
        if (t>tmax) return 0;  if (t>tmin) tmin = t;
            
    } else {
        
        if (P.y<bounding_box_min.y || P.y>bounding_box_max.y ) return 0;
        
    }
        
	/*
    // calculate z planes interval
    if (I.z>0) {

        float t = (-P.z+bounding_box_max.z) / I.z; //z max
        if (t<tmin) return 0;  if (t<tmax) tmax = t;
        t = (-P.z+bounding_box_min.z) / I.z; //z min
        if (t>tmax) return 0;  if (t>tmin) tmin = t;
            
    } else if (I.z!=0) {

        float t = (-P.z+bounding_box_min.z) / I.z; //z max
        if (t<tmin) return 0;  if (t<tmax) tmax = t;
        t = (-P.z+bounding_box_max.z) / I.z; //z min
        if (t>tmax) return 0;  if (t>tmin) tmin = t;
            
    } else {
        
        if (P.z<bounding_box_min.z || P.z>bounding_box_max.z ) return 0;
        
    }
	*/

    z_hit = tmin;

	return 1;
}


//---------------------------------------------------------------------------------------
int		Rmesh::RayIntersectPoly(Rpoint& P, Rpoint& I, int& index_polygon, float& z_hit)
//---------------------------------------------------------------------------------------
{
	static Rpoint edge1, edge2, tvec, pvec, qvec;
	static float det,inv_det;
	static float t, u, v;
	static Rpoint	a,b,c;

	a = point_table[polygon_table[index_polygon].points[0]];
	b = point_table[polygon_table[index_polygon].points[1]];
	c = point_table[polygon_table[index_polygon].points[2]];

	edge1 = b; edge1 -= a;
	edge2 = c; edge2 -= a;
    
	pvec = I % edge2;

	det = edge1 * pvec;

	if (det > -INTERSECTION_EPSILON && det < INTERSECTION_EPSILON)
		return 0;
	
	inv_det = 1.0f / det;

	// calculate distance from vert0 to ray origin 
	tvec = P; tvec -= a;

	// calculate U parameter and test bounds 
	u = (tvec * pvec) * inv_det;

	if (u < 0.0 || u > 1.0f)
		return 0;

	// prepare to test V parameter 
	qvec = tvec % edge1;

	// calculate V parameter and test bounds 
	v = (I * qvec) * inv_det;

	if (v < 0.0 || u + v > 1.0)
		return 0;

	// calculate t, ray intersects triangle 
	z_hit = (edge2 * qvec) * inv_det;

   return 1;
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
