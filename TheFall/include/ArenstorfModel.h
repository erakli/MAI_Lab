#pragma once

#include "Model.h"

class ArenstorfModel : public Model
{
private:
	TYPE m, M;

public:
	TYPE m_period;  // ������ ��������� ���������� ������
	int orbit; // ����� ������ (�����/�������)

	ArenstorfModel(int variant);
	Eigen::VectorXd GetRight(const Eigen::VectorXd &X, TYPE t) const override;
};