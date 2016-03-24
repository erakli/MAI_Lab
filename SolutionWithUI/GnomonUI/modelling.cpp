#include "Functions.h"
#include "Gnomon.h"

#include "modelling.h"

using namespace std;
using namespace MyFunc;

CGnomon gnomon;

CMatrix GenerateShadow(const MyTime::Date &date, const Coordinates &coord, const TYPE height)
{
	TYPE
		// минуты дуги сразу приводим к градусам
		fi = Numbers::deg2rad(coord.fi_deg + coord.fi_min / 60.0),
		lambda = Numbers::deg2rad(coord.lambda_deg + coord.lambda_min / 60.0);

	TYPE JD = MyTime::Transformation::DateToJD(date);

	gnomon.setParam(fi, lambda, height * 1.0e-3);	// высоту приводим к км

	return gnomon.GetShadowForDate(JD);
}