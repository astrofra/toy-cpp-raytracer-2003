// tools.cpp

#include <stdio.h>

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