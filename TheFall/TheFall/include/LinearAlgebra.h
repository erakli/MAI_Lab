#pragma once

#include <Eigen/Dense>

typedef Eigen::Matrix<double, 6, 1, 0, 6, 1>	Vector6d;
typedef Eigen::Matrix<double, 1, 6, 0, 1, 6>	RowVector6d;

#include <list>

typedef std::list<Eigen::VectorXd> VectorList;
