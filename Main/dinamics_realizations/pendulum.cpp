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
	
	fading = fad; // задаём значение коэффициента затухания

	Omega0 = g / leng; // квадрат циклической частоты

	Period = 2 * PI * sqrt(leng / g);

	set_t1(Period * 5); // сразу задаём граничное значение, равное 5 периодам

	StartValues[0] = ang * PI / 180;	// fi in rad
	StartValues[1] = 0;					// fi'

	stop_condition = 1.0e-15; // нужно уточнить!

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

	this->k = k; // задаём значение коэффициента упругости

	Omega = k / mass; // квадрат круговой частоты (собственная частота)
	Period = 2 * PI * sqrt(mass / k);

	set_t1(Period * 5); // сразу задаём граничное значение, равное 5 периодам

	// сила трения скольжения или вязкое трение? (по-умолчанию коэффициент = 0)
		/* 
			Для вязкого трения мы вводим не обобщённый коэффициент 
			mu, а параметр "кси" (коэффициент затухания), делая подстановку
				mu / m = 2 * ksi

			В данном случае коэффициентом будет выступать коэф. пропорциональности
			для "кси" по отношению к циклической частоте Omega^0.5
		*/
	(!bForceType) ? this->coeff = coeff : this->coeff = coeff * sqrt(Omega);
	
	this->bForceType = bForceType;

	StartValues[0] = StartPos;	// x
	StartValues[1] = 0;			// x'

	stop_condition = 1.0e-15;
}

TVector TSpringPendulum::getRight(TVector &X, TYPE t) const{

	// знак скорости (сила трения противоположно-направлена)
	const short int sign = (X[1] > 0) - (X[1] < 0);

	TVector Y(s_size);

	Y[0] = X[1];					// p  = x'
	Y[1] = -Omega * X[0];			// p' = x"

	// Вычитаем силу трения
	if (coeff != 0)
	{
		if (!bForceType)
			Y[1] -= coeff * g * sign;
		else
			Y[1] -= 2 * coeff * X[1];
	}

	return Y;
}