#pragma once

#include "Model.h"

#define JD2016 2457388.5
#define DAYS_IN_CURRENT_YEAR 366


class CEarth : public Model
{
public:
	static const TYPE
		muEarth,		// геоцентрическая гравитационная постоянная, [m^3/s^2]
		angularVeloc,	// угловая скорость вращения, рад/с
		meanRadius,		// средний радиус для сферической земли, км
		ae;				// большая полуось ОЗЭ (общеземного эллипсоида), км

	/* Господа конструкторы (+ по дате и позиции) */
	CEarth();
	CEarth(const TYPE JD);
	CEarth(const Eigen::VectorXd &stateVector, const TYPE start);
	CEarth(const CEarth &copy_earth);

	void addResult(const Eigen::VectorXd &X, TYPE t) override;

	Eigen::VectorXd getRight(const Eigen::VectorXd &X, TYPE t) const override;
};


namespace Sun
{
	const TYPE
		muSun = 132712439.94e+3;	// гравитационная постоянная Солнца, km^3/s^2
}