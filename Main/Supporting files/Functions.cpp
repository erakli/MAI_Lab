#include <cstring>

#include "Functions.h"

/* Numbers */

/*
// перевод из градусов в радианы
inline TYPE MyFunc::Numbers::deg2rad(const TYPE &angle){
	return angle * PI / 180;
}

// функции возведения в степень
inline TYPE MyFunc::Numbers::pow2(const TYPE &arg){
	return arg * arg;
}

inline TYPE MyFunc::Numbers::pow3(const TYPE &arg){
	return arg * arg * arg;
}

inline int MyFunc::Numbers::min(const int &first, const int &second){
	return (first > second) ? second : first;
}

inline int MyFunc::Numbers::max(const int &first, const int &second){
	return (first > second) ? first : second;
}
*/

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
