#pragma once

#include "Types.h"
#include "Constants.h"

#define RAD_IN_DEG	0.01745329251994329576923690768489
#define DEG_IN_RAD	57.295779513082320876798154814105

/* * * * * Вспомогательные функции * * * * */
namespace MyFunc
{
	// перевод из градусов в радианы
	inline TYPE deg2rad(const TYPE &angle){
		return angle * RAD_IN_DEG;
	};

	// из радиан в градусы
	inline TYPE rad2deg(const TYPE &angle){
		return angle * DEG_IN_RAD;
	};
}