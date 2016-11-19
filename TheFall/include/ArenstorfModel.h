#pragma once

#include "Model.h"

class ArenstorfModel : public Model
{
private:
	TYPE m, M;

public:
	TYPE Period;  // Период обращения конкретной орбиты
	int orbit; // Выбор орбиты (малая/большая)

	ArenstorfModel(int variant);
	Eigen::VectorXd GetRight(const Eigen::VectorXd &X, TYPE t) const override;
};