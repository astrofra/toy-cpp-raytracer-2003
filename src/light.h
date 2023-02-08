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

	Rpoint &getLightDirection(Rpoint &);
	Rcolor &getColor() { return color; };
	float &getIntensity() { return intensity; };

	setPosition(Rpoint &);
	setColor(Rcolor &);
	setIntensity(float &);
	setFalloff(float &);
	setRadius(float &);

private:
	Rpoint	position;
	Rcolor	color;
	float	intensity;
	float	falloff;
	float	radius;
};

#endif