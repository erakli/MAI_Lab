#pragma once

//#include <Windows.h>

#include "Model.h"

#include "Stat_linearization.h"

//#define TESTS

//#define WM_USER			0x0400
//#define WM_ADDPOINT		WM_USER + 1
//
//typedef struct tagPosXY { TYPE posX, posY; } PosXY;

class CPID_controller : public CModel
{
private:
	TYPE 
		K_ag,		// коэффициент в числителе апериодического звена (Агрегат)
		ag[3],		// коэффициенты в знаменателе Агрегата

		extU,				// внешнее воздействие u(t) = 1.7

		nonLinear_border,	// показатель в нелинейном звене

		K_filter,			// коэффициент в числителе Формирующего Фильтра
		T_filter,			// коэффициент в знаменателе Формирующего Фильтра
		xi_filter,			// показатель колебательности Формирующего Фильтра

		k_coeff[3];			// соответственно [gain, integrate, differentiate]

	//HWND hWnd;

	// Флаг на вычисление статистических характеристик системы
	bool calculation_of_statistics;	

	// интервал корреляции Белого Шума
	TYPE correlation_interval_WhiteNoise;

	// реализация Белого Шума на всё время моделирования с заданным интервалом корреляции
	CVector WhiteNoise;
	bool WhiteNoise_got;	// была ли получена реализация Белого Шума

	TYPE getWhiteNoise(cTYPE t) const;

private:
	TYPE NonLinearElement(TYPE delta1) const;

	TYPE getEpsilon(cTYPE x1, cTYPE y1, cTYPE y2, cTYPE z1) const;

	/* 
		В аргумент RightPart передаётся результирующая правая часть, которая будет
		отдана в return функции getRight */

	void AperiodicElement(	CVector &RightPart, 
							TYPE y1, TYPE y2, TYPE y3, TYPE input) const;

	void ShapingFilter(	CVector &RightPart, 
						TYPE x1, TYPE x2, TYPE input) const;

	CVector SourceSystem(const CVector& X, cTYPE input_signal) const;

private:
	SaturationLinearize Saturation;

	// количество элементов в векторе, составленном из треугольной матрицы К (ковариации)
	UINT size_K_vec;

	// Флаг на текущий метод линеаризации (0 - первый, 1 - второй)
	bool linearisation_method;

	TYPE getEpsilonDisp(const CMatrix& K, cTYPE mean) const;

	/*
		Функции для вычисления матриц и векторов, необходимых для матрично-векторного
		вычисления эволюции системы с учётом стат. характеристик */

	void getA_Mtrx(		CMatrix &A, cTYPE linearization_k) const;
	void getB_Vector(	CMatrix &B) const;
	void getC_Vector(	CVector &C, cTYPE k0) const;
	void getC_Vector(	CVector &C, cTYPE k1, cTYPE Mx, cTYPE fi_0) const;

	CVector LinearizedSystem(const CVector &full_system_vec, cTYPE input_signal) const;

public:
	
	//CMatrix lookUp_of_WhiteNoise;

	CPID_controller();
	/*CPID_controller(HWND hWnd) : CPID_controller()
	{
		this->hWnd = hWnd;
	};*/

	// генерация (квази)Белого Шума. Должна вызываться перед моделированием
	void Generate_WhiteNoise(const TYPE omega);

	TYPE get_correlation_interval() const;

	void ModelWithLinearisation(bool got_linearisation, bool linearisation_method = false);

	CVector getRight(const CVector &X, TYPE t) const override;

	bool Stop_Calculation(TYPE t, TYPE Step, CVector &PrevStep, CVector &CurStep) override;

	//void addResult(CVector &X, TYPE t) override;
};