#pragma once

#include "Types.h"
#include "Functions.h"

#define DEGINHOUR 360 / 24.0

#define DEGINDAY 360 / 365.0
#define DEGINDAY_LEAP 360 / 366.0

#define AU 1.49597870700e+11 // Астрономическая единица, м

coord EarthPos(const double JD); // понять с началом отсчёта в вычислении положения Земли

/*
	Угол (в рад), на который повернулась Земля относительно начала суток

	Время в Юлианских днях
*/
inline double EarthRotAngle(const double Time){
	return 4 * PI * frac(Time);
}