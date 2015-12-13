#include "Coord_Transformation.h"

#include "Functions.h"
#include "Matrix_Operations.h"
#include "Earth.h"


/*
	Перевод из Гелицентрического положения в Геоцентрическое

	время в Юлианских днях
*/
coord GeoPos(const double Time, coord Pos){

	// Получили позицию Земли относительно Солнца
	coord Earth = EarthPos(Time);

	/*
		Новой позицией будет радиус вектор в Гелио-СК минус
		положение Земли
	*/
	coord NewPos = new double[VECSIZE];

	for (ushort i = 0; i < VECSIZE; i++)
		*(NewPos + i) = *(Pos + i) - *(Earth + i);

	return NewPos;
}

/*
	Перевод из инерциальной Геоцентрической в связанную
*/
coord Cel2Fix(const double Time, coord Pos){

	// Получили угол, на который повернулась Земля
	double
		ERA = EarthRotAngle(Time);

	// На основе этого угла создали матрицу поворота вокруг OZ
	matrix R = RotMatr(3, ERA);

	/* 
		Новое положение в связанной СК будет произведением
		матрицы поворота R на изначальную позицию
	*/
	coord NewPos = Mult(R, Pos);

	Clear(R); // проверить эту конструкцию

	return NewPos;

}


/*
	Непосредственный переход из Гелио- инерциальной в Гео- связанную
*/
coord Gelio2GeoFix(const double Time, coord Pos){

	return Cel2Fix(Time, GeoPos(Time, Pos));

}