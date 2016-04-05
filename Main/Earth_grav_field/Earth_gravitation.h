#pragma once

#include "Types.h"
#include "Matrix_classes.h"

namespace Earth
{
	class CGravitation_Field
	{
		CVector getRight(const CVector &X, TYPE t) const;
	};
}