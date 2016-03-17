#pragma once

#include <cmath>
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


		// дробная часть числа
		inline TYPE frac(const TYPE &X){
			return (X >= 0) ? X - trunc(X) : -(X - trunc(X));
		}


		// функции возведения в степень
		inline TYPE pow2(const TYPE &arg){
			return arg * arg;
		};

		inline TYPE pow3(const TYPE &arg){
			return arg * arg * arg;
		};


		inline int min(const int &first, const int &second){
			return (first > second) ? second : first;
		};

		inline int max(const int &first, const int &second){
			return (first > second) ? first : second;
		};
	}

	namespace Pointers
	{
		pTYPE Resize(pTYPE pOldArray, const UINT &oldSize, const UINT &newSize);
	}
}