#include "Functions.h"
#include <cstring>

/* Numbers */

// перевод из градусов в радианы
TYPE MyFunc::Numbers::deg2rad(const TYPE &angle){
	return angle * PI / 180;
}

// функции возведения в степень
TYPE MyFunc::Numbers::pow2(const TYPE &arg){
	return arg * arg;
}

TYPE MyFunc::Numbers::pow3(const TYPE &arg){
	return arg * arg * arg;
}

UINT MyFunc::Numbers::min(const UINT &first, const UINT &second){
	return (first > second) ? second : first;
}

UINT MyFunc::Numbers::max(const UINT &first, const UINT &second){
	return (first > second) ? first : second;
}

/* Pointers */
pTYPE MyFunc::Pointers::Resize(pTYPE pOldArray, const UINT &oldSize, const UINT &newSize){
	if (oldSize == newSize)
		return pOldArray;

	pTYPE pNewArray = new TYPE[newSize];
	if (newSize > oldSize) // если новый размер больше старого - дополняем нулями
	{
		memmove(pNewArray, pOldArray, sizeof(TYPE) * oldSize);
		delete[] pOldArray;

		for (UINT i = oldSize; i < newSize; i++)
			pNewArray[i] = 0;
	}
	else // иначе обрезаем
	{
		for (UINT i = 0; i < newSize; i++)
			pNewArray[i] = pOldArray[i];
	}

	return pNewArray;
}
