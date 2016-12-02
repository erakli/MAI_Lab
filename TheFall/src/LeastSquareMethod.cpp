#include "LeastSquareMethod.h"

#include <Constants.h>

#include <vector>

using namespace Eigen;
using namespace std;




#define MAX_ITER	25

#define NUM_OF_DEVIATIONS	2
#define CONSOLE_OUTPUT
//#define TEST

#define DELTA_COEFF		1.0e-4

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

//	solver.SetEpsMax(1.0e-13);
	solver.SetCorrelationInterval(1.0);	// TODO: вынести на внешнюю установку
}



MatrixXd LeastSquareMethod::Run(const Eigen::VectorXd & stop_condition)
{
	MatrixXd temp_reference_trajectory;
	MatrixXd reference_trajectory;

	VectorXd reference_observations;
	VectorXd observations_deviation;

	MatrixXd matrix_H;
	MatrixXd D_eta;
	MatrixXd H_D_eta;
	MatrixXd K;

	VectorXd delta_X;

	size_t iter = 0;

	// TODO: будем записывать сюда все итерации
	MatrixXd log_matrix = MatrixXd::Zero(MAX_ITER, initial_condition.size());

	// не будет меняться между итерациями
	D_eta = GetErrorCovMatrix();

	bool reason_for_break;

#ifdef CONSOLE_OUTPUT
	cout << endl << endl;
#endif

	do // while (delta_X.norm() >= stop_condition && iter < max_iter);
	{
		reason_for_break = true;

		temp_reference_trajectory = GenerateReferenceTrajectory();
		reference_trajectory = SelectOnlyObservedTimeMoments(temp_reference_trajectory);
		reference_observations = GenerateReferenceObservations(reference_trajectory);
		observations_deviation = EvalObservationsDeviation(reference_observations);

#ifdef TEST
		//cout << endl << "Saving observations_deviation vector" << endl;
		//to_file(observations_deviation);

		//system("pause");
#endif

		matrix_H = EvalH(reference_trajectory);

		H_D_eta = matrix_H.transpose() * D_eta;
		K = (H_D_eta * matrix_H).inverse();

		delta_X = K * H_D_eta * observations_deviation;

		initial_condition += delta_X;
		log_matrix.row(iter) = delta_X;

#ifdef CONSOLE_OUTPUT
		cout << endl << "iter = " << iter << endl;
		cout << "	delta_X: " << delta_X.transpose() << endl;
		cout << "	initial_condition: " << initial_condition.transpose() << endl;
		cout << endl;

//		to_file(matrix_H);

		//system("pause");
#endif

		for (size_t j = 0; j < delta_X.size(); j++)
		{
			reason_for_break &= abs(delta_X(j)) <= stop_condition(j);
			if (reason_for_break == false)
				break;
		}

		//if (delta_X.norm() < stop_condition)
		//	reason_for_break = true;

		iter++;
	} while (reason_for_break == false && iter < MAX_ITER);

//	log_matrix.conservativeResize(iter, NoChange);

	return log_matrix.topRows(iter);
}



void LeastSquareMethod::SetInitialCondition(const VectorXd& new_initial_condition)
{
	initial_condition = new_initial_condition;
}

VectorXd LeastSquareMethod::GetInitialCondition() const
{
	return initial_condition;
}



void LeastSquareMethod::SetDelta(const Eigen::VectorXd& new_delta_vec)
{
	delta_vec = new_delta_vec;
}



void LeastSquareMethod::SetObservationsError(const VectorXd& observations_disp_vec)
{
	error_cov_vec = observations_disp_vec; // .asDiagonal().inverse();
}

void LeastSquareMethod::SetObservations(const MatrixXd& observations_vec)
{
#ifdef CONSOLE_OUTPUT
//	cout << "observations_vec: " << endl << observations_vec << endl;
#endif

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

#ifdef CONSOLE_OUTPUT
	cout << "	last filled selected_time_moments row - " << j - 1 << endl;
#endif

	return selected_time_moments;
}

VectorXd LeastSquareMethod::GenerateReferenceObservations(const MatrixXd& reference_trajectory)
{
#ifdef CONSOLE_OUTPUT
	cout << endl << "GenerateReferenceObservations()" << endl;
	cout << "	reference_observations = " << (observations.cols() - 1) * observations.rows() << endl;
	cout << "	reference_trajectory.row(0) = " << reference_trajectory.row(0) << endl;

#endif

	size_t observation_vec_size = observations.cols() - 1;
	size_t num_of_observations = observations.rows();

	VectorXd row;
	Vector3d cur_pos;
	TYPE t;

	VectorXd reference_observations(num_of_observations * observation_vec_size);

	for (size_t i = 0; i < num_of_observations; i++)
	{
		row = reference_trajectory.row(i);
		cur_pos = row.head(VEC_SIZE);
		t = observations(i, 0);

		// без случайностей
		reference_observations.segment(i * observation_vec_size, observation_vec_size) =
			p_observation_model->MakeObservation(cur_pos, t);
	}

	return reference_observations;
}

VectorXd LeastSquareMethod::EvalObservationsDeviation(const VectorXd& reference_observations) const
{
#ifdef CONSOLE_OUTPUT
	cout << endl << "EvalObservationsDeviation()" << endl;
#endif

	// TODO: надо осуществить вычитание из соответствующих моментов времени
	size_t observation_vec_size = observations.cols() - 1;

	// отсекаем время и меняем порядок представления данных в матрице на
	// построчный (с постолбцового)
	Matrix<double, Dynamic, Dynamic, RowMajor> observations_matrix = 
		observations.rightCols(observation_vec_size);

	// проецируем построчно матрицу измерений в вектор
	Map<VectorXd> observations_vec(observations_matrix.data(), observations_matrix.size());

	return observations_vec - reference_observations;
}



MatrixXd LeastSquareMethod::GetErrorCovMatrix() const
{
#ifdef CONSOLE_OUTPUT
	cout << endl << "GetErrorCovMatrix()" << endl;
#endif

	size_t observation_vec_size = observations.cols() - 1;
	size_t num_of_observations = observations.rows();

	// превратим каждый компонент в обратный
	VectorXd errors_disp_inversed = error_cov_vec.array().inverse();

	// заполним каждый столбец матрицы компонентами полученного вектора
	MatrixXd temp_matrix = MatrixXd::Zero(observation_vec_size, num_of_observations);
	temp_matrix.colwise() += errors_disp_inversed;

	// по столбцам спроецируем эту матрицу в вектор
	Map<VectorXd> main_diag(temp_matrix.data(), temp_matrix.size());

	// превратим полученный вектор в диагональную матрицу
	MatrixXd result = main_diag.asDiagonal();

	return result;
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

#ifdef CONSOLE_OUTPUT
	cout << endl << endl;
#endif

	for (size_t i = 0; i < num_of_observations; i++)
	{
#ifdef CONSOLE_OUTPUT
		//cout << endl << "i = " << i << endl;
#endif

		for (size_t j = 0; j < initial_condition_size; j++)
		{
#ifdef CONSOLE_OUTPUT
			//cout << endl << "j = " << j << endl;
#endif

			temp_sum = ArrayXd::Zero(observations_vec_size);
			for (size_t k = 0; k < state_vector_size; k++)
			{
				// вектор-столбец частн. производной от измеряемых параметров
				// поэлементно умножается на частн. произв. от компонент вектора
				// состояния по компонентам вектора НУ
				temp_sum += from_state[i].col(k).array() * from_initial[j](i, k);

#ifdef CONSOLE_OUTPUT
				//cout << endl << "k = " << k << endl;
				//cout << "from_state[i].col(k).array()" << endl << from_state[i].col(k).array() << endl;
				//cout << "from_initial[j](i, k) = " << from_initial[j](i, k) << endl;
				//cout << "from_state[i].col(k).array() * from_initial[j](i, k):" << endl << from_state[i].col(k).array() * from_initial[j](i, k) << endl;
				//cout << "temp_sum:" << endl << temp_sum << endl;
				//cout << endl;

				//system("pause");
#endif

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
		//cout << endl << "ballistic_derivates:" << endl;
		//cout << ballistic_derivates << endl;

		//cout << endl << "matrix_H.block:" << endl;
		//cout << matrix_H.topRows(10) << endl;
		//cout << endl;

		//system("pause");
#endif
	}

	return matrix_H;
}



// построение фундаментальной матрицы H
VectorOfMatrix LeastSquareMethod::EvalPartDerivateFromInitial()
{
#ifdef CONSOLE_OUTPUT
	cout << endl << "EvalPartDerivateFromInitial()" << endl;
#endif

	size_t initial_condition_size = initial_condition.size();

	VectorOfMatrix part_derivate_from_initial(initial_condition_size);

//	VectorXd delta = VectorXd::Zero(initial_condition_size);
	VectorXd var_initial_condition = initial_condition;

	MatrixXd var_traectories[NUM_OF_DEVIATIONS];
	short sign[NUM_OF_DEVIATIONS] = { 1, -1 };

	MatrixXd temp_trajectory;
	TYPE temp;

	for (size_t j = 0; j < initial_condition_size; j++)
	{
#ifdef TEST
#ifdef CONSOLE_OUTPUT
		cout << endl << endl << " * * var_initial_condition = " << j << " * * " << endl;
#endif
#endif

//		delta(j) = abs(initial_condition(j)) * DELTA_COEFF;	// делаем вариации на 3-4 порядка меньше в обе стороны

#ifdef TEST
#ifdef CONSOLE_OUTPUT
		cout << endl << "	delta: " << delta.transpose() << endl;
#endif
#endif

		temp = var_initial_condition(j);

		// делаем вариации НУ 
		for (size_t deviation = 0; deviation < NUM_OF_DEVIATIONS; deviation++)
		{
			p_model->ClearResult();
			
//			var_initial_condition(j) += delta(j) * sign[deviation];
			var_initial_condition(j) += delta_vec(j) * sign[deviation];
			p_model->SetStart(var_initial_condition);
			solver.Run(*p_model);
			temp_trajectory = p_model->GetResult(false); // без времени
			var_traectories[deviation] = SelectOnlyObservedTimeMoments(temp_trajectory);

#ifdef TEST
#ifdef CONSOLE_OUTPUT
			cout << endl << "	var_initial_condition: " << endl;
			cout << var_initial_condition.transpose() << endl;

//			system("pause");

//			cout << endl << "to_file(var_traectories[" << sign[deviation] << "])" << endl;
#endif
//			to_file(var_traectories[deviation]);
#endif

			var_initial_condition(j) = temp;
		}

		// каждый из var_traectories состоит только из компонент вектора состояния, время отсутствует
		part_derivate_from_initial[j] =
			(var_traectories[0] - var_traectories[1]) / (2 * delta_vec(j));

#ifdef CONSOLE_OUTPUT
		//to_file(part_derivate_from_initial[j]);
#endif
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

//	VectorXd delta = VectorXd::Zero(state_vec_size);
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

#ifdef TEST
#ifdef CONSOLE_OUTPUT
		cout << endl << endl << " * * var_state_vector = " << i << " * * " << endl;
#endif
#endif

		for (size_t k = 0; k < state_vec_size; k++)
		{
//			delta(k) = abs(var_state_vector(k)) * DELTA_COEFF;	// делаем вариации на 3-4 порядка меньше в обе стороны
			temp = var_state_vector(k);

			for (size_t deviation = 0; deviation < NUM_OF_DEVIATIONS; deviation++)
			{
				var_state_vector(k) += delta_vec(k) * sign[deviation];

				temp_observation = p_observation_model->MakeObservation(var_state_vector, t);
				var_observations[deviation].col(k) = temp_observation;

				var_state_vector(k) = temp;
			}
		}

		// поэлементное деление
		part_derivate_from_state[i] =
			(var_observations[0] - var_observations[1]).array().rowwise() *
			(2 * delta_vec).array().inverse().transpose();

#ifdef TEST
#ifdef CONSOLE_OUTPUT
		cout << "	t = " << t << endl;
		cout << endl << "	delta: " << endl;
		cout << delta.transpose() << endl;

		//cout << endl << "to_file()" << endl;
#endif
		//to_file(var_observations[0]);
		//to_file(var_observations[1]);
		//to_file(delta);
		//to_file(part_derivate_from_state[i]);

		//system("pause");
#endif
	}

	return part_derivate_from_state;
}