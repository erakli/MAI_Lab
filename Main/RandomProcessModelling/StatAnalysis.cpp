
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

inline TYPE FisherTransition(TYPE r)
{
	return 0.5 * (log(1 + r) - log(1 - r));
}

inline TYPE FisherBackTransition(TYPE z)
{
	auto e_2z = exp(2 * z);
	return (e_2z - 1) / (e_2z + 1);
}

/* * * * * * * * * * CStatAnalyzer * * * * * * * * * */

CStatAnalyzer::CStatAnalyzer() 
	: mean_estimation(0), var_estimation(0)
{
	RandomRealization = nullptr;
	realization_size = 0;

	got_mean = false;
	got_var = false;
	got_correlation_fcn = false;
	got_norm_correlation_fcn = false;

	got_mean_tol = false;
	got_var_tol = false;
	got_corr_tol = false;
}

CStatAnalyzer::CStatAnalyzer(const CVector* input_realization)
	: mean_estimation(0), var_estimation(0)
{
	LoadNewRealization(input_realization);
}

void CStatAnalyzer::LoadNewRealization(const CVector* input_realization)
{
	RandomRealization = input_realization;
	realization_size = RandomRealization->getSize();

	got_mean = false;
	got_var = false;
	got_correlation_fcn = false;
	got_norm_correlation_fcn = false;

	got_mean_tol = false;
	got_var_tol = false;
	got_corr_tol = false;
}

TYPE CStatAnalyzer::LaplaceFcnArg(TYPE beta)
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

TYPE CStatAnalyzer::MeanEstimation()
{
	if (!got_mean)
	{
		TYPE sum(0);

		for (auto i = 0; i < realization_size; i++)
			sum += (*RandomRealization)[i];

		mean_estimation = sum / realization_size;

		got_mean = true;
	}

	return mean_estimation;
}

TYPE CStatAnalyzer::VarEstimation()
{
	if (!got_var)
	{
		MeanEstimation();

		TYPE sum(0);

		for (auto i = 0; i < realization_size; i++)
			sum += pow((*RandomRealization)[i] - mean_estimation, 2);

		var_estimation = sum / (realization_size - 1);

		got_var = true;
	}

	return var_estimation;
}

CVector CStatAnalyzer::CorrelationFcnEstimation()
{
	if (!got_correlation_fcn)
	{
		MeanEstimation();

		auto
			k_max = realization_size - 120;

		correlation_fcn_estimation.resize(k_max);
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
			correlation_fcn_estimation[k] = sum / (realization_size - k - 1);
		}

		got_correlation_fcn = true;
	}

	return correlation_fcn_estimation;
}

CVector CStatAnalyzer::NormCorrelationFcnEstimation()
{
	if (!got_norm_correlation_fcn)
	{
		CorrelationFcnEstimation();

		auto K_size = correlation_fcn_estimation.getSize();

		norm_correlation_fcn_estimation.resize(K_size);

		// начинаем с 0, 0-й элемент - дисперсия делённая на саму себя
		for (auto i = 0; i < K_size; i++)
			norm_correlation_fcn_estimation[i] =
			correlation_fcn_estimation[i] / correlation_fcn_estimation[0];

		got_norm_correlation_fcn = true;
	}

	return norm_correlation_fcn_estimation;
}

TYPE* CStatAnalyzer::MeanToleranceInterval(TYPE beta)
{
	if (!got_mean_tol)
	{
		MeanEstimation();
		VarEstimation();

		auto
			sigma = sqrt(var_estimation / realization_size),
			borders = sigma * LaplaceFcnArg(beta);

		mean_tolerance_interval[0] = mean_estimation - borders;
		mean_tolerance_interval[1] = mean_estimation + borders;

		got_mean_tol = true;
	}

	return mean_tolerance_interval;
}

TYPE* CStatAnalyzer::VarToleranceInterval(TYPE beta)
{
	if (!got_var_tol)
	{
		VarEstimation();

		auto
			sigma = sqrt(2 / TYPE(realization_size - 1)) * var_estimation,
			borders = sigma * LaplaceFcnArg(beta);

		var_tolerance_interval[0] = var_estimation - borders;
		var_tolerance_interval[1] = var_estimation + borders;

		got_var_tol = true;
	}

	return var_tolerance_interval;
}

CMatrix CStatAnalyzer::NormCorrelationFcnToleranceInterval(TYPE beta)
{
	if (!got_corr_tol)
	{
		NormCorrelationFcnEstimation();

		auto
			k_max = realization_size - 120;

		CVector z_borders(k_max);

		TYPE
			sigma,
			Laplace_fcn_arg = LaplaceFcnArg(beta);

		for (auto k = 0; k < k_max; k++)
		{
			sigma = sqrt(1 / TYPE(realization_size - k - 3));
			z_borders[k] = sigma * Laplace_fcn_arg;
		}

		// считаем сразу границы доверительного интервала для r
		correlation_tolerance_interval.setSize(2, k_max);
		TYPE z;

		// начинаем с 1, так как у дисперсии будет логарифм от 0
		for (auto i = 1; i < k_max; i++)
		{
			z = FisherTransition(norm_correlation_fcn_estimation[i]);

			correlation_tolerance_interval[0][i] =
				FisherBackTransition(z - z_borders[i]);

			correlation_tolerance_interval[1][i] =
				FisherBackTransition(z + z_borders[i]);
		}

		got_corr_tol = true;
	}

	return correlation_tolerance_interval;
}