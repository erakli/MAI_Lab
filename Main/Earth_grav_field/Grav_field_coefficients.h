#pragma once

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
		 7.53770461,
		-1.62110461,
		-1.62110461,
		 5.88921919,
		 5.88921919,
		-7.53696689,
		-7.53696689
	};

	TYPE
		J_02 =  1082625.7e-9,	// = -sqrt(5) * C_0_20
		J_04 = -2370.9e-9;		// = -3 * C_0_40
}