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
		C_0_20 = -484165.0e-9,
		C_0_40 =  790.3e-9;	
}