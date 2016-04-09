#include "SolarSystem.h"	// Для константы muEarth
#include "Sputnik.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* * * CSputnik                                        * * * */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

CSputnik::CSputnik(const Orbit::Kepler_elements &elements)
{
	gravitation = nullptr;

	StartValues.insert_toEnd(Orbit::Kepler2Decart(elements));
	s_size = StartValues.getSize();
}

void CSputnik::addForce(Earth::CGravitation_field &_field)
{
	gravitation = &_field;
}

CVector CSputnik::getRight(const CVector &X, TYPE t) const
{
	return gravitation->getRight(X);
}
