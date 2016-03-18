#pragma once

#include "Types.h"
#include "Matrix_classes.h"
#include "Model.h"

namespace Earth
{
	class CEarth : public CModel
	{
	public:
		static const TYPE
			muEarth,	// гравитационная постоянная Земли, m^3/s^2
			angularVeloc,	// угловая скорость вращения, рад/с
			meanRadius;		// средний радиус для сферической земли, км

		/* Господа конструкторы (+ по дате и позиции) */
		CEarth();
		CEarth(const TYPE JD);
		CEarth(const CVector &stateVector, const TYPE &start);
		CEarth(const CEarth &copy_earth);

		void set_t0(const TYPE &arg, const bool days);
		void set_t1(const TYPE &arg, const bool days);

		CVector getRight(CVector &X, TYPE t) const override;

		bool Stop_Calculation(TYPE t, TYPE Step, CVector &PrevStep, CVector &CurStep) override 
		{
			return false;
		};
	};

}

namespace Sun
{
	const TYPE
		muSun = 132712438e+3;	// гравитационная постоянная Солнца, km^3/s^2
}