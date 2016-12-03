#pragma once

#include "Types.h"

#define J2000		2451544.5 // юлианская дата на 0:00 01.01.2000

#define SECINMIN	60.0
#define SECINHOUR	3600.0
#define	SECINDAY	86400.0

#define MININHOUR	60.0
#define MININDAY	1440.0

#define HOURINDAY	24.0


namespace MyTime
{
	// календарная дата
	struct Date
	{
		SINT year;
		BYTE 
			month, day, 
			hour, minute, second;
	};

	TYPE getMidnight(const TYPE JD);

	namespace Transformation
	{
		// перевод из календарной Даты в Юлианские дни
		TYPE DateToJD(const Date &date);
	}

}
