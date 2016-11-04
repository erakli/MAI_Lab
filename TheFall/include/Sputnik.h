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
	
	void Init(int argc = 0, void** argv = nullptr) override;	// ������������� ������

	void AddForce(Force* force);
	void ClearForcesList();

	Eigen::VectorXd getRight(const Eigen::VectorXd &X, TYPE t) const override;

	bool Stop_Calculation(
		TYPE t, TYPE Step, const Eigen::VectorXd &PrevStep, const Eigen::VectorXd &CurStep)
		override;

public:
	TYPE GetMass() const;
	void SetMass(TYPE new_mass);

	TYPE GetBallisticCoeff() const;
	void SetBallisticCoeff(TYPE new_ballistic_coeff);

private:
	TYPE mass;
	TYPE ballistic_coeff;

	ForcesVector forces;
	size_t forces_count;
};