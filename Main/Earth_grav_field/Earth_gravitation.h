#pragma once

#include "Types.h"
#include "Matrix_classes.h"

namespace Earth
{
	class CGravitation_Field
	{
	public:
		CVector getRight(const CVector &X, TYPE t) const;
	};
}