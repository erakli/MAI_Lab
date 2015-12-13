#include "Functions.h"

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
		fi = asin( *ptr_z / ro ),
		
		lambda = atan2( *ptr_y, *ptr_x ); // проверить правильность

	coord Result = new double[VECSIZE];

	Result[0] = ro;
	Result[1] = fi;
	Result[2] = lambda;

	return Result;

}