#pragma once

#include "Types.h"
#include "Matrix_classes.h"
#include "Model.h"

#define JD2016 2457388.5
#define DAYS_IN_CURRENT_YEAR 366

namespace Earth
{
	class CEarth : public CModel
	{
	public:
		static const TYPE
			angularVeloc,	// угловая скорость вращения, рад/с
			meanRadius;		// средний радиус для сферической земли, км

		/* Господа конструкторы (+ по дате и позиции) */
		CEarth();
		CEarth(const TYPE JD);
		CEarth(const CVector &stateVector, const TYPE start);
		CEarth(const CEarth &copy_earth);

		void addResult(CVector &X, TYPE t) override;

		CVector getRight(const CVector &X, TYPE t) const override;

		bool Stop_Calculation(TYPE , TYPE , CVector &, CVector &) override 
		{ return false; };
	};

}

namespace Sun
{
	const TYPE
		muSun = 132712439.94e+3;	// гравитационная постоянная Солнца, km^3/s^2
}