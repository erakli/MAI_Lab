#pragma once

#include "Types.h"

#define DEGINHOUR 360 / 24.0

#define DEGINDAY 360 / 365.0
#define DEGINDAY_LEAP 360 / 366.0

#define AU 1.49597870700e+11 // Астрономическая единица, м

coord EarthPos(const double JD);
coord GeoPos(const double Time, coord Pos);

/*
	Осталось 
		реализовать перевод из инерциальной в связанную

		понять с началом отсчёта в вычислении положения Земли
*/