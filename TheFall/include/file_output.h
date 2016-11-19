#pragma once
#pragma warning( disable: 4996 )

#include "LinearAlgebra.h"
#include "DormanPrinceSolver.h"

#define DELAY 1000

void Dorman_to_file(const Eigen::MatrixXd &result, const DormanPrinceSolver &integrator, bool radians = true);
void to_file(const Eigen::MatrixXd &result, bool radians = true);
void to_file(const Eigen::VectorXd &result, bool radians = true);