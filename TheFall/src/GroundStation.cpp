#include "GroundStation.h"
#include <Coordinates.h>
#include <Constants.h>

using namespace Eigen;
using namespace Transform;

#define OBSERVATION_COORDINATES 2
#define DISTRIBUTION_PARAMS	2

GroundStation::GroundStation() : ObservationModel()
{
	// установки базовой модели
	observation_vec_size = OBSERVATION_COORDINATES + 1;

	// собственные установки
	_geographic_pos = Vector3d::Zero();
	_vision_zone_angle = 0.0;

	start_star_time = 0.0;
}

GroundStation::GroundStation(const Vector3d& geographic_pos, TYPE vision_zone_angle)
	: GroundStation()
{
	_geographic_pos = geographic_pos;
	_vision_zone_angle = vision_zone_angle;
}



VectorXd GroundStation::MakeObservation(const VectorXd& X, TYPE t) const
{
	Vector3d cur_geographic_pos = _geographic_pos;
	cur_geographic_pos(2) += StarTime(start_star_time, t);

	Vector2d sputnik_horiz_pos = Fix2Horiz(X.head(VEC_SIZE), cur_geographic_pos);

	return sputnik_horiz_pos;
}

void GroundStation::SaveObservation(const VectorXd& X, TYPE t, size_t time_moment)
{
	Vector2d sputnik_horiz_pos = MakeObservation(X, t);

	// проверка на попадание элевации в конус видимости НИП
	if (sputnik_horiz_pos(0) >= _vision_zone_angle)
	{
		if (is_session_initialized == false)
			InitObservationSession(time_moment);

		if (do_random)
		{
			sputnik_horiz_pos(0) += distribution(generator, random_error_params[0]);
			sputnik_horiz_pos(1) += distribution(generator, random_error_params[1]);
		}

		ObservationModel::SaveObservation(sputnik_horiz_pos, t, time_moment);
	}
	else if (is_session_initialized == true)
	{
		CloseObservationSession(time_moment);	// момент после последнего измерения
	}
}



Vector3d GroundStation::GetGeographicPos() const
{
	return _geographic_pos;
}

void GroundStation::SetGeographicPos(const VectorXd& new_geographic_pos)
{
	_geographic_pos = new_geographic_pos;
}



TYPE GroundStation::GetVisionZoneAngle() const
{
	return _vision_zone_angle;
}

void GroundStation::SetVisionZoneAngle(TYPE new_vision_zone_angle)
{
	_vision_zone_angle = new_vision_zone_angle;
}
