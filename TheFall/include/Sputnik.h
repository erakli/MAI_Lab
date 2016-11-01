#pragma once

#include "Model.h"
#include "Coordinates.h"
#include "Force.h"

#include <vector>

typedef std::vector<Force*> ForcesVector;



class Sputnik : public Model
{
public:
	Sputnik();
	Sputnik(const Orbit::Kepler_elements &elements);
	
	void Init(int argc = 0, void** argv = nullptr) override;	// инициализация модели

	void AddForce(Force* force);
	void ClearForcesList();

	Eigen::VectorXd getRight(const Eigen::VectorXd &X, TYPE t) const override;

private:
	TYPE mass;
	TYPE ballistic_coeff;

	ForcesVector forces;
	size_t forces_count;
};