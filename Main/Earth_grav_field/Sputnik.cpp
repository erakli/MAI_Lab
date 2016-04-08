#include "SolarSystem.h"	// Для константы muEarth
#include "Sputnik.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* * * CSputnik                                        * * * */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

CSputnik::CSputnik(const Orbit::Kepler_elements &elements)
{
	StartValues.insert_toEnd(Orbit::Kepler2Decart(elements));
	s_size = StartValues.getSize();
}

void CSputnik::addForce(Earth::CGravitation_Field &_field)
{
	gravitation = &_field;
}

CVector CSputnik::getRight(const CVector &X, TYPE t) const
{
	return gravitation->getRight(X, t);
}
