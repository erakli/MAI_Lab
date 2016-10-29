#pragma once

#include "Model.h"

class ArenstorfModel : public Model
{
private:
	TYPE m, M;

public:
	TYPE Period;  // ������ ��������� ���������� ������
	int orbit; // ����� ������ (�����/�������)

	ArenstorfModel(int variant);
	Eigen::VectorXd getRight(const Eigen::VectorXd &X, TYPE t) const override;
};