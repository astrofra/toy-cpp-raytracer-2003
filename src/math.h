// math.h

#include <stdlib.h>

#ifndef	MATH_TOOLS
#define	MATH_TOOLS

//-------- Misc tools ------------------------

#define	MIN_VALUE(V, MIN_VAL) (V < MIN_VAL ? V : MIN_VAL)
#define	MAX_VALUE(V, MAX_VAL) (V > MAX_VAL ? V : MAX_VAL)
#define	BOUND_VALUE(V, MIN_VAL, MAX_VAL) (MAX_VALUE(MIN_VALUE(V, MIN_VAL), MAX_VAL))
#define	ABS_VALUE(A) (A < 0.0f ? (-A) : (A)) 

#define RAND(A)	(rand()%1000 / 1000.0f) * (A)

#define	INTERSECTION_EPSILON	0.000001f
#define INTERSECTION_INFINITE	(1.0f / INTERSECTION_EPSILON)

unsigned char	floatToUnsignedChar(float);

float			unsignedCharToFloat(unsigned char);

//-------- Rpoint ------------------------

class Rpoint
{
public:
	Rpoint();
	Rpoint(float);
	Rpoint(float, float, float);
	~Rpoint();

	void	normalize();
	float	length();

	Rpoint	operator+(Rpoint&); // translation
	Rpoint	operator+(float&); 
	Rpoint&	operator+=(Rpoint&);
	Rpoint&	operator+=(float&);

	Rpoint	operator-(Rpoint&);
	Rpoint	operator-(float&); 
	Rpoint&	operator-=(Rpoint&);
	Rpoint&	operator-=(float&);

	Rpoint	operator*(float&); // scale
	Rpoint&	operator*=(float&); // scale

	Rpoint	operator%(Rpoint&); // cross product

	float	operator*(Rpoint&); // dot product

	float	x, y, z;
};

//-------- Rcolor ------------------------

class Rcolor
{
public:
	Rcolor();
	Rcolor(float);
	Rcolor(float, float, float);
	~Rcolor();
	float	luminance();

	Rcolor	operator+(Rcolor&);
	Rcolor	operator+(float&);
	Rcolor&	operator+=(Rcolor&);

	Rcolor	operator-(Rcolor&);
	Rcolor	operator-(float&);

	Rcolor	operator*(Rcolor&);
	Rcolor	operator*(float&);
	Rcolor&	operator*=(Rcolor&);
	Rcolor&	operator*=(float&);

	float	r, g, b;
};

#endif

