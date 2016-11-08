#pragma once

#include "Types.h"
#include "LinearAlgebra.h"

struct GroundStation
{
	Eigen::Vector3d _geographic_pos;
	TYPE _vision_zone_angle;	// [рад]

	Eigen::MatrixXd observations;

	GroundStation();
	GroundStation(const Eigen::Vector3d &geographic_pos, TYPE vision_zone_angle);
};