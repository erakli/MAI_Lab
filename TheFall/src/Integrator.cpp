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



TYPE Integrator::GetStep() const
{
	return step;
}

void Integrator::SetStep(TYPE arg)
{
	step = arg;
}