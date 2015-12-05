#include "Types.h"

/* * * * * Вспомогательные функции * * * * */

// перевод из градусов в радианы
TYPE deg2rad(const TYPE &angle){
	return angle * PI / 180;
}

// функции возведения в степень
TYPE pow2(const TYPE &arg){
	return arg * arg;
}

TYPE pow3(const TYPE &arg){
	return arg * arg * arg;
}