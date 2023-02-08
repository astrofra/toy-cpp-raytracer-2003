// geometry.h

#include "math.h"

#ifndef	GEOMETRY
#define	GEOMETRY

//-------- Rpolygon ------------------------

class Rpolygon
{
public:
	Rpolygon();
	~Rpolygon();

	void	computeNormal();

private:
	unsigned int	points[3];
	Rpoint			N;		//	surface geometric normal
	Rcolor			Cs;		//  surface color

	friend class Rmesh;
};

//-------- Rmesh ------------------------

class Rmesh
{
public:
	Rmesh();
	~Rmesh();

	int		loadFileWavefront(char *);
	int		saveFileWavefront(char *);

	void	computeNormals();
	void	computeBoundingBox();
	void	scale(float );

	void	printBoundingBox();

	int		RayIntersectPoly(Rpoint& , Rpoint& , int&, float&);
	int		RayIntersectBoundingBox(Rpoint& , Rpoint&, float&);

	// datas
	int			point_count;
	int			polygon_count;
		
	Rpoint		*point_table;
	Rpolygon	*polygon_table;

	Rpoint		bounding_box_min, bounding_box_max;
};

#endif