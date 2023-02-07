// Trace.h 
//

#include "gfxBuffer.h"

#ifndef	TRACE
#define	TRACE

#define	qSQR(A)	(float)((A) * (A))

struct	point
{
	float	x, y, z;
};

struct vector
{
	point	origin;
	point	direction;
};

void		rawTrace();
hdr_pixel	traceRay(vector );
float		sphereIntersect(vector, point, float);

#endif