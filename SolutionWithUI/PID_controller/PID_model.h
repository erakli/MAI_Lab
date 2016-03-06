#pragma once

#include "Model.h"
#include "Matrix_classes.h"
#include "Types.h"

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

	TYPE NonLinearElement(TYPE delta1) const;

	CVector AperiodicElement(TYPE beta, TYPE z1, TYPE z2, TYPE alpha) const;
	CVector OscilElement(TYPE beta, TYPE z1, TYPE alpha) const;

public:
	TYPE randProcess;

	CPID_controller();
	CVector getRight(CVector &X, TYPE t) const;

	bool Stop_Calculation(TYPE t, TYPE Step, CVector &PrevStep, CVector &CurStep);

	void addResult(CVector &X, TYPE t);
};