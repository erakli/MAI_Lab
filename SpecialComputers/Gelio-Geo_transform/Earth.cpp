#include "Earth.h"
#include "Time.h"
#include "Functions.h"

/*
	положение Земли относительно Солнца

	Уточнить про начало отсчёта
*/
coord EarthPos(const double JD){

	TDate Date = JD2Date(JD);
	ushort Year(Date.Year);

	// Угол, на который смещается Земля каждый день
	double
		angle = (LeapYear(Year)) ? DEGINDAY : DEGINDAY_LEAP;

	// Время, прошедшее с начала года в днях
	double
		Day = DayNumber(Date) + frac(JD);

	/* 
		Угол, на который Земля отстоит от начала отсчёта 
		в плоскости эклиптики
	*/
	double 
		alpha = Day * angle;

	/*
		Получаем положение Земли относительно Солнца в 
		декартовой СК

		фи принимаем = 0 градусам (типо в плоскости эклиптики)
	*/
	coord Pos = Spher2Fix(AU, 0, deg2rad(alpha));

	return Pos;
}


/*
	Перевод из Гелицентрического положения в Геоцентрическое

	время в Юлианских днях
*/
coord GeoPos(const double Time, coord Pos){

	coord Earth = EarthPos(Time);

	coord NewPos = new double[VECSIZE];

	for (ushort i = 0; i < VECSIZE; i++)
		*(NewPos + i) = *(Pos + i) - *(Earth + i);

	return NewPos;
}