#pragma once

#include "Integrator.h"
#include "LinearAlgebra.h"

#define SIZE 7

class DormanPrinceSolver : public Integrator
{
protected:
	Eigen::VectorXd
		c,				// ������-������� ����� �� �������
		b,				// ������-������ ����� �������
		b1;				// ������-������ ���� b
	Eigen::MatrixXd A;	// ��� ���������� ����� ���������� ������� �������
	Eigen::MatrixXd k;	// ��������������� ������������

	TYPE
//		Error,		// ������������� �������������� ������ (��������� �����������)
		Eps_Max,	// ������������ ������������� �������������� ������ 
		Eps_Global;

	Eigen::VectorXd
		x0,			// ��������� ��������
		x1, _x1;	// �������� ��� ���� (4 � 5 �������)

	int x_size;		// ����� ������� ��������� ��������

	TYPE rounding_error;

protected:
	virtual TYPE StepCorrection(TYPE Error); // ���������� ������ ���� ��������������
	virtual TYPE getError();
	TYPE RoundingError() const;

	void set_k(int size);

	Eigen::VectorXd ThickExtradition(TYPE &Teta, TYPE &Step); // ������� ������

	void set_c();
	void setA();
	void set_b();
	void set_b1();

	unsigned int iter; // ������� ���������� ��������

public:

	DormanPrinceSolver();
	void Run(Model &model) override;

	void setEps_Max(const TYPE &arg);
//	void setEps(const TYPE &arg);

	TYPE getEps_Max() const;
	TYPE getEps_Global() const;
	TYPE get_iter() const;
};
