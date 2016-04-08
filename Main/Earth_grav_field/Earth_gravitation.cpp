#include "SolarSystem.h"	// Для константы muEarth
#include "Coordinates.h"
#include "Grav_field_coefficients.h"
#include "Earth_gravitation.h"

using namespace Earth;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* * * CGravitation_Field                              * * * */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

CGravitation_field::~CGravitation_field()
{
}

CVector CGravitation_field::getRight(const CVector& X) const
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

CVector CNormal_field::getRight(const CVector &X) const
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
		// Вектор между точками массы и ИСЗ: r_vec = (x - mx)
		CVector::Sub(massPoints[i].position, curPosition, r_vec);

		distance = r_vec.getLength();
		distance3 = pow(distance, 3);

		/*
			Sum(epsilon[i] * (-(X - x) 
			/ ((X[0] + x[0])^2 - (X[1] + x[1])^2 - (X[2] + x[2])^2)^0.5))
		*/
		for (auto j = 0; j < VEC_SIZE; j++)
		{
			Sum[j] += massPoints[i].value * r_vec[j] / distance3;
		}
	}

	CVector::Mult( -1 * CEarth::muEarth, Sum );

	/* Итоговый вектор правых частей с учётом замены переменной */
	CVector Res;
	Res.reserve(X.getSize());

	for (auto i = 0; i < VEC_SIZE; i++)
		Res.push_back(X[i + VEC_SIZE]);

	Res.insert_toEnd(Sum);

	return Res;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* * * CNormal_spheric                                 * * * */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
CNormal_spheric::CNormal_spheric()
{

}


inline TYPE delta_m(const int& m)
{
	return m == 0 ? 0.5 : 1;
}

void CNormal_spheric::PrepareP(
	CMatrix &P, CMatrix &_P, const TYPE fi, const int _degree) const
{
	// чтобы мы обращались к конкретному порядку, а не вычитали 1
	auto degree = _degree + 1;	

	if (P.getRowCount() != degree)
	{
		P.setSize(degree, degree);
		_P.setSize(degree, degree);
	}

	for (auto n = 0; n < degree; n++)
	{
		for (auto m = 0; m < n + 1; m++)
		{
			if (n > m)
			{
				auto
					n2 = pow(n, 2),
					m2 = pow(m, 2);

				P[n][m] = P[n - 1][m]
					* sin(fi)
					* sqrt((4 * n2 - 1) / (n2 - m2));
					
				/* 
					Для исключительного случая, когда вычисляется P_1_m мы 
					просто не вычитаем второе слагаемое, так как произойдёт 
					обращение к отрицательному индексу.

					Поэтому, что сымитировать рекуретное выражение, мы принимаем,
					что P[-1][m] = 0 по условию P_nm = 0 при (n < m)
				*/
				if (n != 1)
				{
					P[n][m] -= P[n - 2][m]
						* sqrt((pow(n - 1, 2) - m2) * (2 * n + 1)
						/ ((n2 - m2) * (2 * n - 3)));
				}
			}
			else
			{
				if (n == m && m != 0)
				{
					P[n][m] = P[n - 1][m - 1] 
						* cos(fi) 
						* sqrt((2 * n + 1) / (2 * n) 
						* 1 / delta_m(m - 1));
				}
				else
				{
					if (n < m)
						P[n][m] = 0;
					else
						if (n == m && m == 0)
							P[n][m] = 1;
				}
			}

		}	// for (auto m = 0;...)

		for (auto m = 0; m < n + 1; m++)
		{
			_P[n][m] =
				-1 * m * tan(fi) * P[n][m];

			/* 
				Та же история, что и выше, только в другую сторону:

					P[n][m + 1] = 0, где m = n, то есть из условия 
					P_nm = 0 при (n < m)
			*/
			if (m != n)
			{
				_P[n][m] += 
					sqrt(delta_m(m) * (n - m) * (n + m + 1))
					* P[n][m + 1];
			}
		}
	}
}

CVector CNormal_spheric::ProjectOnDecart(
	const CVector &coord, const CVector& spheric) const
{
	/* 
		TODO: 
			- множественное создание локальных матриц и векторов - стоит исправить
			- деление на 0
			- ассемблер-стайл перемножение матрицы и вектора
			- возможно стоит вынести пересчёт матрицы SpherOnFix в отдельную ф-ию
	*/

	auto
		x = coord[0],
		y = coord[1],
		z = coord[2],

		ro = spheric[0],

		r_xy = sqrt(pow(x, 2) + pow(y, 2));

	if (r_xy == 0) r_xy = 0.00001; // костыльный костыль

	CMatrix SpherOnFix(VEC_SIZE, VEC_SIZE);

	SpherOnFix[0][0] =  x / ro;
	SpherOnFix[0][1] = -x * z / (ro * r_xy);
	SpherOnFix[0][2] = -y / r_xy;

	SpherOnFix[1][0] =  y / ro;
	SpherOnFix[1][1] = -y * z / (ro * r_xy);
	SpherOnFix[1][2] =  x / r_xy;

	SpherOnFix[2][0] =  z / ro;
	SpherOnFix[2][1] =  r_xy / ro;	
	SpherOnFix[2][2] =  0;

	return SpherOnFix * spheric;
}

CVector CNormal_spheric::getRight(const CVector& X) const
{
	CVector
		spher_coordinates = Transform::Decart2Spher(CVector::copyPart(X, 2));

	CMatrix P, _P;

	PrepareP(P, _P, spher_coordinates[1], 4);
	
	/* TODO: Написать основное вычисление ускорения */
	return spher_coordinates;
}
