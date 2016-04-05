#include "Dorman-Prince_modified.h"

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
	TYPE NewStep = CDormanPrince::StepCorrection();

	TYPE
		currentInterval, nextInterval_of_t;

	// получаем значение текущего интервала корреляции
	modf(t / correlation_interval, &currentInterval);
		
	/* 
		получаем значение интервала, в котором мы окажемся, если прибавим
		к текущему времени интегрирования полученный шаг.
	*/
	modf( (t + NewStep) / correlation_interval, &nextInterval_of_t );

	/* 
		если мы с этим шагом окажемся в следующем интервале корреляции,
		то обрезаем шаг до такого значения, чтобы мы оказались на границе 
		текущего интервала корреляции */
	if (nextInterval_of_t != currentInterval)
		NewStep = nextInterval_of_t * correlation_interval - t + RoundErr;

	return NewStep;
}
