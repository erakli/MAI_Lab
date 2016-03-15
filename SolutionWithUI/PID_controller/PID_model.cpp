#include "PID_model.h"

/* * * * * * * * * * CPID_controller * * * * * * * * * */

CPID_controller::CPID_controller(){

	StartValues.setSize(4);
	s_size = StartValues.getSize();

	StartValues[0] = 0;		// beta
	StartValues[1] = 0;		// z1
	StartValues[2] = 0;		// z2
	StartValues[3] = 0;		// teta (используется в сумме x)

	randProcess = 1;	// входные стартовые значения
	extU = 1.7;			// управляющее воздействие

	s = 2.2;			// границы в нелинейном звене

	/* Коэффициенты в числителе и знаменателе апериодического звена (Агрегата) */
	K = 1.5;
	a[0] = 1.5;			
	a[1] = 43;
	a[2] = 50;

	//K = 1;
	T = 1;
	xi = 1;

	/* Коэффициенты ПИД-регулятора */
	k_coeff[0] = 0.63;		// gain
	k_coeff[1] = 0.0504;	// integrate
	k_coeff[2] = 1.9688;	// differentiate
}

TYPE CPID_controller::NonLinearElement(TYPE delta1) const{

	if (delta1 < -s)
		return -s;
	else if ((delta1 >= -s) && (delta1 <= s))
		return delta1;
	else
		return s;

}

CVector CPID_controller::AperiodicElement(TYPE beta, TYPE z1, TYPE z2, TYPE alpha) const{
	CVector Result(3);

	Result[0] = z1;
	Result[1] = z2;
	Result[2] = (alpha * K - z2 * a[1] - z1 * a[0] - beta) / a[2];

	return Result;
}

CVector CPID_controller::OscilElement(TYPE beta, TYPE z1, TYPE alpha) const{
	CVector Result(2);

	Result[0] = z1;
	Result[1] = (alpha * K - 2 * T * xi * z1 - beta) / (T * T);

	return Result;
}

CVector CPID_controller::getRight(CVector &X, TYPE t) const{
	CVector Y(s_size);

	/* Буквенное представление проинтегрированных Правых Частей системы ДУ */
	TYPE beta, z1, z2, teta;

	beta	= X[0];
	z1		= X[1];
	z2		= X[2];
	teta	= X[3];

	TYPE x, alpha, delta, tau;

	tau = beta - extU;
	x = k_coeff[0] * tau + teta + k_coeff[2] * z1;
	delta = randProcess - x;
	alpha = NonLinearElement(delta);

	/* Как не создавать лишнего экземпляра объекта класса вектора? */
	CVector Elem = 
		AperiodicElement(beta, z1, z2, alpha);
		//OscilElement(beta, z1, alpha);

	int size = Elem.getSize();
	for (int i = 0; i < size; i++)
		Y[i] = Elem[i];
	/*Y[0] = z1;
	Y[1] = z2;
	Y[2] = (delta * K - z2 * a[1] - z1 * a[0] - beta) / a[3];*/
	Y[3] = k_coeff[1] * tau;

	return Y;
}

bool CPID_controller::Stop_Calculation(TYPE t, TYPE Step, CVector &PrevStep, CVector &CurStep){
	
	TYPE delta = abs(PrevStep[0] - CurStep[0]);

	if ((delta < 1.0e-8) && (t != 0))
		stop_count++;
		
	if (stop_count >= stop_count_max) 
		return true;
	else 
		return false;
}

void CPID_controller::addResult(CVector &X, TYPE t){
	CModel::addResult(X, t);

	PosXY *pStruct = new PosXY;
	pStruct->posX = t;
	pStruct->posY = X[0];

	PostMessage(hWnd, WM_ADDPOINT, 0, (LPARAM)pStruct);
}