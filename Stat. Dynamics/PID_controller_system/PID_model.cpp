#include <random>	// Для генерации Белого Шума
#include <exception>

#include "PID_model.h"

/* * * * * * * * * * CPID_controller * * * * * * * * * */

CPID_controller::CPID_controller(){

	StartValues.setSize(6);
	s_size = StartValues.getSize();

	StartValues[0] = 0;		// epsilon
	StartValues[1] = 0;		// y
	StartValues[2] = 0;		// beta
	StartValues[3] = 0;		// z1
	StartValues[4] = 0;		// z2
	StartValues[5] = 0;		// teta (используется в сумме x)

	extU = 1.7;			// управляющее воздействие

	nonLinear_border = 2.2;			// границы в нелинейном звене

	/* Коэффициенты в числителе и знаменателе Агрегата */
	K_ag	= 1.5;
	ag[0]	= 1.5;
	ag[1]	= 43;
	ag[2]	= 50;

	/* Коэффициенты в числителе и знаменателе Формирующего Фильтра */
	K_filter	= 4 / sqrt(7);
	T_filter	= 1 / 7.0;
	xi_filter	= 1;

	/* Коэффициенты ПИД-регулятора */
	k_coeff[0] = 0.63;		// gain
	k_coeff[1] = 0.0504;	// integrate
	k_coeff[2] = 1.9688;	// differentiate

	correlation_interval_WhiteNoise = 0;
	WhiteNoise_got = false;
}

/* 
	Генерация вектора (квази)Белого Шума по заданной частоте среза
*/
void CPID_controller::Generate_WhiteNoise(const TYPE omega)
{
	TYPE 
		dt = 2 * PI / omega,	// интервал корреляции (квази)Белого Шума
		Disp = 1 / dt;			// его же дисперсия

	WhiteNoise.reserve(int((t1 - t0) / dt) + 3);

	// генератор с гауссовским нормальным распределением СВ
	std::default_random_engine generator;
	std::normal_distribution<TYPE> distribution(0, sqrt(Disp));

	for (UINT i = 0; i < WhiteNoise.capacity(); i++)
		WhiteNoise.push_back(distribution(generator));

	correlation_interval_WhiteNoise = dt;
	WhiteNoise_got = true;

	//lookUp_of_WhiteNoise.push_back(WhiteNoise);
}

TYPE CPID_controller::get_correlation_interval() const
{
	return correlation_interval_WhiteNoise;
}

TYPE CPID_controller::NonLinearElement(TYPE delta1) const
{
	if (delta1 < -nonLinear_border)
		return -nonLinear_border;

	if ((delta1 >= -nonLinear_border) && (delta1 <= nonLinear_border))
		return delta1;
	
	return nonLinear_border;
}

/*
	Агрегат
*/
void CPID_controller::AperiodicElement(CVector &RightPart, 
	TYPE beta, TYPE z1, TYPE z2, TYPE alpha) const
{
	//CVector Result(3);

	/*Result[0] = z1;
	Result[1] = z2;
	Result[2] = (alpha * K_ag - z2 * ag[1] - z1 * ag[0] - beta) / ag[2];*/

	//return Result;

	RightPart.push_back(z1);
	RightPart.push_back(z2);
	RightPart.push_back(
		(alpha * K_ag - z2 * ag[1] - z1 * ag[0] - beta) / ag[2]
		);
}

/*
	Формирующий фильтр
*/
void CPID_controller::ShapingFilter(CVector &RightPart, 
	TYPE epsilon, TYPE y, TYPE nu) const
{
	/*CVector Result(2);

	Result[0] = y;
	Result[1] = 
		(nu * K_ag - 2 * T_filter * xi_filter * y - epsilon) / pow(T_filter, 2);

	return Result;*/

	RightPart.push_back(y);
	RightPart.push_back(
		(nu * K_ag - 2 * T_filter * xi_filter * y - epsilon) / pow(T_filter, 2)
		);
}

CVector CPID_controller::getRight(const CVector &X, TYPE t) const
{
	/* Буквенное представление проинтегрированных Правых Частей системы ДУ */
	TYPE epsilon, y, beta, z1, z2, teta;

	epsilon = X[0];
	y		= X[1];
	beta	= X[2];
	z1		= X[3];
	z2		= X[4];
	teta	= X[5];

	/* Уравнения связи */
	TYPE x, alpha, delta, tau;

	tau = beta - extU;
	x = k_coeff[0] * tau + teta + k_coeff[2] * z1;
	delta = epsilon - x;
	alpha = NonLinearElement(delta);

	/* 
		Входной БШ для Формирующего Фильтра. 
		Индекс - кратное интервалу корреляции целочисленное число - номер интервала
	*/
	if (! WhiteNoise_got)
	{
		throw std::exception("WhiteNoise hasn't been generated");
	}

	TYPE index_WN;
	modf(t / correlation_interval_WhiteNoise, &index_WN);

	TYPE nu = WhiteNoise[int(index_WN)];

	/*CVector 
		Shaping_filter = ShapingFilter(epsilon, y, nu),
		Agregat = AperiodicElement(beta, z1, z2, alpha);*/

	/*int size = Elem.getSize();
	for (int i = 0; i < size; i++)
		Y[i] = Elem[i];*/

	/* Формируем результирующий вектор как комбинацию векторов от всех звеньев */
	CVector Y;
	Y.reserve(s_size);

	/*Y.insert_toEnd(Shaping_filter);
	Y.insert_toEnd(Agregat);*/

	ShapingFilter(Y, epsilon, y, nu);
	AperiodicElement(Y, beta, z1, z2, alpha);

	Y.push_back(k_coeff[1] * tau);	// прибавляем к системе Teta[2]

	return Y;
}

bool CPID_controller::Stop_Calculation(TYPE t, TYPE, CVector &PrevStep, CVector &CurStep)
{
	/*TYPE delta = abs(PrevStep[0] - CurStep[0]);

	if ((delta < 1.0e-8) && (t != 0))
		stop_count++;
		
	if (stop_count >= stop_count_max) 
		return true;
	else */
		return false;
}

//void CPID_controller::addResult(CVector &X, TYPE t){
//	CModel::addResult(X, t);
//
//	PosXY *pStruct = new PosXY;
//	pStruct->posX = t;
//	pStruct->posY = X[0];
//
//	PostMessage(hWnd, WM_ADDPOINT, 0, (LPARAM)pStruct);
//}