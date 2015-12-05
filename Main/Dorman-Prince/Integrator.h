#pragma once
#include "Model.h"
#include "Types.h"

#define SIZE 7

class TIntegrator{
protected:
	TYPE Step, t;
	CModel *Model;
public:
	TIntegrator();

	TYPE getStep() const;
	void setStep(const TYPE &arg);

	virtual void Run(CModel &Mod) = 0; // pure virtual function
};

class CDormanPrince : public TIntegrator{
private:
	CVector
		c,  // ������-������� ����� �� �������
		b,  // ������-������ ����� �������
		b1;  // ������-������ ���� b
	CMatrix A;  // ��� ���������� ����� ���������� ������� �������
	CVector k[SIZE];  // ��������������� ������������

	TYPE
		Eps, // ������������� �������������� ������ (��������� �����������)
		Eps_Max, // ������������ ������������� �������������� ������ 
		Eps_Global;

	CVector 
		x0, // ��������� ��������
		x1, _x1; // �������� ��� ���� (4 � 5 �������)

	int x_size; // ����� ������� ��������� ��������

	void StepCorrection(); // ���������� ������ ���� ��������������
	void getEps(); 
	TYPE RoundingError();

	void set_k(int size);

	CVector thick_extradition(TYPE &Teta, TYPE &Step); // ������� ������

	void set_c();
	void setA();
	void set_b();
	void set_b1();

	unsigned int iter; // ������� ���������� ��������

public:

	CDormanPrince();
	void Run(CModel &Mod);

	void setEps_Max(const TYPE &arg);
	void setEps(const TYPE &arg);

	TYPE getEps_Max() const;
	TYPE getEps_Global() const;
	TYPE get_iter() const;
};