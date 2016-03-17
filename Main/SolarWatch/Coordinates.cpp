#include "Functions.h"
#include "Time.h"
#include "SolarSystem.h"

#include "Coordinates.h"

using namespace Earth;
using namespace MyFunc;

/*
	Звёздным временем называется часовой угол точки весеннего
	равноденствия (ТВР). Вычисление текущего гринвичского
	звёздного времени в секундах (часовой угол ТВР на гринвичском
	меридиане):
		TYPE s

	Результат:
		Угол ориентации гринвичского меридиана, соответствующего
		периоду 0 - 2Pi, по отношению к направлению в ТВР в радианах.
*/
TYPE StarTime(const TYPE& JD)
{
	TYPE
		d = JD - J2000,			// количество дней с 01.01.2000
		centuries = d / 36525;	// количество столетий, прошедших с 01.01.2000 г.

	TYPE s =
		67310.54841
		+ 8640184.812866 * centuries
		+ 0.093104 * Numbers::pow2(centuries)
		- 6.2e-6 * Numbers::pow3(centuries);

	return
		2 * PI / SECINDAY * fmod(s, SECINDAY);
}


/*
	Прямой расчёт текущего звёздного времени места s

	результат в радианах
*/
TYPE StarTime(const TYPE& JD, const TYPE& lambda)
{
	TYPE 
		t = (Numbers::frac(JD) + 0.5) * SECINDAY;	// t – время по шкале UTC в сек

	return 
		StarTime(JD) + CEarth::angularVeloc * t + lambda;
}


/*
	перевод из сферических в декартовы координаты

	углы в радианах

	[h, fi, lambda] - высота, широтаб долгота
*/
CVector Transform::Geographic2Fix(const CVector &geographic)
{
	auto 
		h(geographic[0]), 
		fi(geographic[1]), 
		lambda(geographic[2]);

	CVector Result(3);
	Result[0] = (h + CEarth::meanRadius) * cos(fi) * cos(lambda);
	Result[1] = (h + CEarth::meanRadius) * cos(fi) * sin(lambda);
	Result[2] = (h + CEarth::meanRadius) * sin(fi);

	return Result;
}