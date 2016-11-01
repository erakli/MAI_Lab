﻿#include "AerodynamicForce.h"

#include "Constants.h"
#include <SolarSystem.h>

using namespace Eigen;



DensityModelParams::DensityModelParams()
{
	height = 0.0;
	A = 0.0;
	k1 = 0.0;
	k2 = 0.0;
}



AerodynamicForce::AerodynamicForce()
{

	density_params[0].height = 0.0;
	density_params[1].height = 2.0e+4;
	density_params[2].height = 6.0e+4;
	density_params[3].height = 1.0e+5;
	density_params[4].height = 1.5e+5;
	density_params[5].height = 3.0e+5;
	density_params[6].height = 6.0e+5;
	density_params[7].height = 9.0e+5;

	density_params[0].A = 1.225;
	density_params[1].A = 0.891e-1;
	density_params[2].A = 2.578e-4;
	density_params[3].A = 4.061e-7;
	density_params[4].A = 2.130e-9;
	density_params[5].A = 4.764e-11;
	density_params[6].A = 8.726e-13;
	density_params[7].A = 6.367e-14;

	density_params[0].k1 = -0.2639e-8;
	density_params[1].k1 = 0.4407e-9;
	density_params[2].k1 = -0.2560e-8;
	density_params[3].k1 = 0.1469e-8;
	density_params[4].k1 = 0.8004e-10;
	density_params[5].k1 = 0.7111e-11;
	density_params[6].k1 = 0.1831e-11;
	density_params[7].k1 = 0;

	density_params[0].k2 = 0.7825e-4;
	density_params[1].k1 = 0.16375e-3;
	density_params[2].k1 = 0.5905e-4;
	density_params[3].k1 = 0.1787e-3;
	density_params[4].k1 = 0.3734e-4;
	density_params[5].k1 = 0.1547e-4;
	density_params[6].k1 = 0.9280e-5;
	density_params[7].k1 = 0.9540e-5;
}



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
