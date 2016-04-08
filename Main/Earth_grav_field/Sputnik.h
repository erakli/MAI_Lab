#pragma once

#include "Model.h"
#include "Coordinates.h"
#include "Earth_gravitation.h"

class CSputnik : public CModel
{
private:
	Earth::CGravitation_Field *gravitation;
public:
	CSputnik(const Orbit::Kepler_elements &elements);
	
	void addForce(Earth::CGravitation_Field &_field);

	CVector getRight(const CVector &X, TYPE t) const override;
};