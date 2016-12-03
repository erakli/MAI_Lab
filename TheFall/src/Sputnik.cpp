#include "SolarSystem.h"	// Для константы muEarth
#include "Sputnik.h"
#include <Constants.h>

using namespace Eigen;


#define CONSOLE_OUTPUT


#ifdef CONSOLE_OUTPUT
#include <iostream>
using namespace std;
#endif

#ifdef DEBUG
#include <list>
std::list<Eigen::VectorXd> right_parts_list;
#endif


#define DEFAULT_FORCES_SIZE	5


Sputnik::Sputnik() : Model()
{
	mass = 0;
	ballistic_coeff = 0;

	forces.reserve(DEFAULT_FORCES_SIZE);
	forces_count = 0;

	do_disable_stop_calculation = false;
}

Sputnik::Sputnik(const Orbit::Kepler_elements &elements) : Sputnik()
{
	Model::SetStartValuesSize(Kepler2Decart(elements));
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



VectorXd Sputnik::GetRight(const VectorXd &X, TYPE t) const
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

#ifdef DEBUG
//	VectorXd res(VEC_SIZE * 2 + 1);
//	res << t, right_part;
//	right_parts_list.push_back(res);
#endif

	return right_part;
}



bool Sputnik::IsStopCalculation(
	TYPE t, TYPE step, const VectorXd& prev_step, const VectorXd& cur_step)
{
	if (do_disable_stop_calculation == true)
		return false;

	TYPE norm = cur_step.head(VEC_SIZE).norm();
	if ((norm - Earth::meanRadius) < 0)
	{
#ifdef CONSOLE_OUTPUT
		cout << " * Touchdown! * " << endl;
		cout << endl;
//		system("pause");
#endif
		return true;
	}

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



void Sputnik::SetDisableStopCalculation(bool do_disable)
{
	do_disable_stop_calculation = do_disable;
}


#ifdef DEBUG
Eigen::MatrixXd Sputnik::GetRightPartsList() const
{
	Eigen::MatrixXd res = Eigen::MatrixXd::Zero(right_parts_list.size(), 7);
	size_t i = 0;

	for (std::list<Eigen::VectorXd>::const_iterator
		it = right_parts_list.begin();
		it != right_parts_list.end();
	++it)
	{
		res.row(i) = *it;
		i++;
	}

	return res;
}
#endif