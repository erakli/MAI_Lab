#pragma once

#include "Matrix_classes.h"

TYPE StarTime(const TYPE &JD);
TYPE StarTime(const TYPE &JD, const TYPE &lambda);

namespace Transform
{
	CVector Geographic2Fix(const CVector &geographic);
}