#pragma once

#include "Matrix_classes.h"
#include "Model.h"
#include "SolarSystem.h"

#define PRECISION			1.0e-12

/* Дни перевода часов. Отсчёт с 0 дня */
#define	LASTSUNDAY_march	85
#define LASTSUNDAY_october	302

#define SWITCH2SUMMER		LASTSUNDAY_march * MININDAY + 2 * MININHOUR
#define SWITCH2WINTER		LASTSUNDAY_october * MININDAY + 3 * MININHOUR

class CGnomon
{
private:
	TYPE height; // высота гномона (в километрах)

	// храним положение гномона в географической СК
	CVector position, curPosition;

	TYPE starTimeAtStart;	// звёздное время на начало вычислений

	bool WeGotPositionsForYear;	// флаг на то, что у нас есть посчитанный год положений Земли

	CMatrix 
		earthPosition_Day,	// положение Земли на начала каждого дня до нужной даты
		earthPosition_Minute; // положение Земли на определённый день

	TYPE lastActual_JD;	// последняя дата с известной позицией Земли

	//UINT interval; // интервал получаемых положений Земли (кол-во минут)

	SINT timeZone;

	bool WorkTime; // флаг на ограничение вычисления светлого времени в диапазоне 8-20
	bool SummerWinterTime_switch; // флаг на наличие смены Летнего времени на Зимнее

	bool DoWeHaveThisDate(const TYPE theDate, Earth::CEarth &Mod);

	/* 
		сделать последнее вычисленное значение начальными условиями нового
		интегрирования */
	void MakeNewStartConditions(Earth::CEarth &Mod);

	//void MakeNewStartConditions_forTimeZone(
	//	Earth::CEarth &Mod, CDormanPrince &Integrator, const TYPE timeMoment);

	// вычисляем положение Земли на искомую дату (на основе эфемерид)
	void getEarthPosition(const TYPE JD, const bool day = true);

	// вычисляем положение гномона на текущий момент
	CVector getPosition(const TYPE t);

	void CountTimeInDay(
		CMatrix &days_of_year, const TYPE scalarProd, const TYPE delta, const int i);

	CMatrix SimulateShadow(const bool days = true);

	List Result;	// храним значения вектора тени
	int Result_size;
	void addResult(const CVector &X);
	CMatrix getResult();
	void clearResult();

public:
	CGnomon();
	CGnomon(const TYPE fi, const TYPE lambda, const SINT timeZone = 0,
		    const TYPE height = 1.0e-3);

	void setParam(const TYPE fi, const TYPE lambda, const SINT timeZone = 0,
				  const TYPE height = 1.0e-3);

	CMatrix GetShadowForDate(const TYPE JD);
	CVector GetLightTimeForYear(const bool WorkTime, const bool Time_switch);

};