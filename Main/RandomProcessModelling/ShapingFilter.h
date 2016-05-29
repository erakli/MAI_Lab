#pragma once

#include "Model.h"

class CShapingFilter : public CModel
{
private:
	TYPE
		K,				// ����������� � ��������� ������������ �������
		T[2],			// ����������� � ��������� � ����������� ������������ �������
		xi;				// ���������� ��������������� ������������ �������

	TYPE
		Mx;				// ���. �������� ���������� ��������

	// �������� ���������� ������ ����
	TYPE correlation_interval_WhiteNoise;

	// ���������� ������ ���� �� �� ����� ������������� � �������� ���������� ����������
	CVector WhiteNoise;
	bool WhiteNoise_got;	// ���� �� �������� ���������� ������ ����

	TYPE getWhiteNoise(cTYPE t) const;

private:
	void ShapingFilter(CVector &RightPart,
		TYPE x1, TYPE x2, TYPE input) const;

public:

	CShapingFilter();

	void addResult(CVector &X, TYPE t) override;

	// ��������� (�����)������ ����. ������ ���������� ����� ��������������
	void Generate_WhiteNoise(const TYPE omega);
	TYPE get_correlation_interval() const;

	CVector getRight(const CVector &X, TYPE t) const override;

	bool Stop_Calculation(TYPE t, TYPE Step, CVector &PrevStep, CVector &CurStep) override;
};