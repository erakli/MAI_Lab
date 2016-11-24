#include "LeastSquareMethod.h"

#include <Constants.h>

#include <vector>

using namespace Eigen;
using namespace std;



#define NUM_OF_DEVIATIONS	2



LeastSquareMethod::LeastSquareMethod()
{
	// TODO: ���������� ����� ����������������
	t_start = 0.0;
	t_end = 0.0;

	p_model = nullptr;
	p_observation_model = nullptr;

	solver.SetEpsMax(1.0e-13);
}



void LeastSquareMethod::Run()
{
	MatrixXd reference_trajectory;
	reference_trajectory = GenerateReferenceTrajectory();
	reference_trajectory = SelectOnlyObservedTimeMoments(reference_trajectory);
	MatrixXd reference_observations = GenerateReferenceObservations(reference_trajectory);
	MatrixXd observations_deviation = EvalObservationsDeviation(reference_observations);
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



void LeastSquareMethod::SetObservationSessionsVec(const ObservationSessionsVector& new_observation_sessions_vec)
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

	return p_model->GetResult(false);	// ����� ��� �������
}

MatrixXd LeastSquareMethod::SelectOnlyObservedTimeMoments(const MatrixXd & reference_trajectory) const
{
	size_t num_of_observations = observations.rows();

	MatrixXd selected_time_moments;
	selected_time_moments = MatrixXd::Zero(num_of_observations, reference_trajectory.cols());

	// TODO: �������, ��� ������� ���������� �������� �� ������� ������� �������
	// ����������
	size_t first_start_time = observation_sessions_vec.front().start_moment;
	size_t cur_time = 0;
	size_t end_time;
	size_t j = 0;

	for (size_t i = 0; i < observation_sessions_vec.size(); i++)
	{
		cur_time = observation_sessions_vec[i].start_moment - first_start_time;
		end_time = observation_sessions_vec[i].end_moment - first_start_time;
		while (cur_time < end_time)
		{
			// ������� ������� ������� ��������������� � ������������
			// � �������� ��������� � ������� ����������
			selected_time_moments.row(j) = reference_trajectory.row(cur_time);

			cur_time++;
			j++;
		}
	}

	return selected_time_moments;
}

MatrixXd LeastSquareMethod::GenerateReferenceObservations(const MatrixXd& reference_trajectory)
{
	size_t num_of_observations = observations.rows();

	p_observation_model->Init(num_of_observations);

	VectorXd row;
	Vector3d cur_pos;
	TYPE t;

	for (size_t i = 0; i < reference_trajectory.rows(); i++)
	{
		row = reference_trajectory.row(i);
		cur_pos = row.head(VEC_SIZE);
		t = observations(i, 0);

		// ��� ������������
		p_observation_model->SaveObservation(cur_pos, t);
	}

	return p_observation_model->GetObservations();
}

MatrixXd LeastSquareMethod::EvalObservationsDeviation(const MatrixXd& reference_observations) const
{
	// TODO: ���� ����������� ��������� �� ��������������� �������� �������
	return 
		observations.rightCols(observations.cols() - 1) - 
		reference_observations.rightCols(reference_observations.cols() - 1);
}



// ���������� ��������������� ������� H
VectorOfMatrix LeastSquareMethod::EvalPartDerivateFromInitial()
{
	size_t initial_condition_size = initial_condition.size();

	VectorOfMatrix part_derivate_from_initial(initial_condition_size);

	VectorXd delta = VectorXd::Zero(initial_condition_size);
	VectorXd var_initial_condition = initial_condition;

	MatrixXd var_traectories[NUM_OF_DEVIATIONS];
	short sign[NUM_OF_DEVIATIONS] = { 1, -1 };

	MatrixXd temp_trajectory;
	TYPE temp;

	for (size_t j = 0; j < initial_condition_size; j++)
	{
		delta(j) = initial_condition(j) * 1.0e-3;	// ������ �������� �� 3-4 ������� ������ � ��� �������

		temp = var_initial_condition(j);

		// ������ �������� �� 
		for (size_t deviation = 0; deviation < NUM_OF_DEVIATIONS; deviation++)
		{
			p_model->ClearResult();
			
			var_initial_condition(j) += delta(j) * sign[deviation];
			p_model->SetStart(var_initial_condition);
			solver.Run(*p_model);
			temp_trajectory = p_model->GetResult(false); // ��� �������
			var_traectories[deviation] = SelectOnlyObservedTimeMoments(temp_trajectory);

			var_initial_condition(j) = temp;
		}

		// ������ �� var_traectories ������� ������ �� ��������� ������� ���������, ����� �����������
		part_derivate_from_initial[j] =
			(var_traectories[0] - var_traectories[1]) / (2 * delta(j));
	}

	return part_derivate_from_initial;
}

VectorOfMatrix LeastSquareMethod::EvalPartDerivateFromState(const MatrixXd & reference_trajectory)
{
	// TODO: ���������� �������� �� �� ���������
	size_t state_vec_size = reference_trajectory.cols();
	size_t num_of_observations = observations.rows();

	VectorOfMatrix part_derivate_from_state(state_vec_size);

	VectorXd delta = VectorXd::Zero(state_vec_size);
	VectorXd var_state_vector;

	MatrixXd var_observations[NUM_OF_DEVIATIONS];
	short sign[NUM_OF_DEVIATIONS] = { 1, -1 };

	for (size_t deviation = 0; deviation < NUM_OF_DEVIATIONS; deviation++)
	{
		var_observations[deviation] = MatrixXd::Zero(NoChange, state_vec_size);
	}

	VectorXd temp_observation;
	TYPE temp;
	TYPE t;

	for (size_t i = 0; i < num_of_observations; i++)
	{
		var_state_vector = reference_trajectory.row(i);
		t = observations(i, 0);

		for (size_t k = 0; k < state_vec_size; k++)
		{
			delta(k) = var_state_vector(k) * 1.0e-3;	// ������ �������� �� 3-4 ������� ������ � ��� �������
			temp = var_state_vector(k);

			for (size_t deviation = 0; deviation < NUM_OF_DEVIATIONS; deviation++)
			{
				var_state_vector(k) += delta(k) * sign[deviation];

				// TODO: ��������� � ������������ ������� �� ����� � �������
				temp_observation = p_observation_model->MakeObservation(var_state_vector, t);
				var_observations[deviation].col(k) = temp_observation;

				var_state_vector(i) = temp;
			}
		}

		// TODO: ������, ��� ��������� ����������� ��� ��
	}
}