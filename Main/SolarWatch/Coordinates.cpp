#include "Functions.h"
#include "Time.h"
#include "SolarSystem.h"

#include "Coordinates.h"

using namespace Earth;
//using namespace MyFunc;

/*
	Звёздным временем называется часовой угол точки весеннего
	равноденствия (ТВР). Вычисление текущего гринвичского
	звёздного времени в секундах (часовой угол ТВР на гринвичском
	меридиане):
		TYPE s

	Результат:
		Угол ориентации гринвичского меридиана, соответствующего
		периоду 0 - 2Pi, по отношению к направлению в ТВР в радианах.
*/
TYPE StarTime(const TYPE JD)
{
	TYPE
		d = JD - J2000,				// количество дней с 01.01.2000
		centuries = d / 36525.0;	// количество столетий, прошедших с 01.01.2000 г.

	TYPE s =
		67310.54841 - 43200	// -12 часов
		+ 8640184.812866 * centuries
		+ 0.093104 * pow(centuries, 2)
		- 6.2e-6 * pow(centuries, 3);

	TYPE
		res = 2 * PI / SECINDAY * fmod(s, SECINDAY);

	return res;
}


/*
	Прямой расчёт текущего звёздного времени места s

	результат в радианах
*/
TYPE StarTime(const TYPE starTime, const TYPE t)
//TYPE StarTime(const TYPE JD, const TYPE lambda)
{
//	TYPE
//		midNight = MyTime::getMidnight(JD),			// полночь текущего дня
//		t = (JD - midNight) * SECINDAY;	// t – время по шкале UTC в сек

	return 
		starTime + CEarth::angularVeloc * t;
		//StarTime(midNight) + CEarth::angularVeloc * t + lambda;
}



/* * * * * * namespace Transform * * * * * * * * * * * * * * * * * */

/*
	Создание матрицы поворота вокруг осей на угол

	угол - в радианах
*/
CMatrix Transform::RotMatrix(const BYTE axis, const TYPE angle)
{
	TYPE
		cos_t = cos(angle),
		sin_t = sin(angle);

	// создаем матрицу поворота
	CMatrix R(VEC_SIZE, VEC_SIZE);

	switch (axis)
	{
	case 1:
		// Матрица поворота вокруг ОХ

		R[0][0] = 1;	R[0][1] = 0;		R[0][2] = 0;

		R[1][0] = 0;	R[1][1] = cos_t;	R[1][2] = sin_t;

		R[2][0] = 0;	R[2][1] = -sin_t;	R[2][2] = cos_t;

		break;

	case 2:
		// Матрица поворота вокруг ОY

		R[0][0] = cos_t;	R[0][1] = 0;	R[0][2] = -sin_t;

		R[1][0] = 0;		R[1][1] = 1;	R[1][2] = 0;

		R[2][0] = sin_t;	R[2][1] = 0;	R[2][2] = cos_t;

		break;

	case 3:
		// Матрица поворота вокруг ОZ

		R[0][0] = cos_t;	R[0][1] = sin_t;	R[0][2] = 0;

		R[1][0] = -sin_t;	R[1][1] = cos_t;	R[1][2] = 0;

		R[2][0] = 0;		R[2][1] = 0;		R[2][2] = 1;

		break;

	default:
		//здесь нужен throw exeption
		break;

	}

	return R;
}

/*
	Перевод из геоцентрической СК в топоцентрическую с геокоординатами центра
	(H, fi, lambda).

	Должно работать только для сферической Земли

	Результат в топоцентрических осях - [z, x, y], 
	где 
		z - направлен по параллели на Восток,
		x - на Север по долготе
		y - по местной нормали
*/
CVector Transform::Fix2Topo(const CVector& fix_vector, const CVector &center_SpherPos)
{
	TYPE
		H(center_SpherPos[0]), fi(center_SpherPos[1]), lambda(center_SpherPos[2]);
		//x(fix_vector[0]), y(fix_vector[1]), z(fix_vector[2]);

	/*TYPE
		sin_fi = sin(fi),			cos_fi = cos(fi),
		sin_lambda = sin(lambda),	cos_lambda = cos(lambda);*/

	CVector Topo;
	CMatrix temp;

	//Topo[0] = x * sin_lambda - y * cos_lambda;
	//Topo[1] = 
	//	x * cos_lambda * cos_fi 
	//	+ y * sin_lambda * cos_fi 
	//	+ z * sin_fi 
	//	- CEarth::meanRadius - H;
	//Topo[2] = -x * cos_lambda * sin_fi - y * sin_lambda * sin_fi + z * cos_fi;

	temp = RotMatrix(1, PI / 2.0 - fi) * RotMatrix(3, PI / 2.0 + lambda);
	//temp = RotMatrix(2, -PI / 2.0) * RotMatrix(1, lambda - PI / 2.0);
	//temp = temp * RotMatrix(3, -fi);

	Topo = temp * fix_vector;
	Topo[2] -= H;

	return Topo;
}


/*
	перевод из сферических в декартовы координаты

	углы в радианах

	[h, fi, lambda] - высота, широта, долгота
*/
CVector Transform::Geographic2Fix(const TYPE h, const TYPE fi, const TYPE lambda)
{
	CVector Result(VEC_SIZE);
	Result[0] = (h + CEarth::meanRadius) * cos(fi) * cos(lambda);
	Result[1] = (h + CEarth::meanRadius) * cos(fi) * sin(lambda);
	Result[2] = (h + CEarth::meanRadius) * sin(fi);

	return Result;
}

/* Перегрузка с CVector на приём */
CVector Transform::Geographic2Fix(const CVector &geographic)
{
	auto 
		h(geographic[0]), 
		fi(geographic[1]), 
		lambda(geographic[2]);

	CVector Result(VEC_SIZE);
	Result[0] = (h + CEarth::meanRadius) * cos(fi) * cos(lambda);
	Result[1] = (h + CEarth::meanRadius) * cos(fi) * sin(lambda);
	Result[2] = (h + CEarth::meanRadius) * sin(fi);

	return Result;
}

/*
	Переход от декартовых координат к сферическим

	углы в радианах

	[ro, fi, lambda] - радиус-вектор, широта, долгота
*/
CVector Transform::Decart2Spher(const CVector& fix)
{
	auto
		x = fix[0],
		y = fix[1],
		z = fix[2];

	CVector Result(VEC_SIZE);
	
	Result[0] = fix.getLength();
	Result[1] = atan2(z, sqrt(pow(x, 2) + pow(y, 2)));
	Result[2] = atan2(y, x);

	return Result;
}


/* * * * * * namespace Orbit * * * * * * * * * * * * * * * * * * * */

/* 
*	Генерирование матрицы ориентации для перехода от элементов орбиты к
	декартовы 
*/
CMatrix Orbit::OrientationMatrix(const Kepler_elements& elements)
{
	TYPE
		u = elements.omega + elements.teta;		// аргумент широты

	TYPE
		sin_u(		sin(u) ),					cos_u(		cos(u) ),
		sin_Omega(	sin(elements._Omega) ),		cos_Omega(	cos(elements._Omega) ),
		sin_i(		sin(elements.i) ),			cos_i(		cos(elements.i) );

	CMatrix A(VEC_SIZE, VEC_SIZE);

	A[0][0] =  cos_u * cos_Omega - sin_u * sin_Omega * cos_i;
	A[0][1] = -sin_u * cos_Omega - cos_u * sin_Omega * cos_i;
	A[0][2] =  sin_i * sin_Omega;

	A[1][0] =  cos_u * sin_Omega + sin_u * cos_Omega * cos_i;
	A[1][1] = -sin_u * sin_Omega + cos_u * cos_Omega * cos_i;
	A[1][2] = -sin_i * cos_Omega;

	A[2][0] =  sin_u * sin_i;
	A[2][1] =  cos_u * sin_i;
	A[2][2] =  cos_i;

	return A;
}

/* 
*	Переход от кеплеровских элементов орбиты к декартовым координатам (ИСК)
	
	Результат:
		Вектор из 6 компонент: 3 компоненты положения, 3 компоненты скорости
*/
CVector Orbit::Kepler2Decart(const Kepler_elements& elements)
{
	CVector _position(VEC_SIZE), _velocity(VEC_SIZE);

	TYPE big_axis;

	/* На случай, если орбиту задали менее радиуса Земли, прибавляем его */
	if (elements.a < CEarth::meanRadius)
		big_axis = elements.a + CEarth::meanRadius;
	else
		big_axis = elements.a;

	TYPE
		p = big_axis * (1 - pow(elements.e, 2)),	// Фокальный параметр орбиты
		
		sin_teta = sin(elements.teta),
		cos_teta = cos(elements.teta);

	_position[0] = p / (1 + elements.e * cos_teta);


	TYPE
		sqrt_mu = sqrt(CEarth::muEarth / p);

	_velocity[0] = sqrt_mu * elements.e * sin_teta;
	_velocity[1] = sqrt_mu * (1 + elements.e * cos_teta);


	CMatrix A(OrientationMatrix(elements));

	_position = A * _position;
	_velocity = A * _velocity;

	CVector Res;
	Res.reserve(VEC_SIZE * 2);

	Res.insert_toEnd(_position);
	Res.insert_toEnd(_velocity);

	return Res;
}
