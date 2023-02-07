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
	hdr_pixel	diffuse_color;
};

struct vector
{
	point	origin;
	point	direction;
};

void		rawTrace();
hdr_pixel	traceRay(vector	, itemList *);
float		sphereIntersect(vector, sphere *);

#endif