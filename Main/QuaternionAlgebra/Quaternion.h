#pragma once

#include "Types.h"
#include "Matrix_extended.h"

#define VEC_PART_SIZE 3
#define QUAT_SIZE 4

class CQuaternion
{
private:
	TYPE scalar; // ��������� ����� �����������
	CVector vector; // ��������� ����� �����������

public:
	// ������ �����������
	CQuaternion(){ scalar = 0; vector.setSize(VEC_PART_SIZE); };

	// ����������� �� ������ 4 �������� ���������� �������-����������
	CQuaternion(TYPE lam_0, TYPE lam_1, TYPE lam_2, TYPE lam_3);

	// ����������� �� ������ ������� � ��� �������� � �������� ���� ��������
	CQuaternion(TYPE phi, const CVector &e_vec, const bool radians);

	// ����������� �����
	CQuaternion(const CQuaternion &orig) : CQuaternion() {
		*this = orig;
	};

	CQuaternion operator + (const CQuaternion &Quat);

	CQuaternion operator * (const CQuaternion &Quat);
	CQuaternion operator * (const CVector &vec);

	// �������� ��� ������� � ��������� ����������� �� �������
	TYPE &operator [] (SINT i);
	const TYPE &operator [] (SINT i) const; // ���������, ����� �� ����� ������

	// �������� ��� ���������� �������� ��������� � ��������� �����
	CQuaternion &operator = (const TYPE scalar);
	CQuaternion &operator = (const CVector &vector);
	CQuaternion &operator = (const CQuaternion &Quat);

	// "��������" ��� ������� � ���������
	const TYPE getScalar() const;
	const CVector getVector() const;

	TYPE getNorm();  // ���������� ����� �����������
	TYPE getLength(); // ������ ����������� (��� �� ��� � � �������)
	CQuaternion getAdjoint(); // ���������� ������������ �����������

	void Normalize(); // ������������ �����������

};