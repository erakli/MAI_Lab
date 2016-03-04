#pragma once

#include "Model.h"
#include "Matrix_classes.h"
#include "Types.h"

class CPID_controller : public CModel
{
private:
	double 
		K,			// коэффициент в числителе апериодического звена (Агрегат)
		extU,		// внешнее воздействие u(t) = 1.7
		a[3],
		k_coeff[3]; // gain, integrate, differentiate


public:
	double randProcess;

	CPID_controller();
	CVector getRight(CVector &X, TYPE t) const;

	bool Stop_Calculation(TYPE t, TYPE Step, CVector &PrevStep, CVector &CurStep);

	void addResult(CVector &X, TYPE t);
};