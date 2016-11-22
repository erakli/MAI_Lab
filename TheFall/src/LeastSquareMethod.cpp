#include "LeastSquareMethod.h"

#include <Constants.h>

#include <vector>

using namespace Eigen;
using namespace std;

LeastSquareMethod::LeastSquareMethod()
{
	// TODO: необходимо будет инициализировать
	t_start = 0.0;
	t_end = 0.0;

	p_model = nullptr;
	p_observation_model = nullptr;

	solver.SetEpsMax(1.0e-13);
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



void LeastSquareMethod::SetObservationSessionsVec(const UnsignedVector& new_observation_sessions_vec)
{
	observation_sessions_vec = new_observation_sessions_vec;
}




MatrixXd LeastSquareMethod::GenerateReferenceTrajectory()
{
	p_model->ClearResult();
	p_model->Set_t0(t_start);
	p_model->Set_t1(t_end);

	p_model->SetStart(initial_condition);
	solver.Run(*p_model);

	return p_model->GetResult();
}

MatrixXd LeastSquareMethod::GenerateReferenceObservations(const MatrixXd& reference_trajectory)
{
	VectorXd time_moments_of_observations = observations.col(0);
	size_t num_of_observations = time_moments_of_observations.size();

	p_observation_model->Init(num_of_observations);

	VectorXd row;
	Vector3d cur_pos;
	TYPE t;

	size_t cur_time = 0;
	size_t end_time;

	for (size_t i = 0; i < observation_sessions_vec.size(); i++)
	{
		end_time = cur_time + observation_sessions_vec[i];
		while (cur_time < end_time)
		{
			row = reference_trajectory.row(cur_time);
			cur_pos = row.segment(1, VEC_SIZE);
			t = time_moments_of_observations(cur_time);

			p_observation_model->SaveObservation(cur_pos, t);

			cur_time++;
		}
	}

	return p_observation_model->GetObservations();
}

MatrixXd LeastSquareMethod::EvalObservationsDeviation(const MatrixXd& reference_observations) const
{
	// TODO: надо осуществить вычитание из соответствующих моментов времени
	return 
		observations.rightCols(observations.cols() - 1) - 
		reference_observations.rightCols(reference_observations.cols() - 1);
}



// построение фундаментальной матрицы H
// t1 - время окончания построения опорной траектории
void LeastSquareMethod::EvalH()
{
	size_t initial_condition_size = initial_condition.size();

	vector<MatrixXd> var_traectories(initial_condition_size * 2);
	VectorXd var_initial_condition;

	VectorXd delta = VectorXd::Zero(initial_condition_size);

	TYPE temp;
	size_t repeat;
	short sign;

	for (size_t i = 0; i < initial_condition_size; i++)
	{
		var_initial_condition = initial_condition;
		delta(i) = initial_condition(i) * 1.0e-3;	// делаем вариации на 3-4 порядка меньше в обе стороны

		temp = var_initial_condition(i);
		repeat = 0;

		// делаем вариации НУ 
		while (repeat < 2)
		{
			sign = (repeat == 0) ? -1 : 1;
			p_model->ClearResult();
			
			var_initial_condition(i) += delta(i) * sign;
			p_model->SetStart(var_initial_condition);
			solver.Run(*p_model);
			var_traectories[i * 2 + repeat] = p_model->GetResult();

			var_initial_condition(i) = temp;

			repeat++;
		}
	}

	vector<MatrixXd> part_derivate_from_initial(initial_condition_size);
}