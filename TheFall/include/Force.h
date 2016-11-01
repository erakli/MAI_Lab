#pragma once

#include "Types.h"
#include "LinearAlgebra.h"

class Force
{
public:
	virtual ~Force();

	virtual void Init(int argc = 0, void** argv = nullptr);	// инициализация модели силы

	virtual Eigen::Vector3d getRight(const Vector6d &X, TYPE t) const = 0;
};
