#include "SolarSystem.h"	// Для константы muEarth
#include "Grav_field_coefficients.h"
#include "Earth_gravitation.h"

using namespace Earth;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* * * CGravitation_Field                              * * * */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

CVector CGravitation_Field::getRight(const CVector& X, TYPE t) const
{
	CVector Res(VEC_SIZE * 2);

	TYPE
		module = CVector::copyPart(X, 2).getLength(),
		moduleX3 = pow(module, 3);

	/*
		Замена переменной, интегрируем второй
		раз проинтегрированную 2 производную
	*/
	Res[0] = X[3];
	Res[1] = X[4];
	Res[2] = X[5];

	Res[3] = -CEarth::muEarth * X[0] / moduleX3;
	Res[4] = -CEarth::muEarth * X[1] / moduleX3;
	Res[5] = -CEarth::muEarth * X[2] / moduleX3;

	return Res;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* * * CNormal_field                                   * * * */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

CNormal_field::CNormal_field()
{
	/* Заполняем массив точечных масс */
	massPoints.reserve(MASSPOINTS);
	Mass_Point mass_point;
	mass_point.position.setSize(VEC_SIZE);

	for (auto i = 0; i < MASSPOINTS; i++)
	{
		mass_point.value = massValues[i];

		for (auto j = 0; j < VEC_SIZE; j++)
			mass_point.position[j] = massPositions[i][j];

		massPoints.push_back(mass_point);
	}
}

CVector CNormal_field::getRight(const CVector &X, TYPE t) const
{
	/* 
		Вектор покомпонентной суммы, необбходимой для
		вычисления потенциала притяжения нормальной
		Земли в точечных массах V_0

			sum(epsilon[i] / r[i]),

			где 
				epsilon[i] - отношение i-ой точеченой массы
				к массе Земли,

				r[i] - расстояние от i-ой точечной массы
				до текущей точки (положение ИСЗ)
	*/
	CVector Sum(VEC_SIZE);

	CVector 
		curPosition(CVector::copyPart(X, 2)),
		r_vec;

	TYPE distance, distance3;

	for (auto i = 0; i < MASSPOINTS; i++)
	{
		// Вектор между точками массы и ИСЗ
		r_vec = curPosition + massPoints[i].position;

		distance = r_vec.getLength();
		distance3 = -1 * pow(distance, 3);

		/*
			Sum(epsilon[i] * (-(X + x) 
			/ ((X[0] + x[0])^2 + (X[1] + x[1])^2 + (X[2] + x[2])^2)^0.5))
		*/

		Sum = Sum + r_vec * (massPoints[i].value / distance3);
	}

	CVector Res;
	Res.reserve(X.getSize());

	for (int i = 0; i < VEC_SIZE; i++)
		Res.push_back(X[i + VEC_SIZE]);

	Res.insert_toEnd(Sum * CEarth::muEarth);

	return Res;
}