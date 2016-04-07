#include "SolarSystem.h"	// Для константы muEarth
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
	/* Позиция ИСЗ */
	CVector position(CVector::copyPart(X, 2));

	TYPE 
		ro, ae_ro2, ae_ro4, Z_ro2, Z_ro4, P, deltaP;

	// Радиус вектор текущей точки (положение ИСЗ
	ro = position.getLength();

	// 2 и 4 степень ro
	ae_ro2 = pow(CEarth::meanRadius / ro, 2);
	ae_ro4 = pow(ae_ro2, 2);

	// 2 и 4 степени Z / ro 
	Z_ro2 = pow(position[2] / ro, 2);
	Z_ro4 = pow(Z_ro2, 2);

	P =
		1.5 * J_02 * ae_ro2 * (1 - 5 * Z_ro2) 
		- 1.875 * J_04 * ae_ro4 
			* (1 - 14 * Z_ro2 + 21 * Z_ro4);

	deltaP =
		3 * J_02 * ae_ro2 
		- 2.5 * J_04 * ae_ro4 * (3 - 7 * Z_ro2);

	/* 
		Суммы в элементах вектора проекций силы гравитационного
		притяжения Земли
	*/
	CVector Sum(VEC_SIZE);

	for (auto i = 0; i < MASSPOINTS; i++)
	{
		// Расстояние от i-ой точечной массы до текущей точки
		TYPE distance =
			(position + massPoints[i].position * (-1)).getLength(),

			distance3 = pow(distance, 3);

		for (auto j = 0; i < VEC_SIZE; j++)
			Sum[j] += 
				massPoints[i].value 
				* (position[i] - massPoints[i].position[j])
				/ distance3;
	}
	
	TYPE
		muEarth_ro3 = CEarth::muEarth / pow(ro, 3);

	/* 
		Проекции силы гравитационного притяжения Земли
		на оси земной геоцентрической системы координат
	*/
	CVector Res(VEC_SIZE);

	Res[0] =
		-muEarth_ro3 * (1 + P) * position[0] 
		- CEarth::muEarth * Sum[0];
	
	Res[1] =
		-muEarth_ro3 * (1 + P) * position[1]
		- CEarth::muEarth * Sum[1];

	Res[2] =
		-muEarth_ro3 * (1 + P + deltaP) * position[2]
		- CEarth::muEarth * Sum[2];

	return Res;
}