#pragma once

#include <Windows.h>

#include "Model.h"

#define WM_USER			0x0400
#define WM_ADDPOINT		WM_USER + 1

typedef struct tagPosXY { TYPE posX, posY; } PosXY;

class CPID_controller : public CModel
{
private:
	TYPE 
		K,			// коэффициент в числителе апериодического звена (Агрегат)
		extU,		// внешнее воздействие u(t) = 1.7

		s,			// показатель в нелинейном звене

		T,			// коэффициент в знаменателе колебательного звена
		xi,			// показатель колебательности

		a[3],
		k_coeff[3]; // gain, integrate, differentiate

	HWND hWnd;

	TYPE NonLinearElement(TYPE delta1) const;

	CVector AperiodicElement(TYPE beta, TYPE z1, TYPE z2, TYPE alpha) const;
	CVector OscilElement(TYPE beta, TYPE z1, TYPE alpha) const;

public:
	TYPE randProcess;
	
	CPID_controller();
	CPID_controller(HWND hWnd) : CPID_controller()
	{
		this->hWnd = hWnd;
	};

	CVector getRight(CVector &X, TYPE t) const;

	bool Stop_Calculation(TYPE t, TYPE Step, CVector &PrevStep, CVector &CurStep);

	void addResult(CVector &X, TYPE t) override;
};