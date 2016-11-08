#include "GroundStation.h"

using namespace Eigen;

GroundStation::GroundStation()
{
	_geographic_pos = Vector3d::Zero();
	_vision_zone_angle = 0;
}

GroundStation::GroundStation(const Vector3d& geographic_pos, TYPE vision_zone_angle)
{
	_geographic_pos = geographic_pos;
	_vision_zone_angle = vision_zone_angle;
}
