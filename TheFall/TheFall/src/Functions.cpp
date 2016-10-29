#include <cstring>

#include "Functions.h"

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
