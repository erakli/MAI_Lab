#include "LeastSquareMethod.h"

#include <Constants.h>

#include <vector>

using namespace Eigen;
using namespace std;

LeastSquareMethod::LeastSquareMethod()
{
	// TODO: ���������� ����� ����������������
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

	size_t j = 0;

	for (size_t i = 0; i < num_of_observations; i++)
	{
		while (j < reference_trajectory_size)
		{
			if (time_moments_of_observations(i) == reference_trajectory(j, 0))
			{
				row = reference_trajectory.row(j);
				cur_pos = row.tail(VEC_SIZE);
				t = time_moments_of_observations(i);

				p_observation_model->SaveObservation(cur_pos, t);
				break;
			}

			j++;
		}
	}

	return p_observation_model->GetObservations();
}

MatrixXd LeastSquareMethod::EvalObservationsDeviation(const MatrixXd& reference_observations)
{
	// TODO: ���� ����������� ��������� �� ��������������� �������� �������
	return 
		observations.rightCols(observations.cols() - 1) - 
		reference_observations.rightCols(reference_observations.cols() - 1);
}



// ���������� ��������������� ������� H
// t1 - ����� ��������� ���������� ������� ����������
void LeastSquareMethod::InitH(TYPE t1)
{
	DormanPrinceSolver solver;
	solver.SetEpsMax(1.0e-13);

	p_model->ClearResult();
	p_model->Set_t1(t1);

	p_model->SetStart(initial_condition);
	solver.Run(*p_model);
	MatrixXd main_traectory = p_model->GetResult();

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
		delta = initial_condition(i) * 1.0e-3;	// ������ �������� �� 3-4 ������� ������ � ��� �������

		temp = var_initial_condition(i);
		repeat = 0;

		// ������ �������� �� 
		while (repeat < 2)
		{
			sign = (repeat == 0) ? -1 : 1;
			p_model->ClearResult();
			
			var_initial_condition(i) += delta * sign;
			p_model->SetStart(var_initial_condition);
			solver.Run(*p_model);
			var_traectories[i * 2 + repeat] = p_model->GetResult();

			var_initial_condition(i) = temp;

			repeat++;
		}
	}

		
}