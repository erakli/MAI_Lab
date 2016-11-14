#include "LeastSquareMethod.h"

#include "DormanPrinceSolver.h"
#include <vector>

using namespace Eigen;
using namespace std;

LeastSquareMethod::LeastSquareMethod()
{
	p_model = nullptr;
	p_observation_model = nullptr;
}



void LeastSquareMethod::SetInitialCondition(const VectorXd& new_initial_condition)
{
	initial_condition = new_initial_condition;
}

void LeastSquareMethod::SetObservationsError(const VectorXd& observations_disp_vec)
{
	error_cov_matrix = observations_disp_vec.asDiagonal().inverse();
}

void LeastSquareMethod::SetObservations(const MatrixXd& observations_vec)
{
	observations = observations_vec;
}



void LeastSquareMethod::SetModel(Model * new_model_ptr)
{
	p_model = new_model_ptr;
}

void LeastSquareMethod::SetObservationModel(ObservationModel * new_observation_model_ptr)
{
	p_observation_model = new_observation_model_ptr;
}



// построение фундаментальной матрицы H
// t1 - время окончания построения опорной траектории
void LeastSquareMethod::InitH(TYPE t1)
{
	DormanPrinceSolver solver;
	solver.setEps_Max(1.0e-13);

	p_model->clearResult();
	p_model->set_t1(t1);

	p_model->setStart(initial_condition);
	solver.Run(*p_model);
	MatrixXd main_traectory = p_model->getResult();

	size_t initial_condition_size = initial_condition.size();

	vector<MatrixXd> var_traectories(initial_condition_size * 2);
	VectorXd var_initial_condition;

	TYPE delta;
	TYPE temp;
	size_t repeat;
	short sign;

	for (size_t i = 0; i < initial_condition.size(); i++)
	{
		var_initial_condition = initial_condition;
		delta = initial_condition(i) * 1.0e-3;	// делаем вариации на 3-4 порядка меньше в обе стороны

		temp = var_initial_condition(i);
		repeat = 0;

		// делаем вариации НУ 
		while (repeat < 2)
		{
			sign = (repeat == 0) ? -1 : 1;
			p_model->clearResult();
			
			var_initial_condition(i) += delta * sign;
			p_model->setStart(var_initial_condition);
			solver.Run(*p_model);
			var_traectories[i * 2 + repeat] = p_model->getResult();

			var_initial_condition(i) = temp;

			repeat++;
		}
	}

		
}