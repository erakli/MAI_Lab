#pragma once

#include "Types.h"

#define J2000 2451544.5 // юлианская дата на 0:00 01.01.2000
#define  SECINDAY 86400

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

	namespace Transformation
	{
		// перевод из календарной Даты в Юлианские дни
		TYPE DateToJD(const Date &date);
	}

}
