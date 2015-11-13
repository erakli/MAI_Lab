#pragma once
#include "Model.h"

/*	������� ����� ��� ������� ���������	*/
class TPendulum : public TModel
{
protected:
	TYPE mass,
		g; // �������������� ����������
public:
	TYPE Period;

	TPendulum();
	bool Stop_Calculation(TYPE t, TYPE Step, TVector &PrevStep, TVector &CurStep);
};


/*	�������������� �������	*/
class TMathPendulum : public TPendulum
{
private:
	TYPE
		Omega0,	// ����������� �������
		fading; // ����������� ���������

public:
	TMathPendulum(TYPE leng, TYPE ang, TYPE mass, TYPE fad = 0);
	TVector getRight(TVector &X, TYPE t) const;

};


/*	��������� �������	*/
class TSpringPendulum : public TPendulum
{
private:
	TYPE
		Omega,	// ����������� � ���� ���������, ����������� � ������ (k / m)
		k,		// ����������� ���������
		coeff;	// ����������� � ���� ������, �����. � ������ (mu / m)
		
	bool bForceType; // ��� ������

public:
	TSpringPendulum(TYPE StartPos, TYPE mass, TYPE k, TYPE coeff = 0, bool bForceType = false);
	TVector getRight(TVector &X, TYPE t) const;

};