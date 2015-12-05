#pragma once
#include "Model.h"

/*	������� ����� ��� ������� ���������	*/
class CPendulum : public CModel
{
protected:
	TYPE mass,
		g; // �������������� ����������
public:
	TYPE Period;

	CPendulum();
	bool Stop_Calculation(TYPE t, TYPE Step, CVector &PrevStep, CVector &CurStep);
};


/*	�������������� �������	*/
class CMathPendulum : public CPendulum
{
private:
	TYPE
		Omega0,	// ����������� �������
		fading; // ����������� ���������

public:
	CMathPendulum(TYPE leng, TYPE ang, TYPE mass, TYPE fad = 0);
	CVector getRight(CVector &X, TYPE t) const;

};


/*	��������� �������	*/
class CSpringPendulum : public CPendulum
{
private:
	TYPE
		Omega,	// ����������� � ���� ���������, ����������� � ������ (k / m)
		k,		// ����������� ���������
		coeff;	// ����������� � ���� ������, �����. � ������ (mu / m)
		
	bool bForceType; // ��� ������

public:
	CSpringPendulum(TYPE StartPos, TYPE mass, TYPE k, TYPE coeff = 0, bool bForceType = false);
	CVector getRight(CVector &X, TYPE t) const;

};