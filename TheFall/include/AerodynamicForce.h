#pragma once

#include "Force.h"

class AerodynamicForce : public Force
{
public:
	Eigen::Vector3d getRight(const Vector6d &X, TYPE t) const override;

private:
	TYPE GetDensity(const Eigen::Vector3d& X) const;
};
