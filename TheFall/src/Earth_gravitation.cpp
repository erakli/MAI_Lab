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

#define NORMAL_DEGREE	4

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
		P.setSize(degree, 0);
		_P.setSize(degree, 0);
	}

	for (auto n = 0; n < degree; n++)
	{
		P[n].resize(n + 2, 0);
		_P[n].resize(n + 2, 0);

	/* Вычисляем псевдорекурентным методом нормированные функции Лежандра */
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

					Поэтому, чтобы сымитировать рекуретное выражение, мы принимаем,
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
					P[n][m] = P[n - 1][m - 1] 
						* cos(fi) 
						* sqrt((2 * n + 1) / (2 * n) 
						* 1 / delta_m(m - 1));
					
				if (n == m && m == 0)
					P[n][m] = 1;

				if (n < m)
					P[n][m] = 0;
			}
		}	// for (auto m = 0;...)

	/* Вычисляем производные функций на основе самих этих функций */
		for (auto m = 0; m < n + 1; m++)
		{
			_P[n][m] =
				-1 * m * tan(fi) * P[n][m];

			/* 
				Та же история, что и выше, только в другую сторону:

					P[n][m + 1] = 0, где m = n, то есть из условия 
					P_nm = 0 при (n < m)
			*/
			if (n != m)
			{
				_P[n][m] += 
					sqrt(delta_m(m) * (n - m) * (n + m + 1))
					* P[n][m + 1];
			}
		}
	}
}


/* 
	Рекуретная форма полиномов Лежандра 
*/
TYPE CNormal_spheric::P(const int n, const int m, const TYPE fi) const
{
	if (n < m)
		return 0;

	if (n == m && m == 0)
		return 1;

	if (n == m && m != 0)
		return
			P(n - 1, m - 1, fi)
			* cos(fi)
			* sqrt((2 * n + 1) / (2 * n)
			* (1 / delta_m(m - 1)));

	if (n > m)
	{
		auto
			n2 = pow(n, 2),
			m2 = pow(m, 2);

		return 
			P(n - 1, m, fi)
			* sin(fi)
			* sqrt((4 * n2 - 1) / (n2 - m2))
			
			- P(n - 2, m, fi)
			* sqrt((pow(n - 1, 2) - m2) * (2 * n + 1)
			/ ((n2 - m2) * (2 * n - 3)));
	}

	return 0;
}

TYPE CNormal_spheric::_P(const int n, const int m, const TYPE fi) const
{
	return
		-1 * m * tan(fi) * P(n, m, fi)
		+ sqrt(delta_m(m) * (n - m) * (n + m + 1))
		* P(n, m + 1, fi);
}

/*
	Вычисление переходной матрицы
	
	Пересчет частных производных потенциала V по сферическим координатам в
	соответствующие им частные производные по геоцентрическим прямоугольным 
	координатам выполняется с использованием переходной матрицы
*/
CMatrix CNormal_spheric::ProjectOnDecart(
	const CVector &coord, const CVector& spheric) const
{
	/* 
		TODO: 
			- деление на 0
			- возможно стоит вынести пересчёт матрицы SpherOnFix в отдельную ф-ию
	*/

	auto
		x = coord[0],
		y = coord[1],
		z = coord[2],

		ro = spheric[0],

		r_xy = sqrt(pow(x, 2) + pow(y, 2));

	if (r_xy == 0) r_xy = 1.0e-6; // костыльный костыль

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

	return SpherOnFix;
}


CVector CNormal_spheric::getRight(const CVector& X) const
{
	CVector
		fix_coordinates = CVector::copyPart(X, 2),
		spher_coordinates = Transform::Decart2Spher(fix_coordinates);
	
	/* 
		Коэффициенты, участвующие в вычислениях нормального 
		гравитационного ускорения 
	*/
	TYPE
		ro = spher_coordinates[0],
		fi = spher_coordinates[1],

		mu_ro2 = CEarth::muEarth / pow(ro, 2),

		ae_ro2 = pow(CEarth::ae / ro, 2),
		ae_ro4 = pow(ae_ro2, 2);

	/*
		Вычисление матриц нормированных функций Лежандра и их производных до
		заданного порядка
	*/

	CMatrix P_matrix, _P_matrix;
	PrepareP(P_matrix, _P_matrix, fi, NORMAL_DEGREE);

	/*
		Вычисление производных нормального гравитационного потенциала по 
		сферическим координатам
	*/
	CVector g_spher(VEC_SIZE);

	g_spher[0] = 
		-mu_ro2 
		+ 5 * mu_ro2 
		* (C_0_20 * ae_ro2 * P_matrix[2][0] + C_0_40 * ae_ro4 * P_matrix[4][0]);

	g_spher[1] = 
		-mu_ro2
		* (C_0_20 * ae_ro2 * _P_matrix[2][0] + C_0_40 * ae_ro4 * _P_matrix[4][0]);

	g_spher[2] = 0;


/* Подготовка результата */
	CVector Res;
	Res.reserve(X.getSize());
	Res.setSize(VEC_SIZE);

	Res[0] = X[3];
	Res[1] = X[4];
	Res[2] = X[5];

	/* 
		Пересчёт частных производных по сферическим координатам в 
		соответствующие им частные производные по геоцентрическим прямоугольным
		координатам
	*/
	Res.insert_toEnd(
		ProjectOnDecart(fix_coordinates, spher_coordinates) * g_spher);

	return Res;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* * * CAnomalous_spheric                              * * * */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

CAnomalous_spheric::CAnomalous_spheric()
{
	/*
		- считывание нормированных коэффициентов разложения
	*/
	C.setSize(NUM_OF_HARMONICS + 1, 0);
	S.setSize(NUM_OF_HARMONICS + 1, 0);

	int m_index = 0;

	for (auto n = 1; n < NUM_OF_HARMONICS + 1; n++)
	{
		C[n].resize(n + 1, 0);
		S[n].resize(n + 1, 0);

		for (auto m = 0; m < n + 1; m++)
		{
			C[n][m] = C_nm_coefficients[n + m_index] * CS_COEFF_MULTIPLIER;
			S[n][m] = S_nm_coefficients[n + m_index] * CS_COEFF_MULTIPLIER;

			m_index++;
		}

		m_index--;
	}
}

void CAnomalous_spheric::EvalAll(
	CVector &delta_g_spher, const CVector &spheric,
	const CMatrix &P, const CMatrix &_P) const
{
	TYPE
		ro, fi, lambda,

		cos_m, sin_m,  // заранее посчитанные значения cos и sin на шаг
		ae_ro,         // заранее считаемые степени (ae / ro)^n+1
		muEarth_ae_ro, // заранее посчитанное значение ( fM / (ae * ro) )

		div_ae_ro;      // значение ae / ro

	ro = spheric[0];
	fi = spheric[1];
	lambda = spheric[2];

	div_ae_ro = CEarth::ae / ro;
	ae_ro = pow(div_ae_ro, 2);

	muEarth_ae_ro = CEarth::muEarth / (CEarth::ae * ro);

	// сумма по каждой отдельной сферической координате
	CVector
		sum_inner(VEC_SIZE), 
		sum_outter(VEC_SIZE);

	for (auto n = 2; n < NUM_OF_HARMONICS + 1; n++)
	{
		sum_inner.assign(VEC_SIZE, 0);

		for (auto m = 0; m < n + 1; m++)
		{
			/* можно оптимизировать просчитав массив cos и sin заранее */
			sin_m = sin(m * lambda);
			cos_m = cos(m * lambda);

			// "внутренние" суммы - сложение по m
			sum_inner[0] += (C[n][m] * cos_m + S[n][m] * sin_m) * P[n][m];

			/* 
				здесь множитель - производная. а ещё здесь может быть 
				дополнительное умножение на cos */
			sum_inner[1] += (C[n][m] * cos_m + S[n][m] * sin_m) * _P[n][m];

			sum_inner[2] += (-C[n][m] * sin_m + S[n][m] * cos_m) * m * P[n][m];

		};

		ae_ro = ae_ro * (div_ae_ro); // степень n + 1

		// "внешние" суммы - сложение по n
		sum_outter[0] += (n + 1) * ae_ro * sum_inner[0];

		sum_outter[1] += ae_ro * sum_inner[1];

		sum_outter[2] += ae_ro * sum_inner[2];

	};

	delta_g_spher[0] = -muEarth_ae_ro * sum_outter[0];			// g_ro
	delta_g_spher[1] = -muEarth_ae_ro * sum_outter[1];			// g_fi
	delta_g_spher[2] = -muEarth_ae_ro / cos(fi) * sum_outter[2];// g_lambda

}

CVector CAnomalous_spheric::getRight(const CVector& X) const
{
	CVector
		fix_coordinates = CVector::copyPart(X, 2),
		spher_coordinates = Transform::Decart2Spher(fix_coordinates);

	/*
		Вычисление матриц нормированных функций Лежандра и их производных до
		заданного порядка
	*/
	CMatrix P_matrix, _P_matrix;
	PrepareP(P_matrix, _P_matrix, spher_coordinates[1], NUM_OF_HARMONICS);

	/* Аномалии гравитационного ускорения в сферических координатах */
	CVector delta_g_spher(VEC_SIZE);

	/* Вычисление аномалий гравитационного ускорения */
	EvalAll(delta_g_spher, spher_coordinates, P_matrix, _P_matrix);


/* Подготовка результата */
	CVector Res;
	Res.reserve(X.getSize());
	Res.setSize(VEC_SIZE);

	Res[0] = X[3];
	Res[1] = X[4];
	Res[2] = X[5];

	/*
		Вычисление нормальной составляющей ускорения
	*/
	TYPE moduleX3 = pow(fix_coordinates.getLength(), 3);

	CVector NormalPart(VEC_SIZE);
	CVector::Mult(-CEarth::muEarth / moduleX3, fix_coordinates, NormalPart);

	/*
		Пересчёт частных производных по сферическим координатам в
		соответствующие им частные производные по геоцентрическим прямоугольным
		координатам
	*/
	fix_coordinates = 
		ProjectOnDecart(fix_coordinates, spher_coordinates) * delta_g_spher;

	/* Результат - сумма нормальной и аномальной составляющих */
	CVector::Add(NormalPart, fix_coordinates);

	Res.insert_toEnd(fix_coordinates);

	return Res;
}