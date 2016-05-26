#include <iterator>
#include "Functions.h"
#include "Model.h"

/* * * * * * * * * * CModel * * * * * * * * * */

CModel::CModel()
{
	s_size = 0;

	Interval = 0.1; // перенести на ручной ввод
	t0 = 0;
	t1 = 5;

	result_matrix_position = 0;
	large_result_flag = false;

	stop_condition = 1.0e-5;

	stop_count = 0;
	stop_count_max = 5;
	stop_flag = false;
}

void CModel::addResult(CVector &X, TYPE t){
	CVector compile(X); // вектор результата + время
	compile.insert(0, t);

	if (! large_result_flag)
	{	// если ожидается менее 1 млн. результатов, пишем в матрицу
		Result_Matrix.push_back(compile);
		result_matrix_position++;
	}
	else
	{	// иначе заносим результаты в List
		Result.push_back(compile);
	}
}

// ----- свойства
CVector CModel::getStart() const{
	return StartValues;
}

TYPE CModel::getInterval() const{
	return Interval;
}

TYPE CModel::get_t0() const{
	return t0;
}

TYPE CModel::get_t1() const{
	return t1;
}

CMatrix CModel::getResult(){
	if (! large_result_flag)
	{
		if (Result_Matrix.getRowCount() != result_matrix_position)
			Result_Matrix.setSize(result_matrix_position, s_size);

		return Result_Matrix;
	}
	else
	{
		CMatrix Output;

		std::copy(Result.begin(), Result.end(), std::back_inserter(Output));

		return Output;
	}
}

CVector CModel::getLastResult()
{
	if (!large_result_flag)
	{
		return Result_Matrix[result_matrix_position - 1];
	}
	else
	{
		List::iterator it = Result.end();

		return *(--it);
	}
}

void CModel::clearResult()
{
	Result_Matrix.clear();	// надеюсь он вызовет все деструкторы
	Result.clear();
	result_matrix_position = 0;
}


void CModel::setResultType()
{
	int num_of_results = int((t1 - t0) / Interval) + 1;	

	// если ожидается более LISTLIMIT результатов, производим запись в List
	if (num_of_results >= LISTLIMIT)
	{
		// проверяем и очищаем список
		if (!Result.empty()) Result.clear();

		large_result_flag = true;
	}
	else
	{
		// очистим перед этим матрицу, если там что-то есть
		if (!Result_Matrix.empty())
		{
			Result_Matrix.clear();
			result_matrix_position = 0;
		}

		// иначе создадим сразу большую матрицу результатов и будем её заполнять
		Result_Matrix.reserve(num_of_results);
		large_result_flag = false;
	}
}

void CModel::setStart(CVector &arg){
	StartValues = arg;
}

void CModel::setInterval(const TYPE &arg){
	Interval = arg;
}

void CModel::set_t0(const TYPE &arg){
	t0 = arg;
}

void CModel::set_t1(const TYPE &arg){
	t1 = arg;
}

bool CModel::Stop_Calculation(double t, double Step, CVector& PrevStep, CVector& CurStep)
{
	return false;
}

// ----- конец свойств


/* * * * * * * * * * TArenstorfModel * * * * * * * * * */

TArenstorfModel::TArenstorfModel(int variant){

	StartValues.setSize(4);
	s_size = StartValues.getSize();

	m = 0.012277471;
	M = 1 - m;

	orbit = variant;

	StartValues[0] = 0.994; // y1
	StartValues[1] = 0;     // y2
	StartValues[2] = 0;     // y1'
	if (orbit) // выбираем большую орбиту
	{
		StartValues[3] = -2.00158510637908252240537862224; // y2'
		Period = 17.0652165601579625588917206249;
	}
	else // иначе малую
	{
		StartValues[3] = -2.0317326295573368357302057924; // y2'	
		Period = 11.124340337266085134999734047;
	}
}

using namespace MyFunc;

CVector TArenstorfModel::getRight(const CVector &X, TYPE t) const{
	CVector Y(s_size);
	TYPE
		R[2] = 
		{
			pow(pow(X[0] + m, 2) + pow(X[1], 2), 1.5),
			pow(pow(X[0] - M, 2) + pow(X[1], 2), 1.5)
		};

	Y[0] = X[2]; // v1 = y1' - замена переменной. После интегрирования получим y1
	Y[1] = X[3]; // v2 = y2'
	Y[2] = X[0] + 2 * X[3] - M * (X[0] + m) / R[0] - m * (X[0] - M) / R[1];
	Y[3] = X[1] - 2 * X[2] - M * X[1] / R[0] - m * X[1] / R[1];
	return Y; // заглушка
}