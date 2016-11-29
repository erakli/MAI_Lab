#include "LeastSquareMethod.h"

#include <Constants.h>

#include <vector>

using namespace Eigen;
using namespace std;



#define NUM_OF_DEVIATIONS	2
#define CONSOLE_OUTPUT
#define TEST

#ifdef CONSOLE_OUTPUT
#include <iostream>
using namespace std;
#endif

#ifdef TEST
#include "file_output.h"
#endif

LeastSquareMethod::LeastSquareMethod()
{
	// TODO: необходимо будет инициализировать
	t_start = 0.0;
	t_end = 0.0;

	p_model = nullptr;
	p_observation_model = nullptr;

	solver.SetEpsMax(1.0e-13);
}



MatrixXd LeastSquareMethod::Run(TYPE stop_condition)
{
	MatrixXd temp_reference_trajectory;
	MatrixXd reference_trajectory;
	MatrixXd reference_observations;
	MatrixXd observations_deviation;
	MatrixXd matrix_H;
	MatrixXd D_eta;
	MatrixXd H_D_eta;
	VectorXd delta_X;

	size_t iter = 0;
	size_t max_iter = 7;

	// TODO: будем записывать сюда все итерации
	MatrixXd log_matrix = MatrixXd::Zero(max_iter, initial_condition.size());

#ifdef CONSOLE_OUTPUT
	cout << endl << endl;
#endif

	do // while (delta_X.norm() >= stop_condition && iter < max_iter);
	{
		temp_reference_trajectory = GenerateReferenceTrajectory();
		reference_trajectory = SelectOnlyObservedTimeMoments(temp_reference_trajectory);
		reference_observations = GenerateReferenceObservations(reference_trajectory);
		observations_deviation = EvalObservationsDeviation(reference_observations);

		matrix_H = EvalH(reference_trajectory);

		D_eta = GetErrorCovMatrix();
		H_D_eta = matrix_H.transpose() * D_eta;

		delta_X = (H_D_eta * matrix_H).inverse() * H_D_eta * observations_deviation;

		initial_condition += delta_X;
		log_matrix.row(iter) = delta_X;

#ifdef CONSOLE_OUTPUT
		cout << endl << "iter = " << iter << endl;
		cout << "	delta_X.norm() = " << delta_X.norm() << endl;
		cout << "	delta_X: " << delta_X.transpose() << endl;
		cout << "	initial_condition: " << initial_condition.transpose() << endl;
#endif

		iter++;
	} while (delta_X.norm() >= stop_condition && iter < max_iter);

	log_matrix.conservativeResize(iter, NoChange);

	return log_matrix;
}



void LeastSquareMethod::SetInitialCondition(const VectorXd& new_initial_condition)
{
	initial_condition = new_initial_condition;
}

VectorXd LeastSquareMethod::GetInitialCondition() const
{
	return initial_condition;
}



void LeastSquareMethod::SetObservationsError(const VectorXd& observations_disp_vec)
{
	error_cov_vec = observations_disp_vec; // .asDiagonal().inverse();
}

void LeastSquareMethod::SetObservations(const MatrixXd& observations_vec)
{
	observations = observations_vec;
	t_start = observations(0, 0);	// считаем первый столбец матрицы - временем
	t_end = observations(observations.rows() - 1, 0);
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
#ifdef CONSOLE_OUTPUT
	cout << "GenerateReferenceTrajectory()" << endl;
#endif
	p_model->ClearResult();
	p_model->Set_t0(t_start);
	p_model->Set_t1(t_end);

	p_model->SetStart(initial_condition);
	solver.Run(*p_model);

	return p_model->GetResult(false);	// давай без времени
}

MatrixXd LeastSquareMethod::SelectOnlyObservedTimeMoments(const MatrixXd & reference_trajectory) const
{
#ifdef CONSOLE_OUTPUT
	cout << endl << "SelectOnlyObservedTimeMoments()" << endl;
	cout << "	reference_trajectory.rows() = " << reference_trajectory.rows() << endl;
	cout << "	observations.rows() = " << observations.rows() << endl;
	cout << "	first_observation = " << observations(0, 0) << endl;
#endif

	size_t num_of_observations = observations.rows();

	MatrixXd selected_time_moments;
	selected_time_moments = MatrixXd::Zero(num_of_observations, reference_trajectory.cols());

	// TODO: считаем, что опорная траектория строится из первого момента времени
	// наблюдений
	size_t first_start_time = observation_sessions_vec.front().start_moment;
	size_t cur_time;
	size_t end_time;
	size_t j = 0;

	for (size_t i = 0; i < observation_sessions_vec.size(); i++)
	{
		cur_time = observation_sessions_vec[i].start_moment - first_start_time;
		end_time = observation_sessions_vec[i].end_moment - first_start_time;
		while (cur_time < end_time)
		{
			// считаем моменты времени равноотстоящими и совпадающими
			// у реальных измерений и опорной траектории
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

		// без случайностей
		p_observation_model->SaveObservation(cur_pos, t);
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



MatrixXd LeastSquareMethod::GetErrorCovMatrix() const
{
	size_t observation_vec_size = observations.cols() - 1;
	size_t num_of_observations = observations.rows();
	VectorXd main_diag(num_of_observations * observation_vec_size);

	ArrayXd errors_disp_inversed = error_cov_vec.array().inverse();

	for (size_t i = 0; i < num_of_observations; i++)
	{
		main_diag.segment(i * observation_vec_size, observation_vec_size) =
			errors_disp_inversed;
	}

	// TODO: проверить вот на этом моменте
	return main_diag.asDiagonal();
}



MatrixXd LeastSquareMethod::EvalH(const MatrixXd& reference_trajectory)
{
#ifdef CONSOLE_OUTPUT
	cout << endl << "EvalH()" << endl;
#endif

	size_t initial_condition_size = initial_condition.size();
	size_t state_vector_size = reference_trajectory.cols();
	size_t num_of_observations = observations.rows();

	// TODO: вычисляем размер вектора измерений (считается, что
	// первым столбцом идёт время, а оно нам не нужно, поэтому и вычтем 1)
	size_t observations_vec_size = observations.cols() - 1; 

	MatrixXd matrix_H(num_of_observations * observations_vec_size, initial_condition_size);

	VectorOfMatrix from_state = EvalPartDerivateFromState(reference_trajectory);
	VectorOfMatrix from_initial = EvalPartDerivateFromInitial();

	MatrixXd ballistic_derivates(observations_vec_size, initial_condition_size);
	ArrayXd temp_sum;

	for (size_t i = 0; i < num_of_observations; i++)
	{
		for (size_t j = 0; j < initial_condition_size; j++)
		{
			temp_sum = ArrayXd::Zero(observations_vec_size);
			for (size_t k = 0; k < state_vector_size; k++)
			{
				// вектор-столбец частн. производной от измеряемых параметров
				// поэлементно умножается на частн. произв. от компонент вектора
				// состояния по компонентам вектора НУ
				temp_sum += from_state[i].col(k).array() * from_initial[j](i, k);
			}

			ballistic_derivates.col(j) = temp_sum.matrix();
		}

		// TODO: по идее, присваиваем значения очередной матрицы H_i,
		// которая состоит из баллистических производных. размерности должны
		// совпадать с выделяемым блоком
		matrix_H.block(		i * observations_vec_size,
							0, 
							observations_vec_size, 
							initial_condition_size) 
			= ballistic_derivates;

#ifdef CONSOLE_OUTPUT
		cout << "ballistic_derivates:" << endl;
		cout << ballistic_derivates << endl;

		cout << 
			"matrix_H.block(" << i * observations_vec_size << ", " << 
			0 << ", " << observations_vec_size << ", " << initial_condition_size << "):"<< endl;
		cout << matrix_H.block(i * observations_vec_size, 0, observations_vec_size, initial_condition_size);
#endif
	}

	return matrix_H;
}



// построение фундаментальной матрицы H
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
		delta(j) = initial_condition(j) * 1.0e-3;	// делаем вариации на 3-4 порядка меньше в обе стороны

		temp = var_initial_condition(j);

		// делаем вариации НУ 
		for (size_t deviation = 0; deviation < NUM_OF_DEVIATIONS; deviation++)
		{
			p_model->ClearResult();
			
			var_initial_condition(j) += delta(j) * sign[deviation];
			p_model->SetStart(var_initial_condition);
			solver.Run(*p_model);
			temp_trajectory = p_model->GetResult(false); // без времени
			var_traectories[deviation] = SelectOnlyObservedTimeMoments(temp_trajectory);

			var_initial_condition(j) = temp;
		}

		// каждый из var_traectories состоит только из компонент вектора состояния, время отсутствует
		part_derivate_from_initial[j] =
			(var_traectories[0] - var_traectories[1]) / (2 * delta(j));
	}

	return part_derivate_from_initial;
}

VectorOfMatrix LeastSquareMethod::EvalPartDerivateFromState(const MatrixXd & reference_trajectory) const
{
#ifdef CONSOLE_OUTPUT
	cout << endl << "EvalPartDerivateFromState()" << endl;
#endif

	size_t state_vec_size = reference_trajectory.cols();
	size_t num_of_observations = observations.rows();
	size_t observations_vec_size = observations.cols() - 1;

	VectorOfMatrix part_derivate_from_state(num_of_observations);

	VectorXd delta = VectorXd::Zero(state_vec_size);
	VectorXd var_state_vector;

	MatrixXd var_observations[NUM_OF_DEVIATIONS];
	short sign[NUM_OF_DEVIATIONS] = { 1, -1 };

	for (size_t deviation = 0; deviation < NUM_OF_DEVIATIONS; deviation++)
	{
		var_observations[deviation] = MatrixXd::Zero(observations_vec_size, state_vec_size);
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
			delta(k) = var_state_vector(k) * 1.0e-3;	// делаем вариации на 3-4 порядка меньше в обе стороны
			temp = var_state_vector(k);

			for (size_t deviation = 0; deviation < NUM_OF_DEVIATIONS; deviation++)
			{
				var_state_vector(k) += delta(k) * sign[deviation];

				temp_observation = p_observation_model->MakeObservation(var_state_vector, t);
				var_observations[deviation].col(k) = temp_observation;

				var_state_vector(k) = temp;
			}
		}

		// поэлементное деление
		part_derivate_from_state[i] =
			(var_observations[0] - var_observations[1]).array() * 
			(2 * delta).inverse();
	}

	return part_derivate_from_state;
}