#pragma once

#include "Types.h"

coord GeoPos(const double Time, coord Pos);
coord Cel2Fix(const double Time, coord Pos);
coord Gelio2GeoFix(const double Time, coord Pos);