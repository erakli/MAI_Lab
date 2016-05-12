#include <random>	// Для генерации Белого Шума
#include <exception>

#include "file_output.h"

#include "PID_model.h"

/* * * * * * * * * * CPID_controller * * * * * * * * * */

#define SYSTEM_COORDINATES		6
#define DISP_IN_SETTLED_MODE	5.0

CPID_controller::CPID_controller(){

	StartValues.setSize(SYSTEM_COORDINATES);
	s_size = StartValues.getSize();

	StartValues[0] = 0;		// x1
	StartValues[1] = 0;		// x2
	StartValues[2] = 0;		// y1
	StartValues[3] = 0;		// y2
	StartValues[4] = 0;		// y3
	StartValues[5] = 0;		// z1 (используется в сумме teta)

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

	calculation_of_statistics = false;	// без вычисления стат. характеристик

	correlation_interval_WhiteNoise = 0;
	WhiteNoise_got = false;

	size_K_vec = int((pow(s_size, 2) + s_size) / 2);

	linearisation_method = false; // первый метод линеаризации
}

/* 
*	Генерация вектора (квази)Белого Шума по заданной частоте среза
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

/*
*	Включение и отключение линеаризации. Вызывать строго перед интегрированием.
*/
void CPID_controller::ModelWithLinearisation(bool got_linearisation, bool linearisation_method)
{
	calculation_of_statistics = got_linearisation;

	if (calculation_of_statistics)
	{
		/* 
			Заполняем вектор НУ. Все значения нулевые, кроме диагональных элементов
			матрицы ковариации. Эти элементы - дисперсии - должны быть инициализированы
			значениями, бОльшими, чем дисперсия этих координат в установившемся режиме*/
		CMatrix K(SYSTEM_COORDINATES, SYSTEM_COORDINATES);
		for (auto i = 0; i < SYSTEM_COORDINATES; i++)
			K[i][i] = DISP_IN_SETTLED_MODE;
		CVector K_vectorized = CVector::SymmetricToVec(K);
		auto K_size = K_vectorized.getSize();

		StartValues.assign(K_size + SYSTEM_COORDINATES * 2, 0);

		for (auto i = 0; i < K_size; i++)
			StartValues[i] = K_vectorized[i];

		this->linearisation_method = linearisation_method;
	}
	else
	{
		StartValues.assign(SYSTEM_COORDINATES, 0);
	}
	
	s_size = StartValues.getSize();
}

/*
*	Входной БШ для Формирующего Фильтра.
*	Индекс - кратное интервалу корреляции целочисленное число - номер интервала
*/
TYPE CPID_controller::getWhiteNoise(cTYPE t)  const
{
	if (!WhiteNoise_got)
	{
		throw std::exception("WhiteNoise hasn't been generated");
	}

	TYPE index_WN;
	modf(t / correlation_interval_WhiteNoise, &index_WN);

	return WhiteNoise[int(index_WN)];
}

TYPE CPID_controller::NonLinearElement(TYPE delta1) const
{
	if (delta1 < -nonLinear_border)
		return -nonLinear_border;

	if ((delta1 >= -nonLinear_border) && (delta1 <= nonLinear_border))
		return delta1;
	
	return nonLinear_border;
}

TYPE CPID_controller::getEpsilon(cTYPE x1, cTYPE y1, cTYPE y2, cTYPE z1) const
{
	/* Уравнения связи */
	TYPE teta, tau;

	tau = y1 - extU;
	teta = k_coeff[0] * tau + z1 + k_coeff[2] * y2;

	return x1 - teta;
}

/*
*	Агрегат
*/
void CPID_controller::AperiodicElement(CVector &RightPart, 
	TYPE y1, TYPE y2, TYPE y3, TYPE input) const
{
	//CVector Result(3);

	/*Result[0] = y2;
	Result[1] = y3;
	Result[2] = (input * K_ag - y3 * ag[1] - y2 * ag[0] - y1) / ag[2];*/

	//return Result;

	RightPart.push_back(y2);
	RightPart.push_back(y3);
	RightPart.push_back(
		(input * K_ag - y3 * ag[1] - y2 * ag[0] - y1) / ag[2]
		);
}

/*
*	Формирующий фильтр
*/
void CPID_controller::ShapingFilter(CVector &RightPart, 
	TYPE x1, TYPE x2, TYPE input) const
{
	/*CVector Result(2);

	Result[0] = x2;
	Result[1] = 
		(input * K_ag - 2 * T_filter * xi_filter * x2 - x1) / pow(T_filter, 2);

	return Result;*/

	RightPart.push_back(x2);
	RightPart.push_back(
		(input * K_ag - 2 * T_filter * xi_filter * x2 - x1) / pow(T_filter, 2)
		);
}

CVector CPID_controller::SourceSystem(const CVector& X, cTYPE input_signal) const
{
	/* Буквенное представление проинтегрированных Правых Частей системы ДУ */
	TYPE x1, x2, y1, y2, y3, z1;

	x1 = X[0];
	x2 = X[1];
	y1 = X[2];
	y2 = X[3];
	y3 = X[4];
	z1 = X[5];

	/* Уравнения связи */
	TYPE alpha, epsilon, tau;

	tau = y1 - extU;
	epsilon = getEpsilon(x1, y1, y2, z1);
	alpha = NonLinearElement(epsilon);

	/* Формируем результирующий вектор как комбинацию векторов от всех звеньев */
	CVector Y;
	Y.reserve(s_size);

	/*Y.insert_toEnd(Shaping_filter);
	Y.insert_toEnd(Agregat);*/

	ShapingFilter(Y, x1, x2, input_signal);
	AperiodicElement(Y, y1, y2, y3, alpha);

	Y.push_back(k_coeff[1] * tau);	// прибавляем к системе z1

	return Y;
}

TYPE CPID_controller::getEpsilonDisp(const CMatrix& K, cTYPE mean) const
{
	/*
		D[epsilon] = M[epsilon^2] - M[epsilon]^2

		D[epsilon] = 
			D[x1] - 2 * k * K[x1, y1] - 2 * k_d * K[x1, x2] - 2 * K[x1, z1] + 

			+ k^2 * D[y1] + 2 * k * k_d * K[y1, y2] + 2 * k * K[y1, z1] +

			+ k_d^2 * D[y2] + 2 * k_d * K[y2, z1] +

			+ D[z1]
		
		M[epsilon] по идее принимаем 0, так как сигнал стационарный.
	*/

	return
		K[0][0]
		- 2 * k_coeff[0] * K[0][2]
		- 2 * k_coeff[2] * K[0][3]
		- 2 * K[0][5]

		+ pow(k_coeff[0], 2) * K[2][2]
		+ 2 * k_coeff[0] * k_coeff[2] * K[2][3]
		+ 2 * k_coeff[0] * K[2][5]

		+ pow(k_coeff[2], 2) * K[3][3]
		+ 2 * k_coeff[2] * K[3][5]

		+ K[5][5]
		
		- pow(mean, 2);
}

void CPID_controller::getA_Mtrx(CMatrix& A, cTYPE linearization_k) const
{
	A.setSize(SYSTEM_COORDINATES, SYSTEM_COORDINATES);

	A[0][0] = 0;
	A[0][1] = 1;
	A[0][2] = 0;
	A[0][3] = 0;
	A[0][4] = 0;
	A[0][5] = 0;

	A[1][0] = -1 / pow(T_filter, 2);
	A[1][1] = -2 * xi_filter / T_filter;
	A[1][2] = 0;
	A[1][3] = 0;
	A[1][4] = 0;
	A[1][5] = 0;

	A[2][0] = 0;
	A[2][1] = 0;
	A[2][2] = 0;
	A[2][3] = 1;
	A[2][4] = 0;
	A[2][5] = 0;

	A[3][0] = 0;
	A[3][1] = 0;
	A[3][2] = 0;
	A[3][3] = 0;
	A[3][4] = 1;
	A[3][5] = 0;

	A[4][0] = K_ag * linearization_k / ag[2];
	A[4][1] = 0;
	A[4][2] = - (1 + K_ag * k_coeff[0] * linearization_k) / ag[2];
	A[4][3] = - (ag[0] + K_ag * k_coeff[2] * linearization_k) / ag[2];
	A[4][4] = - ag[1] / ag[2];
	A[4][5] = - K_ag * linearization_k / ag[2];

	A[5][0] = 0;
	A[5][1] = 0;
	A[5][2] = k_coeff[1];
	A[5][3] = 0;
	A[5][4] = 0;
	A[5][5] = 0;
}

void CPID_controller::getB_Vector(CMatrix& B) const
{
	B.resize(1);
	B[0].assign(SYSTEM_COORDINATES, 0);

	//B[0] = 0;
	B[0][1] = K_filter / pow(T_filter, 2);
	//B[2] = 0;
	//B[3] = 0;
	//B[4] = 0;
	//B[5] = 0;
}

void CPID_controller::getC_Vector(CVector& C, cTYPE k0) const
{
	C.setSize(SYSTEM_COORDINATES);

	C[0] = 0;
	C[1] = 0;
	C[2] = 0;
	C[3] = 0;
	C[4] = K_ag * k0 / ag[2];
	C[5] = -k_coeff[1];
}

void CPID_controller::getC_Vector(CVector& C, cTYPE k1, cTYPE Mx, cTYPE fi_0) const
{
	C.setSize(SYSTEM_COORDINATES);

	C[0] = 0;
	C[1] = 0;
	C[2] = 0;
	C[3] = 0;
	C[4] = K_ag * (k1 * (-k_coeff[0] * extU - Mx) + fi_0) / ag[2];
	C[5] = -k_coeff[1];
}

CVector CPID_controller::LinearizedSystem(const CVector& full_system_vec, cTYPE input_signal) const
{
	CVector
		K_in = CVector::copyPart(full_system_vec, size_K_vec - 1),
		M_in = CVector::copyPart(full_system_vec, size_K_vec, size_K_vec + SYSTEM_COORDINATES - 1),
		X_in = CVector::copyPart(full_system_vec, size_K_vec + SYSTEM_COORDINATES, full_system_vec.getSize() - 1);

	/* Формирование статистических величин */

	CMatrix K = CSymmetricMatrix::VecToSymmetric(K_in);

	TYPE
		mean_epsilon = getEpsilon(M_in[0], M_in[2], M_in[3], M_in[5]),
		disp_epsilon = getEpsilonDisp(K, 0);

	LinearCoeff linearisation =
		Saturation.getCoefficients(nonLinear_border, mean_epsilon, disp_epsilon);

	TYPE 
		k0 = linearisation.fi_0 / mean_epsilon,
		k1;

	k1 = linearisation_method ? linearisation.k1_second : linearisation.k1_first;

#ifdef TESTS
	/*k0 = 0;
	k1 = 1;
	linearisation.fi_0 = 0;*/
#endif

	/* Формирование векторов и матриц для вычисления системы ДУ */

	CMatrix A0, A1, B_matrix;
	CVector B_vec, C0, C1;

	getA_Mtrx(A0, k0);
	getA_Mtrx(A1, k1);

	getB_Vector(B_matrix);

	getC_Vector(C0, k0);
	getC_Vector(C1, k1, mean_epsilon, linearisation.fi_0);

	/* Рассчёт правых частей системы ДУ */

	/*CMatrix 
		K_out(K.getRowCount(), K.getColCount()), 
		temp_matrix(K.getRowCount(), K.getColCount());

	CMatrix::Mult(A1, K, temp_matrix);
	CMatrix::Add(temp_matrix, K_out);
	CMatrix::Mult(K, A1.flip(), temp_matrix);
	CMatrix::Add(temp_matrix, K_out);
	CMatrix::Mult(B_matrix.flip(), B_matrix, temp_matrix);
	CMatrix::Add(temp_matrix, K_out);*/

	CMatrix K_out;

	K_out = A1 * K + K * A1.flip() + B_matrix.flip() * B_matrix;

	CVector dM, dX;

	B_vec = B_matrix[0];

	dM = A0 * M_in + C0;
	dX = A1 * X_in + B_vec * input_signal + C1;

	/* Формирование общего вектора системы (общей правой части) */

	CVector ret;
	ret.reserve(full_system_vec.getSize());

	ret.insert_toEnd(CVector::SymmetricToVec(K_out));
	ret.insert_toEnd(dM);
	ret.insert_toEnd(dX);

	return ret;
}

CVector CPID_controller::getRight(const CVector &X, TYPE t) const
{
	// Входной БШ для Формирующего Фильтра.
	TYPE nu = getWhiteNoise(t);

	if (calculation_of_statistics == false)
	{
		return SourceSystem(X, nu);
	}
	else
	{
		return LinearizedSystem(X, nu);
	}
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