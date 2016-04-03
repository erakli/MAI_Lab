#pragma once

//#include <Windows.h>

#include "Model.h"

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

	// интервал корреляции Белого Шума
	TYPE correlation_interval_WhiteNoise;

	// реализация Белого Шума на всё время моделирования с заданным интервалом корреляции
	CVector WhiteNoise;
	bool WhiteNoise_got;	// была ли получена реализация Белого Шума

	TYPE NonLinearElement(TYPE delta1) const;

	CVector AperiodicElement(TYPE beta, TYPE z1, TYPE z2, TYPE alpha) const;
	CVector ShapingFilter(TYPE epsilon, TYPE y, TYPE nu) const;

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

	CVector getRight(CVector &X, TYPE t) const override;

	bool Stop_Calculation(TYPE t, TYPE Step, CVector &PrevStep, CVector &CurStep) override;

	//void addResult(CVector &X, TYPE t) override;
};