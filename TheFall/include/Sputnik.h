#pragma once

#include "Model.h"
#include "Coordinates.h"
#include "Earth_gravitation.h"

class CSputnik : public Model
{
private:
	Earth::CGravitation_field *gravitation;
public:
	CSputnik(const Orbit::Kepler_elements &elements);
	
	void addForce(Earth::CGravitation_field &_field);

	CVector getRight(const CVector &X, TYPE t) const override;
};