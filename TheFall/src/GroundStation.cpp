#include "GroundStation.h"

using namespace Eigen;

GroundStation::GroundStation()
{
	_topo_position = Vector3d::Zero();
	_vision_zone_angle = 0;
}

GroundStation::GroundStation(const Vector3d& topo_position, TYPE vision_zone_angle)
{
	_topo_position = topo_position;
	_vision_zone_angle = vision_zone_angle;
}
