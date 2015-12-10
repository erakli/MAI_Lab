#include <math.h>

#include "Functions.h"

// перевод из градусов в радианы
double deg2rad(const double &angle){
	return angle * PI / 180;
}

// дробная часть числа
ulong frac(const double X){

	return (X >= 0) ? X - trunc(X) : -(X - trunc(X));

}

// функции возведения в степень
double pow2(const double &arg){
	return arg * arg;
}

// модуль вектора известной длины
double module(double* X, ushort size){

	if (!size) return 0; // если передан 0 размер

	double Result = 0;
	for (ushort i = 0; i < size; i++)
		Result += pow2(*(X + i));

	return sqrt(Result);
}


/*
	перевод из сферических в декартовы координаты

	углы в радианах
*/
coord Spher2Fix(double ro, double fi, double lambda){

	coord Result = new double[VECSIZE];

	Result[0] = ro * cos(fi) * cos(lambda);
	Result[1] = ro * cos(fi) * sin(lambda);
	Result[2] = ro * sin(fi);

	return Result;

}

coord Spher2Fix(coord SpherCoord){

	double
		ro = *SpherCoord,
		fi = *(SpherCoord + 1),
		lambda = *(SpherCoord + 2);

	return Spher2Fix(ro, fi, lambda);

}


/*
	из декартовых в сферические

	углы на выходе в радианах
*/
coord Fix2Spher(coord FixCoord){

	double ro = module(FixCoord, VECSIZE);

	// нужна обработка на ro = 0 (выход)

	double
		*ptr_x = FixCoord,
		*ptr_y = FixCoord + 1,
		*ptr_z = FixCoord + 2;

	// ещё проверка на равенство проекции ro на XoY 0

	double 
		SqrSum = pow2(*ptr_x) + pow2(*ptr_y),
		
		fi = atan( *ptr_z / sqrt(SqrSum) ),
		
		lambda = atan( *ptr_y / *ptr_x ); // проверить, чтобы здесь был дробный результат

	if ((*ptr_x > 0) && (*ptr_y >= 0))
	{
		
	}
	else
	{
		if (*ptr_x <= 0)
			lambda += PI;

		else
			if ((*ptr_x >= 0) && (*ptr_y < 0))
				lambda += 2 * PI;
			
			// финальное ИНАЧЕ с выходом сюда
	}

	coord Result = new double[VECSIZE];

	Result[0] = ro;
	Result[1] = fi;
	Result[2] = lambda;

}