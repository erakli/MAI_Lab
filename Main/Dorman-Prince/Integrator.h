#pragma once
#include "Model.h"
#include "Types.h"

#define SIZE 7

class TIntegrator{
protected:
	TYPE Step, t;
	TModel *Model;
public:
	TIntegrator();

	TYPE getStep() const;
	void setStep(const TYPE &arg);

	virtual void Run(TModel &Mod) = 0; // pure virtual function
};

class TDormanPrince : public TIntegrator{
private:
	TVector
		c,  // ������-������� ����� �� �������
		b,  // ������-������ ����� �������
		b1;  // ������-������ ���� b
	TMatrix A;  // ��� ���������� ����� ���������� ������� �������
	TVector k[SIZE];  // ��������������� ������������

	TYPE
		Eps, // ������������� �������������� ������ (��������� �����������)
		Eps_Max, // ������������ ������������� �������������� ������ 
		Eps_Global;

	TVector 
		x0, // ��������� ��������
		x1, _x1; // �������� ��� ���� (4 � 5 �������)

	int x_size; // ����� ������� ��������� ��������

	void StepCorrection(); // ���������� ������ ���� ��������������
	void getEps(); 
	TYPE RoundingError();

	void set_k(int size);

	TVector thick_extradition(TYPE &Teta, TYPE &Step); // ������� ������

	void set_c();
	void setA();
	void set_b();
	void set_b1();

	unsigned int iter; // ������� ���������� ��������

public:

	TDormanPrince();
	void Run(TModel &Mod);

	void setEps_Max(const TYPE &arg);
	void setEps(const TYPE &arg);

	TYPE getEps_Max() const;
	TYPE getEps_Global() const;
	TYPE get_iter() const;
};