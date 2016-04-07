#include "Matrix_classes.h"

namespace Earth
{
#define MASSPOINTS 7

	/* Позиции точечных масс, km */
	TYPE massPositions[MASSPOINTS][VEC_SIZE] =
	{
		{ 0, 0,	   0 },
		{ 0, 0,  300 },
		{ 0, 0, -300 },
		{ 0, 0,  250 },
		{ 0, 0, -250 },
		{ 0, 0,  180 },
		{ 0, 0, -180 }
	};

	/* Сами точечные массы */
	TYPE massValues[MASSPOINTS] = 
	{
		 7.53770461e+10,
		-1.62110461e+10,
		-1.62110461e+10,
		 5.88921919e+10,
		 5.88921919e+10,
		-7.53696689e+10,
		-7.53696689e+10
	};

	TYPE
		J_02 =  1082625.7e-9,	// = -sqrt(5) * C_0_20
		J_04 = -2370.9e-9;		// = -3 * C_0_40
}