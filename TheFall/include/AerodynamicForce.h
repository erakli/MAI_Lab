#pragma once

#include "Force.h"

#define ATMO_LAYERS	8



struct DensityModelParams
{
	TYPE
		height,	// [м]
		A,		// [кг/м^3]
		k1,		// [м^-2]
		k2;		// [м^-1]

	DensityModelParams();
};



class AerodynamicForce : public Force
{
public:
	AerodynamicForce();
	Eigen::Vector3d getRight(const Vector6d &X, TYPE t) const override;

private:
	DensityModelParams density_params[ATMO_LAYERS];
	TYPE GetDensity(const Eigen::Vector3d& X, TYPE t) const;
};
