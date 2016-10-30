#pragma once

#include "Force.h"

/* 
	Центральное поле
*/
class GravitationField : public Force
{
public:
	Eigen::Vector3d getRight(const Vector6d &X, TYPE t) const override;
};
