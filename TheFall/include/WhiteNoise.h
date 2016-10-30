#pragma once

#include "Types.h"
#include "LinearAlgebra.h"

Eigen::VectorXd Get_WhiteNoise(TYPE omega, TYPE t0, TYPE t1, TYPE &dt);