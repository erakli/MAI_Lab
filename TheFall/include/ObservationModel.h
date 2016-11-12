#pragma once

#include "Types.h"
#include "LinearAlgebra.h"

class ObservationModel
{
public:
	ObservationModel();
	virtual ~ObservationModel();

	void Init(size_t observations_size);

	virtual Eigen::VectorXd MakeObservation(const Eigen::VectorXd & X, TYPE t) const = 0;
	virtual void SaveObservation(const Eigen::VectorXd & X, TYPE t);

	Eigen::MatrixXd GetObservations() const;

protected:
	Eigen::MatrixXd observations;
	size_t num_of_observations;

	size_t observation_vec_size;
};