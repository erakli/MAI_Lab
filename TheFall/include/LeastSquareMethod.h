#pragma once

/*
	Модифицированный Метод Наименьших Квадратов, 
	используемый для определения орбит космических аппаратов
*/

#include "LinearAlgebra.h"
#include "Model.h"
#include "ObservationModel.h"

#include "DormanPrinceSolver.h"

#include <vector>

typedef std::vector<Eigen::MatrixXd> VectorOfMatrix;

class LeastSquareMethod
{
public:
	LeastSquareMethod();

	Eigen::MatrixXd Run(TYPE stop_condition);

	void SetInitialCondition(const Eigen::VectorXd & new_initial_condition);
	Eigen::VectorXd GetInitialCondition() const;

	void SetObservationsError(const Eigen::VectorXd & observations_disp_vec);
	void SetObservations(const Eigen::MatrixXd & observations_vec);

	void SetModel(Model * new_model_ptr);
	void SetObservationModel(ObservationModel * new_observation_model_ptr);

	void SetObservationSessionsVec(const ObservationSessionsVector & new_observation_sessions_vec);

private:
	Eigen::VectorXd initial_condition;
	Eigen::MatrixXd H_matrix;
	Eigen::VectorXd error_cov_vec;

	Eigen::MatrixXd observations; // первым столбцом будет время

	TYPE t_start;
	TYPE t_end;

	Model * p_model;
	ObservationModel * p_observation_model;

	ObservationSessionsVector observation_sessions_vec;

	DormanPrinceSolver solver;

private:
	Eigen::MatrixXd GenerateReferenceTrajectory();
	Eigen::MatrixXd SelectOnlyObservedTimeMoments(const Eigen::MatrixXd & reference_trajectory) const;
	Eigen::MatrixXd GenerateReferenceObservations(const Eigen::MatrixXd & reference_trajectory);
	Eigen::MatrixXd EvalObservationsDeviation(const Eigen::MatrixXd & reference_observations) const;

	Eigen::MatrixXd GetErrorCovMatrix() const;

	Eigen::MatrixXd EvalH(const Eigen::MatrixXd & reference_trajectory);

	VectorOfMatrix EvalPartDerivateFromInitial();
	VectorOfMatrix EvalPartDerivateFromState(const Eigen::MatrixXd & reference_trajectory) const;
};