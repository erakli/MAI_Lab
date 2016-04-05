#include "SolarSystem.h"
#include "Earth_gravitation.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* * * CGravitation_Field                              * * * */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

CVector Earth::CGravitation_Field::getRight(const CVector& X, TYPE t) const
{
	CVector Res(VEC_SIZE * 2);

	TYPE
		module = CVector::copyPart(X, 2).getLength(),
		moduleX3 = pow(module, 3);

	/*
		Замена переменной, интегрируем второй
		раз проинтегрированную 2 производную
	*/
	Res[0] = X[3];
	Res[1] = X[4];
	Res[2] = X[5];

	Res[3] = -CEarth::muEarth * X[0] / moduleX3;
	Res[4] = -CEarth::muEarth * X[1] / moduleX3;
	Res[5] = -CEarth::muEarth * X[2] / moduleX3;

	return Res;
}
