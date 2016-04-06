#include "SolarSystem.h"	// Для константы muEarth
#include "Sputnik.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* * * CSputnik                                        * * * */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

CSputnik::CSputnik(const Orbit::Kepler_elements &elements)
{
	Earth::CGravitation_Field _field;
	gravitation = &_field;

	StartValues.insert_toEnd(Orbit::Kepler2Decart(elements));
	s_size = StartValues.getSize();
}

CVector CSputnik::getRight(const CVector &X, TYPE t) const
{
	CVector RightPart(gravitation->getRight(X, t));

	return RightPart;
}