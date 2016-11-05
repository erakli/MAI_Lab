#pragma once

#include "LinearAlgebra.h"

TYPE StarTime(TYPE JD);
TYPE StarTime(TYPE starTime, TYPE t);
//TYPE StarTime(const TYPE JD, const TYPE lambda);

namespace Transform
{
	Eigen::Matrix3d RotMatrix(BYTE axis, TYPE angle);

	Eigen::Vector3d Fix2Topo(const Eigen::Vector3d &fix_vector, const Eigen::Vector3d &center_SpherPos);

	Eigen::Vector3d Geographic2Fix(TYPE h, TYPE fi, TYPE lambda);
	Eigen::Vector3d Geographic2Fix(const Eigen::Vector3d &geographic);

	Eigen::Vector3d Decart2Spher(const Eigen::Vector3d &fix);
}

namespace Orbit
{
	/* 
		Параметры орбиты ИСЗ
	*/
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
	Eigen::Matrix3d OrientationMatrix(const Kepler_elements &elements);

	Vector6d Kepler2Decart(const Kepler_elements &elements);
}