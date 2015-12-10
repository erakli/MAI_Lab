#include <math.h>

#include "Time.h"
#include "Functions.h"


double Date2JD(const TDate &Date){

	ushort year(Date.Year), month(Date.Month);
	double day(Date.Day);

	if (month <= 2)
	{
		year--;
		month += 12;
	}

	ushort A, B;

	A = (int)trunc(year / 100.0);
	B = 2 - A + (int)trunc(A / 4.0);

	double
		JD = trunc(365.25 * (year + 4716)) 
			+ trunc(30.6001 * (month + 1) + day + B - 1524.5);

	return JD;

}

TDate JD2Date(const double JD){

	TDate Result;

	// the integer part of JD + 0.5
	ulong Z = trunc(JD + 0.5);

	// the fractional (decimal) part of JD + 0.5
	double F = frac(JD); 

	ushort alpha, A;
	if (Z < 2299161)
		A = Z;
	else
	{
		alpha = trunc((Z - 1867216.25) / 36524.25);
		A = Z + 1 + alpha - trunc(alpha / 4.0);
	}

	ushort B, C, D, E;
	B = A + 1524;
	C = trunc((B - 122.1) / 365.25);
	D = trunc(365.25 * C);
	E = trunc((B - D) / 30.6001);

	// day of the month (with decimals)
	Result.Day = B - D - trunc(30.6001 * E) + F;

	// month number
	ushort m;
	if (E < 14) 
		m = E - 1;
	else
		if ((E = 14) || (E = 15))
			m = E - 13;

	// year
	ushort Year;
	if (m > 2)
		Year = C - 4716;
	else 
		if ((m = 1) || (m = 2))
			Year = C - 4715;

	Result.Month = m;
	Result.Year = Year;

}


/*
	Проверка на Високосный год

	true - Високосный год
*/
bool LeapYear(const ushort Year){

	if (
		((Year % 4 == 0) && (Year % 100 != 0))
		|| (Year % 400 == 0)
		)
		return true;
	else
		return false;

}


/*
	Получение количества дней с начала года
*/
ushort DayNumber(const TDate &Date){

	ushort Year(Date.Year), Month(Date.Month);
	double Day(Date.Day);

	// Флаг на то, високосный ли год
	ushort vis;
	if (LeapYear(Year))
		vis = 1; // для високосного года
	else
		vis = 2; // для обычного

	// Количество дней, прошедших с начала года
	ushort Day;
	Day =	trunc((275.0 * Month) / 9.0)
			- vis * trunc((Month + 9.0) / 12.0)
			+ trunc(Day) - 30;

	return Day;

}

ushort DayNumber(const double JD){

	// воспользовались предыдущей функцией
	return DayNumber(JD2Date(JD));

}