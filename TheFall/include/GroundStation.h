#pragma once

#include "Types.h"
#include "LinearAlgebra.h"

class GroundStation
{
public:
	GroundStation();
	GroundStation(const Eigen::Vector3d &topo_position, TYPE vision_zone_angle);

private:
	Eigen::Vector3d _topo_position;
	TYPE _vision_zone_angle;	// [рад]
};