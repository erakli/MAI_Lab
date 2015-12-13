#pragma once

#include <math.h>
#include "Types.h"

#define PI 3.14159265358979323846

/* * * * * Вспомогательные функции * * * * */

// перевод из градусов в радианы
inline double deg2rad(const double &angle){
	return angle * PI / 180;
}

// дробная часть числа
inline double frac(const double X){
	return (X >= 0) ? X - trunc(X) : -(X - trunc(X));
}

// функции возведения в степень
inline double pow2(const double &arg){
	return arg * arg;
}

// модуль вектора известной длины
double module(double* X, ushort size);


/* * * * * Переход между СК * * * * */

// перевод из сферических в декартовы координаты
coord Spher2Fix(double ro, double fi, double lambda);
coord Spher2Fix(coord SpherCoord);

// из декартовых в сферические
coord Fix2Spher(coord FixCoord);


/* * * * * Очистка памяти * * * * */
inline void Clear(coord Vector){
	delete[] Vector;
}

inline void Clear(matrix Matrix){
	// проверить след. конструкцию
	ushort length = sizeof(Matrix) / sizeof(*Matrix);

	for (ushort i = 0; i < length; i++)
		Clear(*(Matrix + i));
}