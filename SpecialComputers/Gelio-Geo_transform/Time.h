#pragma once

#include "Types.h"


struct TDate{
	ushort Year, Month;
	double Day;
};

double Date2JD(const TDate &Date);
TDate JD2Date(const double JD);

inline bool LeapYear(const ushort Year);

ushort DayNumber(const TDate &Date);
ushort DayNumber(const double JD);