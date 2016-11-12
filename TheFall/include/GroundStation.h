#pragma once

#include "ObservationModel.h"

class GroundStation : public ObservationModel
{
public:
	GroundStation();
	GroundStation(const Eigen::Vector3d &geographic_pos, TYPE vision_zone_angle);

	Eigen::VectorXd MakeObservation(const Eigen::VectorXd & X, TYPE t) const override;
	void SaveObservation(const Eigen::VectorXd & X, TYPE t) override;

	Eigen::Vector3d _geographic_pos;
	TYPE _vision_zone_angle;	// [рад]

private:
	TYPE start_star_time;
};