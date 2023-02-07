// Trace.h 
//

#include "gfxBuffer.h"
#include "itemList.h"

#ifndef	TRACE
#define	TRACE

#define	qSQR(A)	(float)((A) * (A))


struct	point
{
	float	x, y, z;
};

struct sphere
{
	point		center;
	float		radius;
	Ccolor_4f	diffuse_color;
};

struct vector
{
	point	origin;
	point	direction;
};

void		rawTrace();
Ccolor_4f	traceRay(vector	, itemList *);
float		sphereIntersect(vector, sphere *);
float dotProduct(vector	, vector );

#endif