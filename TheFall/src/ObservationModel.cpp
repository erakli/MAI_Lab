#include "ObservationModel.h"

#include <chrono>

using namespace std;
using namespace Eigen;


ObservationSession::ObservationSession()
	:start_moment(0), end_moment(0)
{
}

size_t ObservationSession::GetDuration() const
{
	return end_moment - start_moment;
}



#define DEFAULT_OBSERVATION_SESSIONS_NUM	50



ObservationModel::ObservationModel()
{
	num_of_observations = 0;
	observation_vec_size = 0;

	observation_sessions_vec.reserve(DEFAULT_OBSERVATION_SESSIONS_NUM);

	is_session_initialized = false;

	do_random = false;

	// construct a trivial random generator engine from a time - based seed :
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();

	// генератор с гауссовским нормальным распределением —¬
	generator.seed(seed);
}

ObservationModel::~ObservationModel()
{

}



void ObservationModel::Init(size_t observations_size)
{
	num_of_observations = 0;
	observations = MatrixXd::Zero(observations_size, observation_vec_size);
}

void ObservationModel::SaveObservation(const VectorXd& X, TYPE t, size_t time_moment)
{
	VectorXd new_line(X.size() + 1);	// +1 дл€ времени
	new_line << t, X;
	observations.row(num_of_observations) = new_line;
	num_of_observations++;
}



MatrixXd ObservationModel::GetObservations(bool with_time) const
{
	MatrixXd trimmed_matrix = observations;
	trimmed_matrix.conservativeResize(num_of_observations, NoChange);

	if (with_time)
		return trimmed_matrix;

	return trimmed_matrix.rightCols(trimmed_matrix.cols() - 1);
}



size_t ObservationModel::GetNumOfObservations() const
{
	return num_of_observations;
}



ObservationSessionsVector ObservationModel::GetObservationSessionsVector() const
{
	return observation_sessions_vec;
}



void ObservationModel::SetDoRandom(bool should_we_do_random)
{
	do_random = should_we_do_random;
}



DistributionParamVec ObservationModel::GetRandomErrorParams() const
{
	return random_error_params;
}

MyNormalDistribution::param_type ObservationModel::GetRandomErrorParams(size_t param_num) const
{
	return random_error_params[param_num];
}

void ObservationModel::SetRandomErrorParams(const DistributionParamVec & new_random_error_params)
{
	random_error_params = new_random_error_params;
}



void ObservationModel::InitObservationSession(size_t start_moment)
{	
	current_session.start_moment = start_moment;
	is_session_initialized = true;
}

void ObservationModel::CloseObservationSession(size_t end_moment)
{
	current_session.end_moment = end_moment;
	is_session_initialized = false;

	// сохран€ем продолжительность сеанса
	observation_sessions_vec.push_back(current_session);
	current_session = ObservationSession();
}
