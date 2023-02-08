// light.cpp
#include <stdio.h>

#include "light.h"

//-------- Rlight ------------------------

//--------------
Rlight::Rlight()
//--------------
{
	position	=	Rpoint(0.0f, 100.0f, 0.0f);
	color		=	Rcolor(1.0f);
	intensity	=	1.0f;
	falloff		=	-1.0f;
	radius		=	0.0f;
	type		=	1;
}

//-----------------------
Rlight::Rlight(Rpoint &p)
//-----------------------
{
	position	=	p;
	color		=	Rcolor(1.0f);
	intensity	=	1.0f;
	falloff		=	-1.0f;
	radius		=	0.0f;
	type		=	1;
}

//-------------------
Rlight::~Rlight() {};
//-------------------

//------------------------------------------
Rpoint &Rlight::getLightDirection(Rpoint &P)
//------------------------------------------
{
	Rpoint	L;

	switch (type)
	{
		case 0 :
			L = Rpoint(0.0);
			printf("Rlight::getLightDirection(), Ambiant Light cannot return 'direction'\n");
			break;

		case 1 :
			L = position; //position;
			L -= P; //P;
			L.normalize();
			break;
	}

	return L;
}

//----------------------------
Rlight::setType(int	i)
//----------------------------
{
	type = i;
}

//----------------------------
Rlight::setPosition(Rpoint &p)
//----------------------------
{
	position = p;
}

//-------------------------
Rlight::setColor(Rcolor &c)
//-------------------------
{
	color = c;
}

//----------------------------
Rlight::setIntensity(float &f)
//----------------------------
{
	intensity = f;
}

//--------------------------
Rlight::setFalloff(float &f)
//--------------------------
{
	falloff = f;
}

//-------------------------
Rlight::setRadius(float &f)
//-------------------------
{
	radius = f;
}
