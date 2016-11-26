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

	Eigen::VectorXd GetRight(const Eigen::VectorXd &X, TYPE t) const override;

	bool IsStopCalculation(
		TYPE t, TYPE step, const Eigen::VectorXd &prev_step, const Eigen::VectorXd &cur_step)
		override;

public:
	TYPE GetMass() const;
	void SetMass(TYPE new_mass);

	TYPE GetBallisticCoeff() const;
	void SetBallisticCoeff(TYPE new_ballistic_coeff);

#ifdef DEBUG
	Eigen::MatrixXd GetRightPartsList() const;
#endif

private:
	TYPE mass;
	TYPE ballistic_coeff;

	ForcesVector forces;
	size_t forces_count;
};