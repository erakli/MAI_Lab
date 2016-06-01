
#include "StatAnalysis.h"

/* * * * * * * * * * Support Fcn * * * * * * * * * */

TYPE RationalApproximation(TYPE t)
{
	// Abramowitz and Stegun formula 26.2.23.
	// The absolute value of the error should be less than 4.5 e-4.
	static const TYPE c[] = { 2.515517, 0.802853, 0.010328 };
	static const TYPE d[] = { 1.432788, 0.189269, 0.001308 };
	return
		t
		- ((c[2] * t + c[1])*t + c[0]) /
		(((d[2] * t + d[1])*t + d[0])*t + 1.0);
}


/* * * * * * * * * * CStatProcessing * * * * * * * * * */

CStatProcessing::CStatProcessing(const CVector* input_realization)
{
	RandomRealization = input_realization;
	realization_size = RandomRealization->getSize();
}

TYPE CStatProcessing::LaplaceFcnArg(TYPE beta)
{
	auto
		p = (1 + beta) / 2;

	if (p <= 0.0 || p >= 1.0)
	{
		// у нас проблемы, вы шли за допустимые значения
		throw std::exception();
	}

	// See article http://www.johndcook.com/blog/normal_cdf_inverse/ 
	// for explanation of this section.
	if (p < 0.5)
	{
		// F^-1(p) = - G^-1(p)
		return -RationalApproximation(sqrt(-2.0*log(p)));
	}
	else
	{
		// F^-1(p) = G^-1(1-p)
		return RationalApproximation(sqrt(-2.0*log(1 - p)));
	}
}

TYPE CStatProcessing::MeanEstimation()
{
	TYPE sum(0);

	for (auto i = 0; i < realization_size; i++)
		sum += (*RandomRealization)[i];

	mean_estimation = sum / realization_size;

	return mean_estimation;
}

TYPE CStatProcessing::VarEstimation()
{
	// неэффективно, но что поделать
	MeanEstimation();

	TYPE sum(0);

	for (auto i = 0; i < realization_size; i++)
		sum += pow((*RandomRealization)[i] - mean_estimation, 2);

	var_estimation = sum / (realization_size - 1);

	return var_estimation;
}

CVector CStatProcessing::CorrelationFcnEstimation()
{
	MeanEstimation();

	auto
		k_max = realization_size - 120;

	CVector K(k_max);
	TYPE sum;

	for (auto k = 0; k < k_max; k++)
	{
		sum = 0;
		for (auto i = 0; i < realization_size - k; i++)
		{
			sum += 
				((*RandomRealization)[i] - mean_estimation)
				* ((*RandomRealization)[i + k] - mean_estimation);
		}
		K[k] = sum / (realization_size - k - 1);
	}

	return K;
}

TYPE* CStatProcessing::MeanToleranceInterval(TYPE beta)
{
	MeanEstimation();
	VarEstimation();

	auto 
		sigma = sqrt(var_estimation / realization_size),
		borders = sigma * LaplaceFcnArg(beta);

	mean_tolerance_interval[0] = mean_estimation - borders;
	mean_tolerance_interval[1] = mean_estimation + borders;

	return mean_tolerance_interval;
}

TYPE* CStatProcessing::VarToleranceInterval(TYPE beta)
{
	VarEstimation();

	auto
		sigma = sqrt(2 / (realization_size - 1)) * var_estimation,
		borders = sigma * LaplaceFcnArg(beta);

	var_tolerance_interval[0] = var_estimation - borders;
	var_tolerance_interval[1] = var_estimation + borders;

	return var_tolerance_interval;
}
