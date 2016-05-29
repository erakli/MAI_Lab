#include <exception>

#include "WhiteNoise.h"

#include "ShapingFilter.h"

/* * * * * * * * * * CShapingFilter * * * * * * * * * */

#define SYSTEM_COORDINATES		2

CShapingFilter::CShapingFilter(){

	StartValues.setSize(SYSTEM_COORDINATES);
	s_size = StartValues.getSize();
	
	/* ������������ � ��������� � ����������� ������������ ������� */
	K = 0.0174147114037780;
	T[0] = 1.261682186852e-8;
	T[1] = 0.15897383780486;
	xi = 0.047692151341457;

	Mx = 3;

	correlation_interval_WhiteNoise = 0;
	WhiteNoise_got = false;
}

void CShapingFilter::addResult(CVector& X, TYPE t)
{
	CVector compile(X); // ������ ����������
	
	/*	��������� ����� �� ��. ��� ��� ���� ����������
		��� � ������� ��, �� ����� � ��������� ����� 
		
		y1 = K (T_1 x_2 + x_1)
	*/
	TYPE y1 = K * (T[0] * X[1] + X[0]);
	compile.push_back(y1 + Mx);	// ���������� ���. �������� ���������� ��������

	CModel::addResult(compile, t);
}

/*
*	��������� ������� (�����)������ ���� �� �������� ������� �����
*/
void CShapingFilter::Generate_WhiteNoise(const TYPE omega)
{
	TYPE dt(0);

	WhiteNoise = Get_WhiteNoise(omega, t0, t1, dt);

	correlation_interval_WhiteNoise = dt;
	WhiteNoise_got = true;

	//lookUp_of_WhiteNoise.push_back(WhiteNoise);
}

TYPE CShapingFilter::get_correlation_interval() const
{
	return correlation_interval_WhiteNoise;
}

/*
*	������� �� ��� ������������ �������.
*	������ - ������� ��������� ���������� ������������� ����� - ����� ���������
*/
TYPE CShapingFilter::getWhiteNoise(cTYPE t)  const
{
	if (!WhiteNoise_got)
	{
		throw std::exception("WhiteNoise hasn't been generated");
	}

	TYPE index_WN;
	modf(t / correlation_interval_WhiteNoise, &index_WN);

	return WhiteNoise[int(index_WN)];
}


/*
*	����������� ������
*/
void CShapingFilter::ShapingFilter(CVector &RightPart,
	TYPE x1, TYPE x2, TYPE input) const
{
	RightPart.push_back(x2);
	RightPart.push_back(
		(-2 * T[1] * xi * x2 - x1 + input) / pow(T[1], 2)
		);
}

CVector CShapingFilter::getRight(const CVector &X, TYPE t) const
{
	// ������� �� ��� ������������ �������.
	TYPE nu = getWhiteNoise(t);

	CVector RightPart;
	ShapingFilter(RightPart, X[0], X[1], nu);

	return RightPart;
}

bool CShapingFilter::Stop_Calculation(TYPE, TYPE, CVector &, CVector &)
{
	return false;
}