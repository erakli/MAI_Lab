#pragma once
#include "Model.h"

/*	Базовый класс для моделей маятников	*/
class CPendulum : public CModel
{
protected:
	TYPE mass,
		g; // гравитационная постоянная
public:
	TYPE Period;

	CPendulum();
	bool Stop_Calculation(TYPE t, TYPE Step, CVector &PrevStep, CVector &CurStep);
};


/*	Математический маятник	*/
class CMathPendulum : public CPendulum
{
private:
	TYPE
		Omega0,	// циклическая частота
		fading; // коэффициент затухания

public:
	CMathPendulum(TYPE leng, TYPE ang, TYPE mass, TYPE fad = 0);
	CVector getRight(CVector &X, TYPE t) const;

};


/*	Пружинный маятник	*/
class CSpringPendulum : public CPendulum
{
private:
	TYPE
		Omega,	// коэффициент в силе упругости, соотнесённый с массой (k / m)
		k,		// коэффициент упругости
		coeff;	// коэффициент в силе трения, соотн. с массой (mu / m)
		
	bool bForceType; // тип трения

public:
	CSpringPendulum(TYPE StartPos, TYPE mass, TYPE k, TYPE coeff = 0, bool bForceType = false);
	CVector getRight(CVector &X, TYPE t) const;

};