#pragma once

/*
	Модифицированный Метод Наименьших Квадратов, 
	используемый для определения орбит космических аппаратов
*/

#include "LinearAlgebra.h"
#include "Model.h"
#include "ObservationModel.h"

// TODO: подключить модель измерений

class LeastSquareMethod
{
public:
	LeastSquareMethod();

	void SetInitialCondition(const Eigen::VectorXd & new_initial_condition);
	void SetObservationsError(const Eigen::VectorXd & observations_disp_vec);
	void SetObservations(const Eigen::MatrixXd & observations_vec);

	void SetModel(Model * new_model_ptr);
	void SetObservationModel(ObservationModel * new_observation_model_ptr);

private:
	Eigen::VectorXd initial_condition;
	Eigen::MatrixXd H_matrix;
	Eigen::MatrixXd error_cov_matrix;

	Eigen::MatrixXd observations; // первым столбцом будет время

	Model * p_model;
	ObservationModel * p_observation_model;

	// t1 - время окончания построения опорной траектории
	void InitH(TYPE t1);
};