#pragma once


#include "Model.h"

using namespace Eigen;

class ShapingFilter : public Model
{
private:
	TYPE
		K,				// коэффициент в числителе Формирующего Фильтра
		T[2],			// коэффициент в числителе и знаменателе Формирующего Фильтра
		xi;				// показатель колебательности Формирующего Фильтра

	TYPE
		Mx;				// Мат. ожидание требуемого процесса

	// интервал корреляции Белого Шума
	TYPE correlation_interval_WhiteNoise;

	// реализация Белого Шума на всё время моделирования с заданным интервалом корреляции
	VectorXd WhiteNoise;
	bool WhiteNoise_got;	// была ли получена реализация Белого Шума

	TYPE getWhiteNoise(TYPE t) const;

public:

	ShapingFilter();

	/*
		Матрица результатов:	t, x1, x2, y1
		y1 - выход из фильтра
	*/
	void addResult(const VectorXd &X, TYPE t) override;

	// генерация (квази)Белого Шума. Должна вызываться перед моделированием
	void Generate_WhiteNoise(TYPE omega);
	TYPE get_correlation_interval() const;

	Eigen::VectorXd getRight(const Eigen::VectorXd &X, TYPE t) const override;

	static Eigen::VectorXd getReferenceCorrelationFcn(TYPE correlation_interval, int k_max);
};