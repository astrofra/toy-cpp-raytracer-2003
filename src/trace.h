// Trace.h 

// C++ (ugly) code by http://fra.dozign.com
// In no event shall the author be liable for any indirect or
// consequential damages or loss of data resulting from use
// or performance of this software.

#include "gfxBuffer.h"
#include "itemList.h"
#include "math.h"

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

float		dotProduct(vector	, vector );
float		length(vector );
vector		normalize(vector );

class	CrenderContext
{
public:
	CrenderContext();
	~CrenderContext();  

	Ccolor_4f	Cs;		//	surface color
	Ccolor_4f	Os;		//	surface opacity

	Cpoint	P;		//	surface position
	Cpoint	I;		//	direction of ray hitting surface point (often from cam.)
	Cpoint	N;		//	surface shading normal
	Cpoint	Ng;		//	surface geometric normal 

	float	s,t;	//	Surface texture coordinates
};

#endif