#pragma once

#include "Model.h"
#include "Coordinates.h"
#include "Force.h"

#include <vector>

typedef std::vector<const Force*> ForcesVector;



class Sputnik : public Model
{
public:
	Sputnik();
	Sputnik(const Orbit::Kepler_elements &elements);
	
	void AddForce(const Force* force);
	void ClearForcesList();

	Eigen::VectorXd getRight(const Eigen::VectorXd &X, TYPE t) const override;

private:
	ForcesVector forces;
	size_t forces_count;
};