#include "trace.h"

//-------------------------------------------------------------------------------------------------------------------
int	RayIntersectBoundingBox(Rpoint& P, Rpoint& I, Rpoint& bounding_box_min, Rpoint& bounding_box_max, float& z_hit)
//-------------------------------------------------------------------------------------------------------------------
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
	

    z_hit = tmin;

	return 1;
}


//--------------------------------------------------------------------------
int	RayIntersectPoly(Rpoint& P, Rpoint& I, Rpoint& a, Rpoint& b, Rpoint& c, float& z_hit)
//--------------------------------------------------------------------------
{
	Rpoint edge1, edge2, tvec, pvec, qvec;
	float det,inv_det;
	float t, u, v;
	//static Rpoint	a,b,c;

	/*a = point_table[polygon_table[index_polygon].points[0]];
	b = point_table[polygon_table[index_polygon].points[1]];
	c = point_table[polygon_table[index_polygon].points[2]];*/

	edge1 = b - a;
	edge2 = c - a;
    
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