// math.h

// C++ (ugly) code by http://fra.dozign.com
// In no event shall the author be liable for any indirect or
// consequential damages or loss of data resulting from use
// or performance of this software.

#ifndef	MATH_TOOLS
#define	MATH_TOOLS

//-------- Cpoint ------------------------

class Cpoint
{
public:
	Cpoint();
	Cpoint(double);
	Cpoint(double, double, double);
	~Cpoint();

	const double	getX();
	const double	getY();
	const double	getZ();

	Cpoint	operator+(Cpoint);
	Cpoint	operator+(double);

	Cpoint	operator-(Cpoint);
	Cpoint	operator-(double);

	Cpoint	operator*(Cpoint);
	Cpoint	operator*(double); 

private :
	double	x, y, z;
};
/*

//-------- Ccolor ------------------------

class Ccolor : public Cpoint
{
public:
	Ccolor();
	Ccolor(double);
	Ccolor(double, double, double);
	~Ccolor();

	const double	getR();
	const double	getG();
	const double	getB();
}

*/

#endif

