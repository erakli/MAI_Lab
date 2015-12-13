#include "Matrix_Operations.h"

#include <math.h>


/*
	Умножение Матрицы на Вектор
*/
coord Mult(matrix Matr, coord Vec){

	coord Result = new double[VECSIZE];

	for (ushort i = 0; i < VECSIZE; i++)
	{

		double Sum = 0;
		for (ushort j = 0; j < VECSIZE; j++)
			Sum += *(Vec + j) * *(*(Matr + i) + j);

		*(Result + i) = Sum;
	}

	return Result;

}

/*
	Создание матрицы вращения

	Входной угол в радианах
*/
matrix RotMatr(const ushort axis, const double angle){

	double
		cos_t = cos(angle),
		sin_t = sin(angle);

	// создаем матрицу поворота - проверить правильность
	matrix R = new coord[VECSIZE];
	for (ushort i = 0; i < VECSIZE; i++)
		*(R + i) = new double[VECSIZE];
		//R[i] = new double[VECSIZE];

	switch (axis)
	{
		case 1:
			// Матрица поворота вокруг ОХ

			*(*(R + 0) + 0) = 1;	*(*(R + 0) + 1) = 0;		*(*(R + 0) + 2) = 0;

			*(*(R + 1) + 0) = 0;	*(*(R + 1) + 1) = cos_t;	*(*(R + 1) + 2) = sin_t;

			*(*(R + 2) + 0) = 0;	*(*(R + 2) + 1) = -sin_t;	*(*(R + 2) + 2) = cos_t;

			break;

		case 2:
			// Матрица поворота вокруг ОY

			*(*(R + 0) + 0) = cos_t;	*(*(R + 0) + 1) = 0;	*(*(R + 0) + 2) = -sin_t;

			*(*(R + 1) + 0) = 0;		*(*(R + 1) + 1) = 1;	*(*(R + 1) + 2) = 0;

			*(*(R + 2) + 0) = sin_t;	*(*(R + 2) + 1) = 0;	*(*(R + 2) + 2) = cos_t;

			break;

		case 3:
			// Матрица поворота вокруг ОZ

			*(*(R + 0) + 0) = cos_t;	*(*(R + 0) + 1) = sin_t;	*(*(R + 0) + 2) = 0;

			*(*(R + 1) + 0) = -sin_t;	*(*(R + 1) + 1) = cos_t;	*(*(R + 1) + 2) = 0;

			*(*(R + 2) + 0) = 0;		*(*(R + 2) + 1) = 0;		*(*(R + 2) + 2) = 1;

			break;

		default:
			//здесь нужен throw exeption
			break;

	}

	return R;

}