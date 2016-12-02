#include "Functions.h"
#include "Model.h"


using namespace Eigen;

Model::Model()
{
	s_size = 0;

	m_interval = 0.1; 
	Set_t0(0);
	Set_t1(5);

	result_size = 0;
	result_line_length = 0;

	stop_condition = 1.0e-5;
	stop_count = 0;
	stop_count_max = 5;
	stop_flag = false;
}

Model::Model(const Model& other)
{
	m_start_values = other.m_start_values;
	s_size = other.s_size;

	m_interval = other.m_interval;
	t0 = other.t0;
	t1 = other.t1;

	m_result = other.m_result;
	result_size = other.result_size;
	result_line_length = other.result_line_length;

	stop_condition = other.stop_condition;
	stop_count = other.stop_count;
	stop_count_max = other.stop_count_max;
	stop_flag = other.stop_flag;
}

Model::~Model()
{
	// nothing to do
}



Model& Model::operator=(const Model& right)
{
	if (this == &right)
		return *this;

	m_start_values = right.m_start_values;
	s_size = right.s_size;

	m_interval = right.m_interval;
	t0 = right.t0;
	t1 = right.t1;

	m_result = right.m_result;
	result_size = right.result_size;
	result_line_length = right.result_line_length;

	stop_condition = right.stop_condition;
	stop_count = right.stop_count;
	stop_count_max = right.stop_count_max;
	stop_flag = right.stop_flag;

	return *this;
}



void Model::Init(int argc, void** argv)
{
	SetResultSize();
}



bool Model::IsStopCalculation(
	TYPE t, TYPE step, const VectorXd& prev_step, const VectorXd& cur_step)
{
	return false;
}



void Model::AddResult(const VectorXd &X, TYPE t)
{
	VectorXd compile(X.size() + 1); // вектор результата + время
	compile << t, X;

	m_result.row(result_size) = compile;
	result_size++;
}

MatrixXd Model::GetResult(bool with_time) const
{
	MatrixXd trimmed_matrix = m_result.topRows(result_size);
//	trimmed_matrix.conservativeResize(result_size, NoChange);

	if (with_time)
		return trimmed_matrix;

	return trimmed_matrix.rightCols(trimmed_matrix.cols() - 1);
}

VectorXd Model::GetLastResult() const
{
	return m_result.row(result_size > 0 ? result_size - 1 : 0);
}

void Model::ClearResult()
{
	m_result.resize(0, 0);
	result_size = 0;
}



VectorXd Model::GetStart() const
{
	return m_start_values;
}

void Model::SetStart(const VectorXd &arg)
{
	// TODO: полностью заменить эту функцию SetStartValuesSize
	SetStartValuesSize(arg);
	//m_start_values = arg;
}



TYPE Model::GetInterval() const
{
	return m_interval;
}

void Model::SetInterval(TYPE arg)
{
	m_interval = arg;
}



TYPE Model::Get_t0() const
{
	return t0;
}

void Model::Set_t0(TYPE arg)
{
	t0 = arg;
}



TYPE Model::Get_t1() const
{
	return t1;
}

void Model::Set_t1(TYPE arg)
{
	t1 = arg;
}



void Model::SetStartValuesSize(size_t new_size, size_t result_line_expansion_by)
{
	m_start_values = VectorXd::Zero(new_size);
	s_size = new_size;
	result_line_length = new_size + result_line_expansion_by; // +1 для времени
}

void Model::SetStartValuesSize(const VectorXd& new_start_values, size_t result_line_expansion_by)
{
	SetStartValuesSize(new_start_values.size(), result_line_expansion_by);
	m_start_values = new_start_values;
}



void Model::SetResultSize()
{
	if (t0 > t1)
	{
		TYPE temp = t0;
		t0 = t1;
		t1 = temp;
	}

	if (t0 == t1)
		t1 += 1;

	size_t new_result_size = size_t(ceil((t1 - t0) / m_interval)) + 1;

	m_result = MatrixXd::Zero(new_result_size, result_line_length);
	result_size = 0;
}
