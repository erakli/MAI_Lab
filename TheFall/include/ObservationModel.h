#pragma once

#include "Types.h"
#include "LinearAlgebra.h"

#include <random>
#include <vector>


typedef std::normal_distribution<TYPE> MyNormalDistribution;
typedef std::vector<MyNormalDistribution::param_type> DistributionParamVec;


class ObservationModel
{
public:
	ObservationModel();
	virtual ~ObservationModel();

	void Init(size_t observations_size);

	virtual Eigen::VectorXd MakeObservation(const Eigen::VectorXd & X, TYPE t) const = 0;
	virtual void SaveObservation(const Eigen::VectorXd & X, TYPE t);

	Eigen::MatrixXd GetObservations() const;
	size_t GetNumOfObservations() const;

	Eigen::MatrixXd GetRandomErrorParams() const;
	Eigen::VectorXd GetRandomErrorParams(size_t param_num) const;

protected:
	Eigen::MatrixXd observations;
	size_t num_of_observations;

	size_t observation_vec_size;

	// матрица, в которой по столбцам записаны параметры всех случайных ошибок
	Eigen::MatrixXd random_error_params;
};