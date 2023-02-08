#include "math.h"
#include "geometry.h"

#ifndef	TRACE_TOOLS
#define	TRACE_TOOLS

int	RayIntersectBoundingBox(Rpoint&, Rpoint&, Rpoint& , Rpoint& ,float&);

int	RayIntersectPoly(Rpoint& , Rpoint& , Rpoint& , Rpoint& , Rpoint& , float& );

#endif