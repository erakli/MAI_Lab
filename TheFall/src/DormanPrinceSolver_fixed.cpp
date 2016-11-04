#include "DormanPrinceSolver_fixed.h"

//#define STEP_CORRECTION

DormanPrinceSolver_fixed::DormanPrinceSolver_fixed()
{
	correlation_interval = 0;
}

DormanPrinceSolver_fixed::DormanPrinceSolver_fixed(TYPE correlation_interval)
{
	SetCorrelationInterval(correlation_interval);
}



TYPE DormanPrinceSolver_fixed::StepCorrection(TYPE Error)
{
#ifdef STEP_CORRECTION
	TYPE NewStep = DormanPrinceSolver::StepCorrection();

	if (NewStep > correlation_interval)
		NewStep = correlation_interval;

	return NewStep;
#else
	return step;
#endif
}

TYPE DormanPrinceSolver_fixed::getError()
{
	//CDormanPrince::getError();
	
	//if (Error > Eps_Max)
	//	Error = 0;

	return 0;
}



void DormanPrinceSolver_fixed::SetCorrelationInterval(TYPE correlation_interval)
{
	step = correlation_interval; // начальный шаг делаем равным интервалу корреляции
	this->correlation_interval = correlation_interval;
}

TYPE DormanPrinceSolver_fixed::GetCorrelationInterval() const
{
	return correlation_interval;
}