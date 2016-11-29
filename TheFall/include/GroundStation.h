#pragma once

#include "ObservationModel.h"

class GroundStation : public ObservationModel
{
public:
	GroundStation();
	GroundStation(const Eigen::Vector3d &geographic_pos, TYPE vision_zone_angle);

	Eigen::VectorXd MakeObservation(const Eigen::VectorXd & X, TYPE t) const override;
	void SaveObservation(const Eigen::VectorXd & X, TYPE t, size_t time_moment = -1) override;

	Eigen::Vector3d GetGeographicPos() const;
	void SetGeographicPos(const Eigen::VectorXd & new_geographic_pos);

	TYPE GetVisionZoneAngle() const;
	void SetVisionZoneAngle(TYPE new_vision_zone_angle);

protected:
	Eigen::Vector3d _geographic_pos;
	TYPE _vision_zone_angle;	// [рад]
	TYPE start_star_time;
};
