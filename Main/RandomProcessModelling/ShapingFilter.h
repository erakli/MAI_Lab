#pragma once

#include "Model.h"

class CShapingFilter : public CModel
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
	CVector WhiteNoise;
	bool WhiteNoise_got;	// была ли получена реализация Белого Шума

	TYPE getWhiteNoise(cTYPE t) const;

private:
	void ShapingFilter(CVector &RightPart,
		TYPE x1, TYPE x2, TYPE input) const;

public:

	CShapingFilter();

	/*
		Матрица результатов:	t, x1, x2, y1
		y1 - выход из фильтра
	*/
	void addResult(CVector &X, TYPE t) override;

	// генерация (квази)Белого Шума. Должна вызываться перед моделированием
	void Generate_WhiteNoise(const TYPE omega);
	TYPE get_correlation_interval() const;

	CVector getRight(const CVector &X, TYPE t) const override;

	bool Stop_Calculation(TYPE t, TYPE Step, CVector &PrevStep, CVector &CurStep) override;

	static CVector getReferenceCorrelationFcn(TYPE correlation_interval, int k_max);
};