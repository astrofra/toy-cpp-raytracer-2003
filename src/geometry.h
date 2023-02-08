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
	int getPoint(int i) { return points[i]; };

	Rcolor&	getCs() { return Cs; };
	Rpoint&	getN() { return N; };

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
	void	translate(Rpoint&);
	void	rotateX(Rpoint&, float);
	void	preshade();

	void	printBoundingBox();

	// datas
	int			point_count;
	int			polygon_count;
		
	Rpoint		*point_table;
	Rpolygon	*polygon_table;

	Rpoint		bounding_box_min, bounding_box_max;
};

#endif