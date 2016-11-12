#pragma once

/*
	���������������� ����� ���������� ���������, 
	������������ ��� ����������� ����� ����������� ���������
*/

#include "LinearAlgebra.h"
#include "Model.h"

// TODO: ���������� ������ ���������

class LeastSquareMethod
{
public:
	LeastSquareMethod();

	void SetInitialCondition(const Eigen::VectorXd & new_initial_condition);
	void SetObservationsError(const Eigen::VectorXd & observations_disp_vec);
	void SetObservations(const Eigen::MatrixXd & observations_vec);

private:
	Eigen::VectorXd initial_condition;
	Eigen::MatrixXd H_matrix;
	Eigen::MatrixXd error_cov_matrix;

	Eigen::MatrixXd observations; // ������ �������� ����� �����

	Model * p_model;

	// t1 - ����� ��������� ���������� ������� ����������
	void InitH(TYPE t1);
};