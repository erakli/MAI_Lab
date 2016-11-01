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

	void Init(int argc, void** argv) override;

	Eigen::Vector3d getRight(const Vector6d &X, TYPE t) const override;

private:
	TYPE ballistic_coeff;

	DensityModelParams density_params[ATMO_LAYERS];
	Eigen::VectorXd random_process_realization;


	TYPE GetDensity(const Eigen::Vector3d& X, TYPE t) const;

	void GenerateRandomRealization(TYPE t1);
};
