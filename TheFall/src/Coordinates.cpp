//#include "Functions.h"
#include "Constants.h"

#include "Time.h"
#include "SolarSystem.h"

#include "Coordinates.h"

using namespace Eigen;

#ifdef DEBUG
#include <iostream>
using namespace std;
#endif

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
TYPE StarTime(TYPE JD)
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
TYPE StarTime(TYPE starTime, TYPE t)
//TYPE StarTime(const TYPE JD, const TYPE lambda)
{
//	TYPE
//		midNight = MyTime::getMidnight(JD),			// полночь текущего дня
//		t = (JD - midNight) * SECINDAY;	// t – время по шкале UTC в сек

	return 
		starTime + Earth::angularVeloc * t;
		//StarTime(midNight) + Earth::angularVeloc * t + lambda;
}



/* * * * * * namespace Transform * * * * * * * * * * * * * * * * * */
namespace Transform
{
	/*
		Создание матрицы поворота вокруг осей на угол

		угол - в радианах
	*/
	Matrix3d RotMatrix(BYTE axis, TYPE angle)
	{
		TYPE
			cos_t = cos(angle),
			sin_t = sin(angle);

		if (abs(cos_t) < 1.0e-16)
			cos_t = 0.0;

		if (abs(sin_t) < 1.0e-16)
			sin_t = 0.0;

		// создаем матрицу поворота
		//	CMatrix R(VEC_SIZE, VEC_SIZE);
		Matrix3d R;

		switch (axis)
		{
		case 1:
			// Матрица поворота вокруг ОХ

			R <<	1,	0,		0,
					0,	cos_t,	sin_t,
					0,	-sin_t,	cos_t;

			break;

		case 2:
			// Матрица поворота вокруг ОY

			R <<	cos_t,	0,	-sin_t,
					0,		1,	0,
					sin_t,	0,	cos_t;

			break;

		case 3:
			// Матрица поворота вокруг ОZ

			R <<	cos_t,	sin_t,	0,
					-sin_t,	cos_t,	0,
					0,		0,		1;

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
	Vector3d Fix2Topo(const Vector3d &fix_vector, const Vector3d &center_geographic)
	{
		TYPE
			h(center_geographic(0)), fi(center_geographic(1)), lambda(center_geographic(2));
		//x(fix_vector[0]), y(fix_vector[1]), z(fix_vector[2]);

		/*TYPE
			sin_fi = sin(fi),			cos_fi = cos(fi),
			sin_lambda = sin(lambda),	cos_lambda = cos(lambda);*/

		Vector3d Topo;
		Matrix3d temp;

		//Topo[0] = x * sin_lambda - y * cos_lambda;
		//Topo[1] = 
		//	x * cos_lambda * cos_fi 
		//	+ y * sin_lambda * cos_fi 
		//	+ z * sin_fi 
		//	- Earth::meanRadius - H;
		//Topo[2] = -x * cos_lambda * sin_fi - y * sin_lambda * sin_fi + z * cos_fi;

		temp = RotMatrix(1, PI_HALF - fi) * RotMatrix(3, PI_HALF + lambda);
		//temp = RotMatrix(2, -PI / 2.0) * RotMatrix(1, lambda - PI / 2.0);
		//temp = temp * RotMatrix(3, -fi);

		Topo = temp * fix_vector;
		Topo[2] -= h + Earth::meanRadius;

		return Topo;
	}


	/*
		перевод из сферических в декартовы координаты

		углы в радианах

		[h, fi, lambda] - высота, широта, долгота
	*/
	Vector3d Geographic2Fix(TYPE h, TYPE fi, TYPE lambda)
	{
		Vector3d Result;
		Result(0) = (h + Earth::meanRadius) * cos(fi) * cos(lambda);
		Result(1) = (h + Earth::meanRadius) * cos(fi) * sin(lambda);
		Result(2) = (h + Earth::meanRadius) * sin(fi);

		return Result;
	}

	/* Перегрузка с CVector на приём */
	Vector3d Geographic2Fix(const Vector3d &geographic)
	{
		auto
			h(geographic(0)),
			fi(geographic(1)),
			lambda(geographic(2));

		Vector3d Result;
		Result(0) = (h + Earth::meanRadius) * cos(fi) * cos(lambda);
		Result(1) = (h + Earth::meanRadius) * cos(fi) * sin(lambda);
		Result(2) = (h + Earth::meanRadius) * sin(fi);

		return Result;
	}



	/*
			Переход от декартовых координат к сферическим
	
			углы в радианах
	
			[ro, fi, lambda] - радиус-вектор, широта, долгота
		*/
	Vector3d Decart2Spher(const Vector3d& fix)
	{
		auto
			x = fix(0),
			y = fix(1),
			z = fix(2);

		Vector3d Result;

		Result(0) = fix.norm();
		Result(1) = atan2(z, sqrt(pow(x, 2) + pow(y, 2)));
		Result(2) = atan2(y, x);

		return Result;
	}



	Vector2d Fix2Horiz(const Vector3d &to_find_fix_vec, const Vector3d &center_geographic)
	{
		Vector3d center_fix_vec = Geographic2Fix(center_geographic);
		Vector3d vision_line = to_find_fix_vec - center_fix_vec;

		TYPE elevation = 0.0;

		TYPE norm = (center_fix_vec.norm() * vision_line.norm());
		if (norm != 0.0)
		{
			TYPE cos_z = center_fix_vec.dot(vision_line) / norm;

			TYPE z = acos(cos_z);
			elevation = PI_HALF - z;
		}

		Vector3d vision_line_topo = Fix2Topo(to_find_fix_vec, center_geographic);
		Vector3d projection_on_LHP = vision_line_topo;
		projection_on_LHP(2) = 0.0;		// y_t = 0.0

		TYPE azimuth = 0.0;

		TYPE projection_norm = projection_on_LHP.norm();
		if (projection_norm != 0.0)
		{
			// скалярное произведение проекции вектора линии визирования на МГП
			// и орта x_t (направление на север)
			Vector3d topo_north_vec(0.0, 1.0, 0.0);
			TYPE cos_az = projection_on_LHP.dot(topo_north_vec) / projection_norm;
			azimuth = acos(cos_az);

			if (projection_on_LHP(0) < 0)	// z_t < 0 (азимут против часовой)
				azimuth *= -1.0;
		}

		return Vector2d(elevation, azimuth);
	}
}


/* * * * * * namespace Orbit * * * * * * * * * * * * * * * * * * * */

/* 
*	Генерирование матрицы ориентации для перехода от элементов орбиты к
	декартовы 
*/
Matrix3d Orbit::OrientationMatrix(const Kepler_elements& elements)
{
	TYPE
		u = elements.omega + elements.teta;		// аргумент широты

	TYPE
		sin_u(		sin(u) ),					cos_u(		cos(u) ),
		sin_Omega(	sin(elements._Omega) ),		cos_Omega(	cos(elements._Omega) ),
		sin_i(		sin(elements.i) ),			cos_i(		cos(elements.i) );

	Matrix3d A;

	A(0, 0) =  cos_u * cos_Omega - sin_u * sin_Omega * cos_i;
	A(0, 1) = -sin_u * cos_Omega - cos_u * sin_Omega * cos_i;
	A(0, 2) =  sin_i * sin_Omega;

	A(1, 0) =  cos_u * sin_Omega + sin_u * cos_Omega * cos_i;
	A(1, 1) = -sin_u * sin_Omega + cos_u * cos_Omega * cos_i;
	A(1, 2) = -sin_i * cos_Omega;

	A(2, 0) =  sin_u * sin_i;
	A(2, 1) =  cos_u * sin_i;
	A(2, 2) =  cos_i;

	return A;
}

/* 
*	Переход от кеплеровских элементов орбиты к декартовым координатам (ИСК)
	
	Результат:
		Вектор из 6 компонент: 3 компоненты положения, 3 компоненты скорости
*/
Vector6d Orbit::Kepler2Decart(const Kepler_elements& elements)
{
	Vector3d _position = Vector3d::Zero();
	Vector3d _velocity = Vector3d::Zero();

	TYPE big_axis;

	/* На случай, если орбиту задали менее радиуса Земли, прибавляем его */
	if (elements.a < Earth::meanRadius)
		big_axis = elements.a + Earth::meanRadius;
	else
		big_axis = elements.a;

	TYPE
		p = big_axis * (1 - pow(elements.e, 2)),	// Фокальный параметр орбиты
		
		sin_teta = sin(elements.teta),
		cos_teta = cos(elements.teta);

	_position(0) = p / (1 + elements.e * cos_teta);


	TYPE
		sqrt_mu = sqrt(Earth::muEarth / p);

	_velocity(0) = sqrt_mu * elements.e * sin_teta;
	_velocity(1) = sqrt_mu * (1 + elements.e * cos_teta);


	Matrix3d A(OrientationMatrix(elements));

	_position = A * _position;
	_velocity = A * _velocity;

	Vector6d Res;
	Res << _position, _velocity;
	//Res.reserve(VEC_SIZE * 2);

	//Res.insert_toEnd(_position);
	//Res.insert_toEnd(_velocity);

	return Res;
}
