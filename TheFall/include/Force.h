#pragma once

#include "Types.h"
#include "LinearAlgebra.h"

class Force
{
public:
	virtual ~Force();

	virtual Eigen::VectorXd getRight(const Eigen::VectorXd &X, TYPE t) const = 0;
};
