#pragma once

#include "Force.h"

/* 
	Центральное поле
*/
class GravitationField : public Force
{
public:
	Eigen::VectorXd getRight(const Eigen::VectorXd &X, TYPE t) const override;
};
