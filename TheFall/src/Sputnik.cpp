#include "SolarSystem.h"	// Для константы muEarth
#include "Sputnik.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* * * Sputnik                                        * * * */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

Sputnik::Sputnik(const Orbit::Kepler_elements &elements)
{
	gravitation = nullptr;

	StartValues.insert_toEnd(Orbit::Kepler2Decart(elements));
	s_size = StartValues.getSize();
}

void Sputnik::addForce(Earth::GravitationField &_field)
{
	gravitation = &_field;
}

CVector Sputnik::getRight(const CVector &X, TYPE t) const
{
	return gravitation->getRight(X);
}
