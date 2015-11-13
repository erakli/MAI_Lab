#pragma once
#include "Model.h"

/*	Базовый класс для моделей маятников	*/
class TPendulum : public TModel
{
protected:
	TYPE mass,
		g; // гравитационная постоянная
public:
	TYPE Period;

	TPendulum();
	bool Stop_Calculation(TYPE t, TYPE Step, TVector &PrevStep, TVector &CurStep);
};


/*	Математический маятник	*/
class TMathPendulum : public TPendulum
{
private:
	TYPE
		Omega0,	// циклическая частота
		fading; // коэффициент затухания

public:
	TMathPendulum(TYPE leng, TYPE ang, TYPE mass, TYPE fad = 0);
	TVector getRight(TVector &X, TYPE t) const;

};


/*	Пружинный маятник	*/
class TSpringPendulum : public TPendulum
{
private:
	TYPE
		Omega,	// коэффициент в силе упругости, соотнесённый с массой (k / m)
		k,		// коэффициент упругости
		coeff;	// коэффициент в силе трения, соотн. с массой (mu / m)
		
	bool bForceType; // тип трения

public:
	TSpringPendulum(TYPE StartPos, TYPE mass, TYPE k, TYPE coeff = 0, bool bForceType = false);
	TVector getRight(TVector &X, TYPE t) const;

};