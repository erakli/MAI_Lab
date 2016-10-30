#include "AerodynamicForce.h"

#include "Constants.h"
#include <SolarSystem.h>

using namespace Eigen;

Vector3d AerodynamicForce::getRight(const Vector6d& X, TYPE t) const
{
	Vector3d pos, veloc;
	pos = X.head(VEC_SIZE);
	veloc = X.tail(VEC_SIZE);

	Vector3d earth_ang_veloc(0.0, 0.0, Earth::angularVeloc);

	Vector3d atmospheric_veloc;
	atmospheric_veloc = veloc - earth_ang_veloc.cross(pos);

	TYPE scalar_part = atmospheric_veloc.norm() * GetDensity(pos) / 2.0;

	Vector3d right_part;
	right_part = scalar_part * atmospheric_veloc;

	return right_part;
}



TYPE AerodynamicForce::GetDensity(const Vector3d& X) const
{
	TYPE height = X.norm() - Earth::meanRadius;

	TYPE density;

	return density;
}
