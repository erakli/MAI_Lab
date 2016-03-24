#pragma once

#include "Matrix_classes.h"

TYPE StarTime(const TYPE JD);
TYPE StarTime(const TYPE starTime, const TYPE t);
//TYPE StarTime(const TYPE JD, const TYPE lambda);

namespace Transform
{
	CMatrix RotMatrix(const BYTE axis, const TYPE angle);

	CVector Fix2Topo(const CVector &fix_vector, const CVector &center_SpherPos);

	CVector Geographic2Fix(const TYPE h, const TYPE fi, const TYPE lambda);
	CVector Geographic2Fix(const CVector &geographic);
}