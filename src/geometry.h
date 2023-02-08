// geometry.h

#include "math.h"

#ifndef	GEOMETRY
#define	GEOMETRY

//-------- Rsphere ------------------------

class Rsphere
{
public :
	Rsphere();
	~Rsphere();

	float	x, y, z;
	float	radius;
	Rcolor	color;
	float	reflection;
};

//-------- Robject ------------------------

class Robject
{
public:
	Robject();
	~Robject();

	int		loadFileCSG(char *);
	int		saveFileCSG(char *);

	void	scale(float );
	void	translate(Rpoint&);

	// datas
	int		count;		
	Rsphere	*sphere_table;
};

#endif