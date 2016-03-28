#pragma once

#include "Matrix_classes.h"
#include "Time.h"

struct Coordinates
{
	TYPE fi_deg, fi_min, lambda_deg, lambda_min;
};



CMatrix GenerateShadow(
	const MyTime::Date &date, const Coordinates &coord, 
	const SINT timeZone, const TYPE height);

CVector GetLightTime(
	const Coordinates &coord, const SINT timeZone, 
	const bool WorkTime, const bool Switch);