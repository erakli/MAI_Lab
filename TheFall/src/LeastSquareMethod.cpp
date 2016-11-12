#include "LeastSquareMethod.h"

#include "DormanPrinceSolver.h"

using namespace Eigen;

LeastSquareMethod::LeastSquareMethod()
{
	p_model = nullptr;
}



void LeastSquareMethod::SetInitialCondition(const VectorXd& new_initial_condition)
{
	initial_condition = new_initial_condition;
}

void LeastSquareMethod::SetObservationsError(const VectorXd& observations_disp_vec)
{
	error_cov_matrix = observations_disp_vec.asDiagonal().inverse();
}

void LeastSquareMethod::SetObservations(const MatrixXd& observations_vec)
{
	observations = observations_vec;
}



// t1 - время окончания построения опорной траектории
void LeastSquareMethod::InitH(TYPE t1)
{

}
