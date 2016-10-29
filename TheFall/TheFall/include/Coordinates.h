#pragma once

#include "LinearAlgebra.h"

TYPE StarTime(const TYPE JD);
TYPE StarTime(const TYPE starTime, const TYPE t);
//TYPE StarTime(const TYPE JD, const TYPE lambda);

namespace Transform
{
	Eigen::Matrix3d RotMatrix(const BYTE axis, const TYPE angle);

	Eigen::Vector3d Fix2Topo(const Eigen::Vector3d &fix_vector, const Eigen::Vector3d &center_SpherPos);

	Eigen::Vector3d Geographic2Fix(const TYPE h, const TYPE fi, const TYPE lambda);
	Eigen::Vector3d Geographic2Fix(const Eigen::Vector3d &geographic);

	Eigen::Vector3d Decart2Spher(const Eigen::Vector3d &fix);
}

namespace Orbit
{
	/* 
		Параметры орбиты ИСЗ

		_Omega,	* Долгота восходящего узла,		градусы [0, 360]
		i,		* Наклонение орбиты,			градусы [0, 180]
		omega,	* Широта перицентра,			градусы [-90, 90]
		a,		* Большая полуось орбиты,		км
		e,		* Эксцентриситет
		teta;	* Истинная аномалия,			градусы [0, 360)
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