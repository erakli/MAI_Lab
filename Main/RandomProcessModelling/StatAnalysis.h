#pragma once

#include "Matrix_classes.h"

class CStatAnalyzer
{
private:
	// сам случайный процесс, который анализируем
	const CVector* RandomRealization;
	int realization_size;

	// признак того, что величина уже посчитана
	bool
		got_mean,
		got_var,
		got_correlation_fcn,
		got_norm_correlation_fcn;

	bool
		got_mean_tol,
		got_var_tol,
		got_corr_tol;

	// оценки
	TYPE
		mean_estimation,
		var_estimation;

	CVector
		correlation_fcn_estimation,
		norm_correlation_fcn_estimation;

	// доверительные интервалы
	TYPE
		mean_tolerance_interval[2],
		var_tolerance_interval[2];

	CMatrix
		correlation_tolerance_interval;	// две границы - две строки матрицы
public:
	CStatAnalyzer();
	CStatAnalyzer(const CVector *input_realization);

	void LoadNewRealization(const CVector *input_realization);

	static TYPE LaplaceFcnArg(TYPE beta);

	// оценки
	TYPE MeanEstimation();
	TYPE VarEstimation();
	CVector CorrelationFcnEstimation();
	CVector NormCorrelationFcnEstimation();

	// доверительные интервалы
	TYPE* MeanToleranceInterval(TYPE beta);
	TYPE* VarToleranceInterval(TYPE beta);
	CMatrix NormCorrelationFcnToleranceInterval(TYPE beta);

};