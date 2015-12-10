#pragma once

#include "Types.h"

#define PI 3.14159265358979323846

/* * * * * Вспомогательные функции * * * * */

// перевод из градусов в радианы
inline double deg2rad(const double &angle);

// дробная часть числа
inline ulong frac(const double X);

// функции возведения в степень
inline double pow2(const double &arg);

// модуль вектора известной длины
inline double module(double* X, ushort size);

/* * * * * Переход между СК * * * * */
// перевод из сферических в декартовы координаты
coord Spher2Fix(double ro, double fi, double lambda);
coord Spher2Fix(coord SpherCoord);

// из декартовых в сферические
coord Fix2Spher(coord FixCoord);