#include "SolarSystem.h"	// Для константы muEarth
#include "Sputnik.h"
#include <Constants.h>

using namespace Eigen;


#ifdef DEBUG
#include <iostream>
using namespace std;
#endif


#define DEFAULT_FORCES_SIZE	5


Sputnik::Sputnik() : mass(0), ballistic_coeff(0), forces_count(0)
{
}

Sputnik::Sputnik(const Orbit::Kepler_elements &elements)
{
	Model::SetStartValuesSize(Kepler2Decart(elements));

	mass = 0;
	ballistic_coeff = 0;

	forces.reserve(DEFAULT_FORCES_SIZE);
	forces_count = 0;
}



void Sputnik::Init(int argc, void** argv)
{
	Model::Init();

	const int arg_count = 2;
	void** args = new void*[arg_count];

	const int param_count = 2;
	TYPE params[param_count] = { t1, ballistic_coeff };

	args[0] = (void*)&param_count;
	args[1] = (void*)&params;
	
	for (size_t i = 0; i < forces_count; i++)
	{
		forces[i]->Init(arg_count, args);
	}

	delete [] args;
}



void Sputnik::AddForce(Force* force)
{
	forces.push_back(force);
	forces_count++;
}

void Sputnik::ClearForcesList()
{
	forces.clear();
	forces.reserve(DEFAULT_FORCES_SIZE);
	forces_count = 0;
}



VectorXd Sputnik::getRight(const VectorXd &X, TYPE t) const
{
	Vector3d cur_force;
	Vector3d forces_sum = Vector3d::Zero();

	for (size_t i = 0; i < forces_count; i++)
	{
		cur_force = forces[i]->getRight(X, t);
		if (i > 0)
			cur_force /= mass;
		forces_sum += cur_force;
	}

	VectorXd right_part(VEC_SIZE * 2);
	right_part << X.tail(VEC_SIZE), forces_sum;

	return right_part;
}



bool Sputnik::Stop_Calculation(
	TYPE t, TYPE Step, const VectorXd& PrevStep, const VectorXd& CurStep)
{
	TYPE norm = PrevStep.head(VEC_SIZE).norm();
	if ((norm - Earth::meanRadius) < 0)
		return true;

	return false;
}



TYPE Sputnik::GetMass() const
{
	return mass;
}

void Sputnik::SetMass(TYPE new_mass)
{
	mass = new_mass;
}

TYPE Sputnik::GetBallisticCoeff() const
{
	return ballistic_coeff;
}

void Sputnik::SetBallisticCoeff(TYPE new_ballistic_coeff)
{
	ballistic_coeff = new_ballistic_coeff;
}