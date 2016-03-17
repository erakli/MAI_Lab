#pragma once

#include "Types.h"

#define J2000 2451544.5 // ��������� ���� �� 0:00 01.01.2000
#define  SECINDAY 86400

namespace MyTime
{
	// ����������� ����
	struct Date
	{
		SINT year;
		BYTE 
			month, day, 
			hour, minute, second;
	};

	namespace Transformation
	{
		// ������� �� ����������� ���� � ��������� ���
		TYPE DateToJD(const Date &date);
	}

}
