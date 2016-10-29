#include "Integrator.h"


Integrator::Integrator()
{
	p_model = nullptr;

	t = 0;
	step = 1;
}

Integrator::~Integrator()
{
}



TYPE Integrator::getStep() const
{
	return step;
}

void Integrator::setStep(TYPE arg)
{
	step = arg;
}