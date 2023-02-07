// math.cpp

// C++ (ugly) code by http://fra.dozign.com
// In no event shall the author be liable for any indirect or
// consequential damages or loss of data resulting from use
// or performance of this software.

#include "math.h"

//-------- Cpoint ------------------------

Cpoint::Cpoint()
{	x = y = z = 0.0; }

Cpoint::Cpoint(double a)
{	x = y = z = a; }

Cpoint::Cpoint(double a, double b, double c)
{	x = a; y = b; z = c; }

Cpoint::~Cpoint() { };


const double Cpoint::getX()
{	return x; }

const double Cpoint::getY()
{	return y; }

const double Cpoint::getZ()
{	return z; }


Cpoint	Cpoint::operator+(Cpoint a)
{	return Cpoint(x + a.x, y + a.y, z + a.z); }

Cpoint	Cpoint::operator+(double b)
{	return Cpoint(x + b, y + b, z + b); }

Cpoint	Cpoint::operator-(Cpoint a)
{	return Cpoint(x - a.x, y - a.y, z - a.z); }

Cpoint	Cpoint::operator-(double b)
{	return Cpoint(x - b, y - b, z - b); }

Cpoint	Cpoint::operator*(Cpoint a)
{	return Cpoint(x * a.x, y * a.y, z * a.z); }

Cpoint	Cpoint::operator*(double b)
{	return Cpoint(x * b, y * b, z * b); }

