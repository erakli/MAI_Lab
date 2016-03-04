#include "PID_model.h"

/* * * * * * * * * * CPID_controller * * * * * * * * * */

CPID_controller::CPID_controller(){

	StartValues.setSize(4);
	s_size = StartValues.getSize();

	/* TO-DO: Какие стартовые значения? */
	StartValues[0] = 0;		// beta
	StartValues[1] = 0;		// z1
	StartValues[2] = 0;		// z2
	StartValues[3] = 0;		// teta (используется в сумме x)

	randProcess = 1;	// входные стартовые значения
	extU = 1.7;			// управляющее воздействие

	/* Коэффициенты в числителе и знаменателе апериодического звена (Агрегата) */
	K = 1.5;
	a[0] = 1.5;			
	a[1] = 43;
	a[2] = 50;

	/* Коэффициенты ПИД-регулятора */
	k_coeff[0] = 0.63;		// gain
	k_coeff[1] = 0.0504;	// integrate
	k_coeff[2] = 1.9688;	// differentiate
}

CVector CPID_controller::getRight(CVector &X, TYPE t) const{
	CVector Y(s_size);

	/* Буквенное представление проинтегрированных Правых Частей системы ДУ */
	double beta, z1, z2, teta;

	beta	= X[0];
	z1		= X[1];
	z2		= X[2];
	teta	= X[3];

	double x, delta, tau;

	tau = beta - extU;
	x = k_coeff[0] * tau + teta + k_coeff[2] * z1;
	delta = randProcess - x;

	Y[0] = z1;
	Y[1] = z2;
	Y[2] = (delta * K - z2 * a[1] - z1 * a[0] - beta) / a[3];
	Y[3] = k_coeff[1] * tau;

	return Y;
}

bool CPID_controller::Stop_Calculation(TYPE t, TYPE Step, CVector &PrevStep, CVector &CurStep){
	
	double delta = abs(PrevStep[0] - CurStep[0]);

	if ((delta < 1.0e-10) && (t != 0))
		stop_count++;
		
	if (stop_count >= stop_count_max) 
		return true;
	else 
		return false;
}