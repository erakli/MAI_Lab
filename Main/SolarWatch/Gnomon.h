#pragma once

#include "Matrix_classes.h"
#include "Model.h"
#include "SolarSystem.h"

#define PRECISION 1.0e-12

class CGnomon
{
private:
	TYPE height; // высота гномона (в километрах)

	// храним положение гномона в географической СК
	CVector position, curPosition;

	TYPE starTimeAtStart;	// звёздное время на начало вычислений

	CMatrix 
		earthPosition_Day,	// положение Земли на начала каждого дня до нужной даты
		earthPosition_Minute; // положение Земли на определённый день

	TYPE lastActual_JD;	// последняя дата с известной позицией Земли

	//UINT interval; // интервал получаемых положений Земли (кол-во минут)

	SINT timeZone;

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
		const bool WorkTime,
		CMatrix &days_of_year, UINT &day_number, bool &SunriseGot, 
		const TYPE scalarProd, const TYPE delta, const int i);

	CMatrix SimulateShadow(const bool WorkTime = false, const bool days = true);

	List Result;	// храним значения вектора тени
	int Result_size;
	void addResult(const CVector &X);
	CMatrix getResult();
	void clearResult();

public:
	CGnomon() : 
		height(1.0e-3), starTimeAtStart(0), lastActual_JD(0), 
		timeZone(0), Result_size(0)
	{
		position.setSize(3);
	};
	CGnomon(const TYPE fi, const TYPE lambda, const SINT timeZone = 0,
		    const TYPE height = 1.0e-3);

	void setParam(const TYPE fi, const TYPE lambda, const SINT timeZone = 0,
				  const TYPE height = 1.0e-3);

	CMatrix GetShadowForDate(const TYPE JD);
	CVector GetLightTimeForYear();

};