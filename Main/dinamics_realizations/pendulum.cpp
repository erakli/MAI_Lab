#include "pendulum.h"

/* * * * * * * * * * TPendulum * * * * * * * * * */

TPendulum::TPendulum(){
	
	g = 9.81;

};


/* * * * * * * * * * TMathPendulum * * * * * * * * * */

TMathPendulum::TMathPendulum(TYPE leng, TYPE ang, TYPE mass, TYPE fad){
	
	StartValues.setSize(2);
	s_size = StartValues.getSize();
	
	fading = fad; // ����� �������� ������������ ���������

	Omega0 = g / leng; // ������� ����������� �������

	Period = 2 * PI * sqrt(leng / g);

	StartValues[0] = ang * PI / 180;	// fi in rad
	StartValues[1] = 0;					// fi'
}

TVector TMathPendulum::getRight(TVector &X, TYPE t) const{
	TVector Y(s_size);

	Y[0] = X[1];									// p = fi'
	Y[1] = -Omega0 * sin(X[0]) - 2 * fading * X[1];	// p' = fi"

	return Y;
}



/* * * * * * * * * * TSpringPendulum * * * * * * * * * */

TSpringPendulum::TSpringPendulum(TYPE StartPos, TYPE mass, TYPE k,
	TYPE coeff, bool bForceType){

	StartValues.setSize(2);
	s_size = StartValues.getSize();

	this->k = k; // ����� �������� ������������ ���������

	Omega = k / mass;
	Period = 2 * PI * sqrt(mass / k);

	// ���� ������ ���������� ��� ������ ������? (��-��������� ����������� = 0)
	(bForceType) ? this->coeff = coeff : this->coeff = coeff / mass;
	
	this->bForceType = bForceType;

	StartValues[0] = StartPos;	// x
	StartValues[1] = 0;			// x'
}

TVector TSpringPendulum::getRight(TVector &X, TYPE t) const{

	// ���� �������� (���� ������ ��������������-����������)
	const short int sign = (X[1] > 0) - (X[1] < 0);

	TVector Y(s_size);

	Y[0] = X[1];					// p  = x'
	Y[1] = -Omega * X[0];			// p' = x"

	// �������� ���� ������
	if ((!bForceType) && (coeff != 0))
		Y[1] -= coeff * g * sign;
	else
		Y[1] -= coeff * X[1];

	return Y;
}