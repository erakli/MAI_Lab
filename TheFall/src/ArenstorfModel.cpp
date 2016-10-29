#include "ArenstorfModel.h"

using namespace Eigen;

ArenstorfModel::ArenstorfModel(int variant)
{
	StartValues.resize(4);
	s_size = StartValues.size();

	m = 0.012277471;
	M = 1 - m;

	orbit = variant;

	StartValues(0) = 0.994; // y1
	StartValues(1) = 0;     // y2
	StartValues(2) = 0;     // y1'
	if (orbit) // выбираем большую орбиту
	{
		StartValues(3) = -2.00158510637908252240537862224; // y2'
		Period = 17.0652165601579625588917206249;
	}
	else // иначе малую
	{
		StartValues(3) = -2.0317326295573368357302057924; // y2'	
		Period = 11.124340337266085134999734047;
	}
}



VectorXd ArenstorfModel::getRight(const VectorXd &X, TYPE t) const
{
	TYPE
		R[2] =
	{
		pow(pow(X(0) + m, 2) + pow(X(1), 2), 1.5),
		pow(pow(X(0) - M, 2) + pow(X(1), 2), 1.5)
	};

	VectorXd Y(s_size);

	Y(0) = X(2); // v1 = y1' - замена переменной. После интегрирования получим y1
	Y(1) = X(3); // v2 = y2'

	Y(2) = X(0) + 2 * X(3) - M * (X(0) + m) / R[0] - m * (X(0) - M) / R[1];
	Y(3) = X(1) - 2 * X(2) - M * X(1) / R[0] - m * X(1) / R[1];

	return Y; // заглушка
}