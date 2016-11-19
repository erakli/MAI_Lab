#include "ArenstorfModel.h"

using namespace Eigen;

ArenstorfModel::ArenstorfModel(int variant)
{
	Model::SetStartValuesSize(4);

	m = 0.012277471;
	M = 1 - m;

	orbit = variant;

	m_start_values(0) = 0.994; // y1
	m_start_values(1) = 0;     // y2
	m_start_values(2) = 0;     // y1'
	if (orbit) // �������� ������� ������
	{
		m_start_values(3) = -2.00158510637908252240537862224; // y2'
		m_period = 17.0652165601579625588917206249;
	}
	else // ����� �����
	{
		m_start_values(3) = -2.0317326295573368357302057924; // y2'	
		m_period = 11.124340337266085134999734047;
	}
}



VectorXd ArenstorfModel::GetRight(const VectorXd &X, TYPE t) const
{
	TYPE
		R[2] =
	{
		pow(pow(X(0) + m, 2) + pow(X(1), 2), 1.5),
		pow(pow(X(0) - M, 2) + pow(X(1), 2), 1.5)
	};

	VectorXd Y(s_size);

	Y(0) = X(2); // v1 = y1' - ������ ����������. ����� �������������� ������� y1
	Y(1) = X(3); // v2 = y2'

	Y(2) = X(0) + 2 * X(3) - M * (X(0) + m) / R[0] - m * (X(0) - M) / R[1];
	Y(3) = X(1) - 2 * X(2) - M * X(1) / R[0] - m * X(1) / R[1];

	return Y; // ��������
}