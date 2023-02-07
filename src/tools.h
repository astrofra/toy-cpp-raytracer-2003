// tools.h

#ifndef COMMON_TOOLS
#define COMMON_TOOLS

#define	MIN_VALUE(V, MIN_VAL) (V < MIN_VAL ? MIN_VAL : V)
#define	MAX_VALUE(V, MAX_VAL) (V > MAX_VAL ? MAX_VAL : V)
#define	BOUND_VALUE(V, MIN_VAL, MAX_VAL) (MAX_VALUE(MIN_VALUE(V, MIN_VAL), MAX_VAL))

unsigned char	floatToUnsignedChar(float);

float			unsignedCharToFloat(unsigned char);

#endif