#pragma once

#include "Types.h"

/* * * * * Вспомогательные функции * * * * */
namespace MyFunc
{
	namespace Numbers
	{
		// перевод из градусов в радианы
		inline TYPE deg2rad(const TYPE &angle){
			return angle * PI / 180;
		};

	}

	namespace Pointers
	{
		pTYPE Resize(pTYPE pOldArray, const UINT &oldSize, const UINT &newSize);
	}
}