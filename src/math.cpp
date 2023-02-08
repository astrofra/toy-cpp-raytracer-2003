// math.cpp

#include <MATH.H>
#include "math.h"

//-------- Misc tools ------------------------

//------------------------------------------
unsigned char	floatToUnsignedChar(float value_in)
//------------------------------------------
{
	if (value_in < 0.0f) return 0;
	if (value_in > 1.0f) return 255;

	return ((unsigned char)(value_in * 255.0f));
}

//------------------------------------------
float	unsignedCharToFloat(unsigned char value_in)
//------------------------------------------
{
	return ( ((float)value_in) / 255.0f );
}

/*
//-------- Quasi Random ------------------
QuasiRandom::QuasiRandom() { rand_index = 0; }

QuasiRandom::~QuasiRandom(); { }

QuasiRandom::getIntQuasiRandom(const int &range)
{
	int temp_rand;
	temp_rand = reinterpret_cast<int>rand_table[gotoNextRand()];
	return (temp_rand);

}
*/

//-------- Rpoint ------------------------

Rpoint::Rpoint()
{	x = y = z = 0.0;}

Rpoint::Rpoint(float a)
{	x = y = z = a;}

Rpoint::Rpoint(float a, float b, float c)
{	x = a; y = b; z = c;}

Rpoint::~Rpoint() { };

void Rpoint::normalize()
{
	float l = 1.0f / this->length();
	x *= l; y *= l; z *= l;
}

float Rpoint::length()
{	return ((float)sqrt(x * x + y * y + z * z)); }

Rpoint	Rpoint::operator+(Rpoint &a)
{	return Rpoint(x + a.x, y + a.y, z + a.z); }

Rpoint	Rpoint::operator+(float &b)
{	return Rpoint(x + b, y + b, z + b); }

Rpoint	&Rpoint::operator+=(Rpoint &a)
{	
	x += a.x;	
	y += a.y;
	z += a.z;
	return *this;
}

Rpoint	&Rpoint::operator+=(float &b)
{	
	x += b;	
	y += b;
	z += b;
	return *this;
}

Rpoint	Rpoint::operator-(Rpoint &a)
{	return Rpoint(x - a.x, y - a.y, z - a.z); }

Rpoint	Rpoint::operator-(float &b)
{	return Rpoint(x - b, y - b, z - b); }

Rpoint	&Rpoint::operator-=(Rpoint &a)
{	
	x -= a.x;	
	y -= a.y;
	z -= a.z;
	return *this;
}

Rpoint	&Rpoint::operator-=(float &b)
{	
	x -= b;	
	y -= b;
	z -= b;
	return *this;
}

Rpoint	Rpoint::operator*(float &b)	// scale
{	return Rpoint(x * b, y * b, z * b); }

Rpoint	&Rpoint::operator*=(float &b)
{	
	x *= b;	
	y *= b;
	z *= b;
	return *this;
}

float	Rpoint::operator*(Rpoint &a)	// dot product
{	return (x * a.x + y * a.y + z * a.z); }

Rpoint	Rpoint::operator%(Rpoint &a) // cross product
{
	Rpoint b;
	b.x = y * a.z - a.y * z;
	b.y = z * a.x - a.z * x;
	b.z = x * a.y - a.x * y;
	return b;
}

//-------- Rcolor ------------------------

Rcolor::Rcolor()
{	r = g = b = 0.0;}

Rcolor::Rcolor(float a)
{	r = g = b = a;}

Rcolor::Rcolor(float i, float j, float k)
{	r = i; g = j; b = k;}

Rcolor::~Rcolor() { };

float	Rcolor::luminance()
{
	return ((r + g + b) * 0.3333333f); // wrong coefs !!!
}

Rcolor	Rcolor::operator+(Rcolor& a)
{	return Rcolor(r + a.r, g + a.g, b + a.b); }

Rcolor	Rcolor::operator+(float& a)
{	return Rcolor(r + a, g + a, b + a); }

Rcolor&	Rcolor::operator+=(Rcolor& a)
{	
	r += a.r;
	g += a.g;
	b += a.b;

	return *this;
}

Rcolor	Rcolor::operator-(Rcolor& a)
{	return Rcolor(r - a.r, g - a.g, b - a.b); }

Rcolor	Rcolor::operator-(float& a)
{	return Rcolor(r - a, g - a, b - a); }

Rcolor	Rcolor::operator*(Rcolor& a)
{	return Rcolor(r * a.r, g * a.g, b * a.b); }

Rcolor	Rcolor::operator*(float& a)
{	return Rcolor(r * a, g * a, b * a); }

Rcolor&	Rcolor::operator*=(Rcolor& a)
{	
	r *= a.r;
	g *= a.g;
	b *= a.b;

	return *this;
}

Rcolor&	Rcolor::operator*=(float& a)
{	
	r *= a;
	g *= a;
	b *= a;

	return *this;
}
