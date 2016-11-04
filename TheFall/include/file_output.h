#pragma once
#pragma warning( disable: 4996 )

#include "LinearAlgebra.h"
#include "DormanPrinceSolver.h"

#define DELAY 1000

void Dorman_to_file(const Eigen::MatrixXd &Result, const DormanPrinceSolver &Integrator, bool radians = true);
void to_file(const Eigen::MatrixXd &Result, bool radians = true);
void to_file(const Eigen::VectorXd &Result, bool radians = true);