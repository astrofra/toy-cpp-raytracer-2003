// light.cpp

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
}

//-------------------
Rlight::~Rlight() {};
//-------------------

//------------------------------------------
Rpoint &Rlight::getLightDirection(Rpoint &P)
//------------------------------------------
{
	static Rpoint	L;
	
	L = position;
	L -= P;
	L.normalize();

	return L;
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
