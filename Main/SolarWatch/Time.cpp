#include "Functions.h"

#include "Time.h"

/*
	Перевод календарной даты в Юлианские дни
*/
TYPE MyTime::Transformation::DateToJD(const Date &date)
{
	BYTE
		a = (14 - date.month) / 12,
		M = date.month + 12 * a - 3;

	SINT Y = date.year + 4800 - a;

	UINT JDN = 
		date.day + ((153 * M + 2) / 5) 
		+ 365 * Y 
		+ (Y / 4) - (Y / 100) 
		+ (Y / 400) - 32045;

	return 
		JDN 
		+ (date.hour - 12) / 24.0
		+ date.minute / 1440.0
		+ date.second / TYPE(SECINDAY);
}