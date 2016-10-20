#include "Dorman-Prince_modified.h"

#define STEP_CORRECTION

//#define ORDER 1.0e-7

/* Округление до необходимого знака после запятой */
//void RoundTo(TYPE &value, const TYPE order)
//{
//	TYPE
//		rounded_value = ceil(value),
//		difference = rounded_value - value;
//
//	/* 
//		Если разница между округлённым вверх значением и самим числом меньше 
//		заданного порядка, то считаем, что число является уже округлённым
//	*/
//	if (difference < order && difference != 0)
//		value = rounded_value;
//}

/* * * * * * * * * * CDormanPrince_modified * * * * * * * * * */

CDormanPrince_modified::CDormanPrince_modified()
{
	correlation_interval = 0;
}

CDormanPrince_modified::CDormanPrince_modified(const TYPE correlation_interval)
{
	Step = correlation_interval; // начальный шаг делаем равным интервалу корреляции
	this->correlation_interval = correlation_interval;
}

void CDormanPrince_modified::set_correlation_interval(const TYPE correlation_interval)
{
	Step = correlation_interval;
	this->correlation_interval = correlation_interval;
}

TYPE CDormanPrince_modified::StepCorrection()
{
#ifdef STEP_CORRECTION
	TYPE NewStep = CDormanPrince::StepCorrection();

	if (NewStep > correlation_interval)
		NewStep = correlation_interval;

	return NewStep;
#endif

#ifndef STEP_CORRECTION
	return Step;
#endif
}

void CDormanPrince_modified::getError()
{
	//CDormanPrince::getError();
	
	if (Error > Eps_Max)
		Error = 0;
}
