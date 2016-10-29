#include "SolarSystem.h"	// Для константы muEarth
#include "Sputnik.h"

using namespace Eigen;


#define DEFAULT_FORCES_SIZE	5


Sputnik::Sputnik() : forces_count(0)
{
}

Sputnik::Sputnik(const Orbit::Kepler_elements &elements)
{
	StartValues = Kepler2Decart(elements);
	s_size = StartValues.size();

	forces.reserve(DEFAULT_FORCES_SIZE);
	forces_count = 0;
}



void Sputnik::AddForce(const Force* force)
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
	Vector6d right_part;
	right_part.fill(0);

	for (size_t i = 0; i < forces_count; i++)
	{
		right_part += forces[i]->getRight(X, t);
	}

	return right_part;
}