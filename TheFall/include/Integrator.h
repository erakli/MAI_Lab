#pragma once

#include "Types.h"
#include "Model.h"

class Integrator
{
protected:
	TYPE step, t;
	Model *p_model;

public:
	Integrator();
	virtual ~Integrator();

	virtual void Run(Model &model) = 0; // pure virtual function

	TYPE GetStep() const;
	void SetStep(TYPE arg);
};