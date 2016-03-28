#include "Functions.h"
#include "Gnomon.h"

#include "modelling.h"

using namespace std;
using namespace MyFunc;

CGnomon gnomon;

CMatrix GenerateShadow(
	const MyTime::Date &date, const Coordinates &coord,
	const SINT timeZone, const TYPE height)
{
	TYPE
		// ������ ���� ����� �������� � ��������
		fi = Numbers::deg2rad(coord.fi_deg + coord.fi_min / 60.0),
		lambda = Numbers::deg2rad(coord.lambda_deg + coord.lambda_min / 60.0);

	TYPE JD = MyTime::Transformation::DateToJD(date);

	gnomon.setParam(fi, lambda, timeZone, height * 1.0e-3);	// ������ �������� � ��

	return gnomon.GetShadowForDate(JD);
}

CVector GetLightTime(
	const Coordinates &coord, const SINT timeZone, 
	const bool WorkTime, const bool Switch)
{
	TYPE
		// ������ ���� ����� �������� � ��������
		fi = Numbers::deg2rad(coord.fi_deg + coord.fi_min / 60.0),
		lambda = Numbers::deg2rad(coord.lambda_deg + coord.lambda_min / 60.0);

	gnomon.setParam(fi, lambda, timeZone, 1.0e-3);	// ����� 1 ���� � ������

	return gnomon.GetLightTimeForYear(WorkTime, Switch);
}