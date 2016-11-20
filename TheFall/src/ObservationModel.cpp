#include "ObservationModel.h"

#include <chrono>

using namespace std;
using namespace Eigen;



ObservationModel::ObservationModel()
{
	num_of_observations = 0;
	observation_vec_size = 0;

	do_random = false;

	// construct a trivial random generator engine from a time - based seed :
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();

	// генератор с гауссовским нормальным распределением СВ
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

void ObservationModel::SaveObservation(const VectorXd& X, TYPE t)
{
	VectorXd new_line(X.size() + 1);	// +1 для времени
	new_line << t, X;
	observations.row(num_of_observations) = new_line;
	num_of_observations++;
}



MatrixXd ObservationModel::GetObservations() const
{
	MatrixXd trimmed_matrix = observations;
	trimmed_matrix.conservativeResize(num_of_observations, NoChange);
	return trimmed_matrix;
}



size_t ObservationModel::GetNumOfObservations() const
{
	return num_of_observations;
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
