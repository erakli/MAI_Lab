#include "Constants.h"
#include "SolarSystem.h"	// Для константы muEarth
#include "Gravitation.h"


Eigen::VectorXd GravitationField::getRight(const Eigen::VectorXd &X, TYPE t) const
{
	Vector6d Res;

	TYPE
		module = X.head(VEC_SIZE).norm(),
		moduleX3 = pow(module, 3);

	TYPE const_part = -CEarth::muEarth / moduleX3;

	/*
		Замена переменной, интегрируем второй
		раз проинтегрированную 2 производную
	*/
	Res(0) = X(3);
	Res(1) = X(4);
	Res(2) = X(5);

	Res(3) = X(0) * const_part;
	Res(4) = X(1) * const_part;
	Res(5) = X(2) * const_part;

	return Res;
}
