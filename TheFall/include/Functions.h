#pragma once

#include "Types.h"
#include "Constants.h"

/* * * * * Вспомогательные функции * * * * */
namespace MyFunc
{
	// перевод из градусов в радианы
	inline TYPE deg2rad(const TYPE &angle){
		return angle * PI / 180;
	};
}