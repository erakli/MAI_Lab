#pragma once

#include "Types.h"
#include "Matrix_extended.h"

#define VEC_PART_SIZE 3
#define QUAT_SIZE 4

class CQuaternion
{
private:
	TYPE scalar; // скалярная часть кватерниона
	CVector vector; // векторная часть кватерниона

public:
	// пустой конструктор
	CQuaternion(){ scalar = 0; vector.setSize(VEC_PART_SIZE); };

	// конструктор на основе 4 значений параметров Родрига-Гамильтона
	CQuaternion(TYPE lam_0, TYPE lam_1, TYPE lam_2, TYPE lam_3);

	// конструктор на основе вектора – оси вращения и значения угла поворота
	CQuaternion(TYPE phi, const CVector &e_vec, const bool radians);

	// конструктор копии
	CQuaternion(const CQuaternion &orig) : CQuaternion() {
		*this = orig;
	};

	CQuaternion operator + (const CQuaternion &Quat);

	CQuaternion operator * (const CQuaternion &Quat);
	CQuaternion operator * (const CVector &vec);

	// Свойства для доступа к элементам кватерниона по индексу
	TYPE &operator [] (SINT i);
	const TYPE &operator [] (SINT i) const; // проверить, нужна ли здесь ссылка

	// Свойства для присвоения значений скалярной и векторной части
	CQuaternion &operator = (const TYPE scalar);
	CQuaternion &operator = (const CVector &vector);
	CQuaternion &operator = (const CQuaternion &Quat);

	// "Свойства" для доступа к значениям
	const TYPE getScalar() const;
	const CVector getVector() const;

	TYPE getNorm();  // вычисление нормы кватерниона
	TYPE getLength(); // модуль кватерниона (так же как и у вектора)
	CQuaternion getAdjoint(); // вычисление сопряженного кватерниона

	void Normalize(); // нормирование квантериона

};