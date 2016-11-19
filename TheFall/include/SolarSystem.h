#pragma once

#include "Model.h"

#define JD2016 2457388.5
#define DAYS_IN_CURRENT_YEAR 366


class Earth : public Model
{
public:
	static const TYPE
		muEarth,		// геоцентрическая гравитационная постоянная, [m^3/s^2]
		angularVeloc,	// угловая скорость вращения, рад/с
		meanRadius,		// средний радиус для сферической земли, км
		ae;				// большая полуось ОЗЭ (общеземного эллипсоида), км

	/* Господа конструкторы (+ по дате и позиции) */
	Earth();
	Earth(const TYPE JD);
	Earth(const Eigen::VectorXd &stateVector, const TYPE start);
	Earth(const Earth &copy_earth);

	void AddResult(const Eigen::VectorXd &X, TYPE t) override;

	Eigen::VectorXd GetRight(const Eigen::VectorXd &X, TYPE t) const override;
};


namespace Sun
{
	const TYPE
		muSun = 132712439.94e+3;	// гравитационная постоянная Солнца, km^3/s^2
}