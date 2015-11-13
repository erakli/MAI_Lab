#include "pendulum.h"

/* * * * * * * * * * TPendulum * * * * * * * * * */

TPendulum::TPendulum(){
	
	g = 9.81;

};

bool TPendulum::Stop_Calculation(TYPE t, TYPE Step, TVector &PrevStep, TVector &CurStep){

	TYPE delta = abs(PrevStep[0] - CurStep[0]);

	if (delta <= stop_condition)
	{
		stop_count++;
		if (stop_count >= stop_count_max)
		{
			addResult(PrevStep, t);
			addResult(CurStep, t + Step);

			stop_flag = true;
			return stop_flag;
		}
	}
	//else if (stop_count > 0) stop_count = 0;

	return false;

}

/* * * * * * * * * * TMathPendulum * * * * * * * * * */

TMathPendulum::TMathPendulum(TYPE leng, TYPE ang, TYPE mass, TYPE fad){
	
	StartValues.setSize(2);
	s_size = StartValues.getSize();
	
	fading = fad; // ����� �������� ������������ ���������

	Omega0 = g / leng; // ������� ����������� �������

	Period = 2 * PI * sqrt(leng / g);

	set_t1(Period * 5); // ����� ����� ��������� ��������, ������ 5 ��������

	StartValues[0] = ang * PI / 180;	// fi in rad
	StartValues[1] = 0;					// fi'

	stop_condition = 1.0e-15; // ����� ��������!

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

	Omega = k / mass; // ������� �������� ������� (����������� �������)
	Period = 2 * PI * sqrt(mass / k);

	set_t1(Period * 5); // ����� ����� ��������� ��������, ������ 5 ��������

	// ���� ������ ���������� ��� ������ ������? (��-��������� ����������� = 0)
		/* 
			��� ������� ������ �� ������ �� ���������� ����������� 
			mu, � �������� "���" (����������� ���������), ����� �����������
				mu / m = 2 * ksi

			� ������ ������ ������������� ����� ��������� ����. ������������������
			��� "���" �� ��������� � ����������� ������� Omega^0.5
		*/
	(!bForceType) ? this->coeff = coeff : this->coeff = coeff * sqrt(Omega);
	
	this->bForceType = bForceType;

	StartValues[0] = StartPos;	// x
	StartValues[1] = 0;			// x'

	stop_condition = 1.0e-15;
}

TVector TSpringPendulum::getRight(TVector &X, TYPE t) const{

	// ���� �������� (���� ������ ��������������-����������)
	const short int sign = (X[1] > 0) - (X[1] < 0);

	TVector Y(s_size);

	Y[0] = X[1];					// p  = x'
	Y[1] = -Omega * X[0];			// p' = x"

	// �������� ���� ������
	if (coeff != 0)
	{
		if (!bForceType)
			Y[1] -= coeff * g * sign;
		else
			Y[1] -= 2 * coeff * X[1];
	}

	return Y;
}