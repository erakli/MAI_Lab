#include "ObservationModel.h"

using namespace Eigen;

ObservationModel::ObservationModel()
{
	num_of_observations = 0;
	observation_vec_size = 0;
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
