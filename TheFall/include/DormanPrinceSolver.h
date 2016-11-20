#pragma once

#include "Integrator.h"
#include "LinearAlgebra.h"

#define SIZE 7

class DormanPrinceSolver : public Integrator
{
protected:
	Eigen::VectorXd
		m_c,				// ������-������� ����� �� �������
		m_b,				// ������-������ ����� �������
		m_b1;				// ������-������ ���� m_b
	Eigen::MatrixXd m_A;	// ��� ���������� ����� ���������� ������� �������
	Eigen::MatrixXd m_k;	// ��������������� ������������

	TYPE
//		Error,		// ������������� �������������� ������ (��������� �����������)
		m_eps_max,	// ������������ ������������� �������������� ������ 
		m_eps_global;

	Eigen::VectorXd
		x0,			// ��������� ��������
		x1, _x1;	// �������� ��� ���� (4 � 5 �������)

	unsigned x_size;		// ����� ������� ��������� ��������

	TYPE m_rounding_error;

protected:
	virtual TYPE StepCorrection(TYPE Error); // ���������� ������ ���� ��������������
	virtual TYPE GetError();
	TYPE RoundingError() const;

	void SetK(int size);

	void SaveSubstepResult(TYPE &tout, TYPE delta, TYPE new_step, TYPE t_end);
	Eigen::VectorXd ThickExtradition(TYPE &Teta, TYPE Step); // ������� ������

	void Set_c();
	void SetA();
	void Set_b();
	void Set_b1();

	unsigned iter; // ������� ���������� ��������

public:

	DormanPrinceSolver();
	void Run(Model &model) override;

	void SetEpsMax(TYPE arg);

	TYPE GetEpsMax() const;
	TYPE GetEpsGlobal() const;
	TYPE GetIter() const;
};
