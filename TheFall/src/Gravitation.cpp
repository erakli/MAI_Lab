#include "Constants.h"
#include "SolarSystem.h"	// Для константы muEarth
#include "Gravitation.h"

using namespace Eigen;

Vector3d GravitationField::getRight(const Vector6d &X, TYPE t) const
{
	Vector3d head = X.head(VEC_SIZE);

	TYPE
		module = head.norm(),
		moduleX3 = pow(module, 3);

	TYPE scalar_part = -Earth::muEarth / moduleX3;

	return head * scalar_part;
}
