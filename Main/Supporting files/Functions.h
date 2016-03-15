#pragma once

#include "Types.h"

/* * * * * Вспомогательные функции * * * * */
namespace MyFunc
{
	namespace Numbers
	{
		// перевод из градусов в радианы
		TYPE deg2rad(const TYPE &angle);

		// функции возведения в степень
		TYPE pow2(const TYPE &arg);
		TYPE pow3(const TYPE &arg);

		UINT min(const UINT &first, const UINT &second);
		UINT max(const UINT &first, const UINT &second);
	}

	namespace Pointers
	{
		pTYPE Resize(pTYPE pOldArray, const UINT &oldSize, const UINT &newSize);
	}
}