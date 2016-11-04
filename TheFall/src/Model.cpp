#include "Functions.h"
#include "Model.h"


using namespace Eigen;

Model::Model()
{
	s_size = 0;

	Interval = 0.1; 
	set_t0(0);
	set_t1(5);

	last_result_idx = 0;

	stop_condition = 1.0e-5;
	stop_count = 0;
	stop_count_max = 5;
	stop_flag = false;
}

Model::Model(const Model& other)
{
	StartValues = other.StartValues;

	s_size = other.s_size;

	Interval = other.Interval;
	t0 = other.t0;
	t1 = other.t1;

	Result = other.Result;
	last_result_idx = other.last_result_idx;

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

	StartValues = right.StartValues;

	s_size = right.s_size;

	Interval = right.Interval;
	t0 = right.t0;
	t1 = right.t1;

	Result = right.Result;

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



bool Model::Stop_Calculation(
	TYPE t, TYPE Step, VectorXd& PrevStep, VectorXd& CurStep)
{
	return false;
}



void Model::addResult(const VectorXd &X, TYPE t)
{
	VectorXd compile(X.size() + 1); // вектор результата + время
	compile << t, X;

	Result.row(last_result_idx) = compile;
	last_result_idx++;
}

MatrixXd Model::getResult() const
{
	return Result;
}

VectorXd Model::getLastResult() const
{
	return Result.row(last_result_idx);
}

void Model::clearResult()
{
	Result.resize(0, 0);
	last_result_idx = 0;
}



VectorXd Model::getStart() const
{
	return StartValues;
}

void Model::setStart(const VectorXd &arg)
{
	StartValues = arg;
}



TYPE Model::getInterval() const{
	return Interval;
}

void Model::setInterval(TYPE arg)
{
	Interval = arg;
}



TYPE Model::get_t0() const
{
	return t0;
}

void Model::set_t0(TYPE arg)
{
	t0 = arg;
}



TYPE Model::get_t1() const
{
	return t1;
}

void Model::set_t1(TYPE arg)
{
	t1 = arg;
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

	size_t result_size = size_t(ceil((t1 - t0) / Interval));

	Result = MatrixXd::Zero(result_size, s_size + 1);	// +1 для времени
	last_result_idx = 0;
}
