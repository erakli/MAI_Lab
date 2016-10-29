#pragma once

#include "Model.h"
#include "Coordinates.h"
#include "Earth_gravitation.h"

class Sputnik : public Model
{
private:
	Earth::GravitationField *gravitation;
public:
	Sputnik(const Orbit::Kepler_elements &elements);
	
	void addForce(Earth::GravitationField &_field);

	CVector getRight(const CVector &X, TYPE t) const override;
};