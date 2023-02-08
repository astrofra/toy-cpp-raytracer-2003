// math.h

#include <stdlib.h>

#ifndef	MATH_TOOLS
#define	MATH_TOOLS

//-------- Misc tools ------------------------

#define	MIN_VALUE(V, MIN_VAL) (V < MIN_VAL ? MIN_VAL : V)
#define	MAX_VALUE(V, MAX_VAL) (V > MAX_VAL ? MAX_VAL : V)
#define	BOUND_VALUE(V, MIN_VAL, MAX_VAL) (MAX_VALUE(MIN_VALUE(V, MIN_VAL), MAX_VAL))

#define RAND(A)	(rand()%1000 / 1000.0f) * (A)

unsigned char	floatToUnsignedChar(float);

float			unsignedCharToFloat(unsigned char);

//-------- Rpoint ------------------------

class Rpoint
{
public:
	Rpoint();
	Rpoint(double);
	Rpoint(double, double, double);
	~Rpoint();

	void	normalize();
	double	length();

	Rpoint	operator+(Rpoint);
	Rpoint	operator+(double);

	Rpoint	operator-(Rpoint);
	Rpoint	operator-(double);

	Rpoint	operator*(double);

	Rpoint	operator%(Rpoint); // cross product

	double	operator*(Rpoint); // dot product

	double	x, y, z;
};

//-------- Rcolor ------------------------

class Rcolor
{
public:
	Rcolor();
	Rcolor(double);
	Rcolor(double, double, double);
	~Rcolor();

	Rcolor	operator+(Rcolor);
	Rcolor	operator+(double);

	Rcolor	operator-(Rcolor);
	Rcolor	operator-(double);

	Rcolor	operator*(Rcolor);
	Rcolor	operator*(double);

	double	r, g, b;
};

#endif

