#include "Integrator.h"
#include <algorithm>
#include <math.h>

TVector SetValues(TYPE *values){
	TVector Res(SIZE);
	for (int i = 0; i < SIZE; i++)
	{
		Res[i] = values[i];
	}
	return Res;
}

/* * * * * * * * * * TIntegrator * * * * * * * * * */
TIntegrator::TIntegrator(){
	Step = 1;
}

TYPE TIntegrator::getStep() const{
	return Step;
}
void TIntegrator::setStep(const TYPE &arg){
	Step = arg;
}

/* * * * * * * * * * TDormanPrince * * * * * * * * * */
TDormanPrince::TDormanPrince(){

	// �������������� ��� ������������
	c.setSize(SIZE);
	A.setSize(SIZE, SIZE);
	b.setSize(SIZE);
	b1.setSize(SIZE);

	// ���������
	set_c();
	set_b();
	set_b1();
	setA();

	Step = 1.0e-3;
	Eps = 1.0e-5;
	Eps_Max = 1.0e-17;
	Eps_Global = 0;

	iter = 0; // ���������� ��������

}

/*
------------- �������� �������
*/
void TDormanPrince::Run(TModel &Mod){

	Model = &Mod; // ������ ����� ������ ��� ���������� ����

	// �������������� ����� ��������� ��� ��������� �� ������
	t = Model->get_t0(); 
	x0 = Model->getStart();

	// ��������� ������ �������� �������
	x_size = x0.getSize(); 

	TYPE tout = t; // ��� ������� ������
	TYPE PrevStep; // ������ ������ � ���������� ����

	/*
		�������� ���� ����������
	*/
	while (t < Model->get_t1())
	{
		// ��������� �������� ���������� ��������
		if (iter < 50000) iter++;
		else
			break;

		set_k(x_size);

		TVector sum(x_size), sum_1(sum);

		for (int i = 0; i < x_size; i++) // �������� �� ��������� ������� �
		{
			for (int j = 0; j < SIZE; j++) // �������� ������� ��� k
			{
				sum[i] += b[j] * k[j][i];
				sum_1[i] += b1[j] * k[j][i];
			}
		}

		/*
			���������� � ������� ��������� �������
			������ ����������� ��������������.
			��� 4 � 5 �������
		*/
		x1 = x0 + sum * Step;
		_x1 = x0 + sum_1 * Step;

		PrevStep = Step; // ��������� ��� �� ����� ���� ��������
		getEps();
		StepCorrection();	

		// ���� �� �� �������� �������, �������� ��� � ������� t
		if (Eps > Eps_Max)	continue; // ------------------- �������� ������������ �����

		Eps_Global += Eps; // ������� ���������� ����������� ��� ����� ���������

		// ���� ���������� ���������� ����� ��������� ������� ��������� �������
		if (Model->Stop_Calculation(t, PrevStep, x0, x1)) break;

		/*
			������� ������. ���������� ������ � �������
			����������� ������
		*/
		TYPE Teta;
		TVector Xout; // ���� ������������ �������� � ������ ����. ������� ������
		while ((tout < t + PrevStep) && (tout < Model->get_t1()))
		{
			Teta = (tout - t) / PrevStep;
			Xout = thick_extradition(Teta, PrevStep);
			Model->addResult(Xout, tout);
			tout += Model->getInterval();
		}

		x0 = x1; // �� ����� ����� ��������� 4 ������� (�������� ��� ��������)
		t += PrevStep;
	}
}

/*
------------- ���������� k-���������
*/
void TDormanPrince::set_k(int size){

	k[0] = Model->getRight(x0, t);

	for (int s = 1; s < SIZE; s++) // ��������� �� ������� ���� (�� �������)
	{
		// �������������� ��������-������� ������� ��������������� �����.
		k[s].setSize(size);

		TVector sum(size);

		for (int i = 0; i < s; i++) // �������� �� ������� A, ��������� ��
		{
			/* 
				������ �� ������ ��������.
				sum - ����� (��, ��� � �������) ������������ ������������� ��� ������ 
				������-������� (������� ����������� ��� k)
			*/
			for (int j = 0; j < size; j++)
			{
				sum[j] += A[s][i] * k[i][j];
			}
		}

		k[s] = Model->getRight(x0 + sum * Step, t + c[s] * Step);
	}
}

/*
------------- ������� ������. 
	���������� ��� ������ ����������� �� ��������.
*/
TVector TDormanPrince::thick_extradition(TYPE &Teta, TYPE &Step){
	TYPE sqrTeta;

	sqrTeta = pow(Teta, 2); // ������� �� ����

	const int b_size = 6;

	TVector b(b_size);

	b[0] = Teta *
		(1.0 + Teta *
		(-1337.0 / 480 + Teta * (1039.0 / 360 + Teta * (-1163.0 / 1152))));

	b[1] = 0;

	b[2] = 100.0 * sqrTeta *
		(1054.0 / 9275 + Teta * (-4682.0 / 27825 + Teta * (379.0 / 5565))) / 3;

	b[3] = -5.0 * sqrTeta * (27.0 / 40 + Teta * (-9.0 / 5 + Teta * (83.0 / 96))) / 2;

	b[4] = 18225.0 * sqrTeta *
		(-3.0 / 250 + Teta * (22.0 / 375 + Teta * (-37.0 / 600))) / 848;

	b[5] = -22.0 * sqrTeta *
		(-3.0 / 10 + Teta * (29.0 / 30 + Teta * (-17.0 / 24))) / 7;


	TVector sum(x_size);
	for (int i = 0; i < x_size; i++)
	{
		for (int j = 0; j < b_size; j++)
		{
			sum[i] += b[j] * k[j][i];
		}
	}

	return x0 + sum * Step;

}

/*
------------- ��������� �������� ���� �� ������ �����������
*/
void TDormanPrince::StepCorrection(){
	TYPE min_part =
			std::min<TYPE>
			(5.0, pow(Eps / Eps_Max, 0.2) / 0.9);

	Step /= std::max<TYPE>(0.1, min_part);
}

/*
------------- ��������� ��������� �����������
*/
void TDormanPrince::getEps(){

	// ��������� � ����������� ����� ��� ������
	TVector numerator(x_size), denominator(x_size), fraction(x_size);
	
	TYPE u = RoundingError(); // ���������� ������ ����������

	for (int i = 0; i < x_size; i++)
	{
		numerator[i] = Step * (x1[i] - _x1[i]);
		denominator[i] =
			std::max<TYPE>(
			std::max<TYPE>(1.0e-5, abs(x1[i])),
			std::max<TYPE>(abs(x0[i]), 2.0 * u / Eps_Max)
			);
		fraction[i] = numerator[i] / denominator[i];
	}

	// ��������������� ����������� ����� �������
	Eps = fraction.getLength() / sqrt((double)x_size);	
	
}

TYPE TDormanPrince::RoundingError(){
	TYPE v(1), u;

	while (1 + v > 1)
	{
		u = v;
		v /= 2;
	}

	return u;
}

// -------------- ��������������� ������������
void TDormanPrince::set_c(){
	TYPE prep[SIZE] = { 0, 0.2, 0.3, 0.8, 8.0 / 9, 1, 1 };
	c = SetValues(prep);
}

void TDormanPrince::setA(){
	TYPE prep[SIZE][SIZE] =
	{
		{},
		{ 0.2 },
		{ 3.0 / 40, 9.0 / 40 },
		{ 44.0 / 45, -56.0 / 15, 32.0 / 9 },
		{ 19372.0 / 6561, -25360.0 / 2187, 64448.0 / 6561, -212.0 / 729 },
		{ 9017.0 / 3168, -355.0 / 33, 46732.0 / 5247, 49.0 / 176, -5103.0 / 18656 },
		{ 35.0 / 384, 0, 500.0 / 1113, 125.0 / 192, -2187.0 / 6784, 11.0 / 84, 0 }
	};

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < i; j++)
		{
			A[i][j] = prep[i][j];
		}
	}
}

void TDormanPrince::set_b(){
	TYPE prep[SIZE] = 
	{ 35.0 / 384, 0, 500.0 / 1113, 125.0 / 192, -2187.0 / 6784, 11.0 / 84, 0 };
	b = SetValues(prep);
}

void TDormanPrince::set_b1(){
	TYPE prep[SIZE] =
	{ 5179.0 / 57600, 0, 7571.0 / 16695, 393.0 / 640, -92097.0 / 339200, 187.0 / 2100, 1.0 / 40 };
	b1 = SetValues(prep);
}


// ------------ ������������
void TDormanPrince::setEps_Max(const TYPE &arg){
	Eps_Max = arg;
}

void TDormanPrince::setEps(const TYPE &arg){
	Eps = arg;
}

TYPE TDormanPrince::getEps_Max() const{
	return Eps_Max;
}

TYPE TDormanPrince::get_iter() const{
	return iter;
}

TYPE TDormanPrince::getEps_Global() const{
	return Eps_Global;
}