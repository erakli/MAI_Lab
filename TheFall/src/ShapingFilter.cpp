#include "ShapingFilter.h"

#include "Constants.h"
#include "WhiteNoise.h"

#include <exception>

using namespace Eigen;

/* * * * * * * * * * Support Fcn * * * * * * * * * */

inline TYPE ReferenceCorrelationFcn(TYPE tau)
{
	static
	const TYPE
		D = 0.01,
		lambda = 1.0e-3,
		beta = 2 * PI / 100;

	return
		D 
		* exp(-lambda * abs(tau)) 
		* cos(beta * tau);
}


/* * * * * * * * * * ShapingFilter * * * * * * * * * */

#define SYSTEM_COORDINATES		2

ShapingFilter::ShapingFilter()
{
	StartValues.resize(SYSTEM_COORDINATES);
	s_size = StartValues.size();

	StartValues = VectorXd::Zero();
	
	/* Коэффициенты в числителе и знаменателе Формирующего Фильтра */
	K = 0.071167241475998;
	T[0] = 15.913478971148;
	T[1] = 15.913478971148;
	xi = 0.015913478970986;

	Mx = 0;

	correlation_interval_WhiteNoise = 0;
	WhiteNoise_got = false;
}

void ShapingFilter::addResult(const VectorXd &X, TYPE t)
{
	VectorXd compile; // вектор результата
	compile.resize(X.size() + 1);
	
	/*	добавляем выход из ФФ. так как этой координаты
		нет в системе ДУ, то будем её учитывать здесь 
		
		y1 = K (T_1 x_2 + x_1)
	*/
	TYPE y1 = K * (T[0] * X[1] + X[0]);

	compile << X, y1 + Mx;	// Прибавляем мат. ожидание требуемого процесса

	Model::addResult(compile, t);
}

/*
*	Генерация вектора (квази)Белого Шума по заданной частоте среза
*/
void ShapingFilter::Generate_WhiteNoise(TYPE omega)
{
	TYPE dt(0);

	WhiteNoise = GetWhiteNoise(omega, t0, t1, dt);

	correlation_interval_WhiteNoise = dt;
	WhiteNoise_got = true;

	//lookUp_of_WhiteNoise.push_back(WhiteNoise);
}

TYPE ShapingFilter::GetCorrelationInterval() const
{
	return correlation_interval_WhiteNoise;
}



/*
*	Входной БШ для Формирующего Фильтра.
*	Индекс - кратное интервалу корреляции целочисленное число - номер интервала
*/
TYPE ShapingFilter::getWhiteNoise(TYPE t)  const
{
	if (!WhiteNoise_got)
	{
		throw std::exception("WhiteNoise hasn't been generated");
	}

	TYPE index_WN;
	modf(t / correlation_interval_WhiteNoise, &index_WN);

	return WhiteNoise[int(index_WN)];
}



VectorXd ShapingFilter::getRight(const VectorXd &X, TYPE t) const
{
	// Входной БШ для Формирующего Фильтра.
	TYPE nu = getWhiteNoise(t);
	TYPE x1 = X(0);
	TYPE x2 = X(1);

	TYPE y = (-2 * T[1] * xi * x2 - x1 + nu) / pow(T[1], 2);

	VectorXd RightPart(SYSTEM_COORDINATES);
	RightPart << x2, y;

	return RightPart;
}



VectorXd ShapingFilter::getReferenceCorrelationFcn(
	TYPE correlation_interval, int k_max)
{
	VectorXd K(k_max);
	TYPE tau;

	for (auto k = 0; k < k_max; k++)
	{
		tau = correlation_interval * k;
		K[k] = ReferenceCorrelationFcn(tau);
	}

	return K;
}
