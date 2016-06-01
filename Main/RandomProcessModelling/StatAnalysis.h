#pragma once

#include "Matrix_classes.h"

class CStatProcessing
{
private:
	const CVector* RandomRealization;

	int realization_size;

	TYPE
		mean_estimation,
		mean_tolerance_interval[2],
		var_estimation,
		var_tolerance_interval[2];
public:
	CStatProcessing(const CVector *input_realization);

	static TYPE LaplaceFcnArg(TYPE beta);

	TYPE MeanEstimation();
	TYPE VarEstimation();
	CVector CorrelationFcnEstimation();
	// нормированная оценка корреляционной функции

	TYPE* MeanToleranceInterval(TYPE beta);
	TYPE* VarToleranceInterval(TYPE beta);
	// доверительный интервал нормированной корреляционной функции

	// вывод данных
};