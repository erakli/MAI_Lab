#include "Dorman-Prince_modified.h"

#define ORDER 1.0e-7

/* Округление до необходимого знака после запятой */
void RoundTo(TYPE &value, const TYPE order)
{
	TYPE
		rounded_value = ceil(value),
		difference = rounded_value - value;

	/* 
		Если разница между округлённым вверх значением и самим числом меньше 
		заданного порядка, то считаем, что число является уже округлённым
	*/
	if (difference < order && difference != 0)
		value = rounded_value;
}

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
	//TYPE NewStep = CDormanPrince::StepCorrection();

	//TYPE
	//	curPosition_on_curInterval,
	//	currentInterval, nextInterval_of_t;

	//curPosition_on_curInterval = t / correlation_interval;
	//RoundTo(curPosition_on_curInterval, ORDER);

	//// получаем значение текущего интервала корреляции
	//modf(curPosition_on_curInterval, &currentInterval);
	//	
	///* 
	//	получаем значение интервала, в котором мы окажемся, если прибавим
	//	к текущему времени интегрирования полученный шаг.
	//*/
	//modf( (t + NewStep) / correlation_interval, &nextInterval_of_t );

	///* 
	//	если мы с этим шагом окажемся в следующем интервале корреляции,
	//	то обрезаем шаг до такого значения, чтобы мы оказались на границе 
	//	текущего интервала корреляции */
	//if (nextInterval_of_t != currentInterval)
	//	NewStep = nextInterval_of_t * correlation_interval - t/* + RoundErr*/;

	//return NewStep;

	return Step;
}

void CDormanPrince_modified::getError()
{
	if (Error > Eps_Max)
		Error = 0;
}
