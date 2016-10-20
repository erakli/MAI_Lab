#include <random>	// Для генерации Белого Шума

#include "Types.h"
#include "Matrix_classes.h"

#include "WhiteNoise.h"

/*
*	Генерация вектора (квази)Белого Шума по заданной частоте среза
*/
CVector Get_WhiteNoise(cTYPE omega, cTYPE t0, cTYPE t1, TYPE &dt)
{
	dt = 2 * PI / omega;		// интервал корреляции (квази)Белого Шума
	TYPE Disp = 1 / dt;			// его же дисперсия

	CVector WhiteNoise;

	WhiteNoise.reserve(int((t1 - t0) / dt) + 3);

	// генератор с гауссовским нормальным распределением СВ
	std::default_random_engine generator;
	std::normal_distribution<TYPE> distribution(0, sqrt(Disp));

	for (UINT i = 0; i < WhiteNoise.capacity(); i++)
		WhiteNoise.push_back(distribution(generator));

	return WhiteNoise;
}
