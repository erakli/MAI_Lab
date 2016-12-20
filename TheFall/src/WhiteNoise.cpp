#include "WhiteNoise.h"

#include "Types.h"
#include "Constants.h"

#include <chrono>
#include <random>	// Для генерации Белого Шума

using namespace std;
using namespace Eigen;

/*
*	Генерация вектора (квази)Белого Шума по заданной частоте среза
*/
VectorXd GetWhiteNoise(TYPE omega, TYPE t0, TYPE t1, TYPE &dt)
{
	dt = 2 * PI / omega;		// интервал корреляции (квази)Белого Шума
	TYPE Disp = 1 / dt;			// его же дисперсия

	VectorXd WhiteNoise;
	size_t vector_size = int((t1 - t0) / dt) + 3;

	WhiteNoise.resize(vector_size);

	// construct a trivial random generator engine from a time - based seed :
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();

	// генератор с гауссовским нормальным распределением СВ
	default_random_engine generator;
	normal_distribution<TYPE> distribution(0, sqrt(Disp));

	generator.seed(seed);

	for (size_t i = 0; i < vector_size; i++)
		WhiteNoise(i) = distribution(generator);

	return WhiteNoise;
}
