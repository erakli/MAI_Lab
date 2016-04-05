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

namespace Orbit
{
	/* Параметры орбиты ИСЗ */
	struct Kepler_elements
	{
		TYPE
			_Omega,		// Долгота восходящего узла,	градусы [0, 360]
			i,			// Наклонение орбиты,			градусы [0, 180]
			omega,		// Широта перицентра,			градусы [-90, 90]
			a,			// Большая полуось орбиты,		км
			e,			// Эксцентриситет
			teta;		// Истинная аномалия,			градусы [0, 360)
	};

	/* Матрица ориентации */
	CMatrix OrientationMatrix(const Kepler_elements &elements);

	CVector Kepler2Decart(const Kepler_elements &elements);
}