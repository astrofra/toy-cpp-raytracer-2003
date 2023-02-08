// light.h

#include "math.h"

#ifndef	LIGHT
#define	LIGHT

//-------- Rlight ------------------------

class Rlight
{
public:
	Rlight();
	Rlight(Rpoint &);
	~Rlight();

	Rpoint	&getLightDirection(Rpoint &);
	Rcolor	&getColor() { return color; };
	float	&getIntensity() { return intensity; };
	int		&getType() { return type;};

	setType(int);
	setPosition(Rpoint &);
	setColor(Rcolor &);
	setIntensity(float &);
	setFalloff(float &);
	setRadius(float &);

private:
	int		type;  // 0 = AMBIANT LIGHT , type 1 = POINT LIGHT
	Rpoint	position;
	Rcolor	color;
	float	intensity;
	float	falloff;
	float	radius;
};

#endif