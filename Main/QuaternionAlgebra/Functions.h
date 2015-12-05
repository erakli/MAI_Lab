#include "Types.h"

/* * * * * ��������������� ������� * * * * */

// ������� �� �������� � �������
TYPE deg2rad(const TYPE &angle){
	return angle * PI / 180;
}

// ������� ���������� � �������
TYPE pow2(const TYPE &arg){
	return arg * arg;
}

TYPE pow3(const TYPE &arg){
	return arg * arg * arg;
}