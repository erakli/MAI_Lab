#include "Functions.h"
#include "Time.h"
#include "SolarSystem.h"

#include "Coordinates.h"

using namespace Earth;
using namespace MyFunc;

/*
	������� �������� ���������� ������� ���� ����� ���������
	������������� (���). ���������� �������� ������������
	�������� ������� � �������� (������� ���� ��� �� �����������
	���������):
		TYPE s

	���������:
		���� ���������� ������������ ���������, ����������������
		������� 0 - 2Pi, �� ��������� � ����������� � ��� � ��������.
*/
TYPE StarTime(const TYPE& JD)
{
	TYPE
		d = JD - J2000,			// ���������� ���� � 01.01.2000
		centuries = d / 36525;	// ���������� ��������, ��������� � 01.01.2000 �.

	TYPE s =
		67310.54841
		+ 8640184.812866 * centuries
		+ 0.093104 * Numbers::pow2(centuries)
		- 6.2e-6 * Numbers::pow3(centuries);

	return
		2 * PI / SECINDAY * fmod(s, SECINDAY);
}


/*
	������ ������ �������� �������� ������� ����� s

	��������� � ��������
*/
TYPE StarTime(const TYPE& JD, const TYPE& lambda)
{
	TYPE 
		t = (Numbers::frac(JD) + 0.5) * SECINDAY;	// t � ����� �� ����� UTC � ���

	return 
		StarTime(JD) + CEarth::angularVeloc * t + lambda;
}


/*
	������� �� ����������� � ��������� ����������

	���� � ��������

	[h, fi, lambda] - ������, ������� �������
*/
CVector Transform::Geographic2Fix(const CVector &geographic)
{
	auto 
		h(geographic[0]), 
		fi(geographic[1]), 
		lambda(geographic[2]);

	CVector Result(3);
	Result[0] = (h + CEarth::meanRadius) * cos(fi) * cos(lambda);
	Result[1] = (h + CEarth::meanRadius) * cos(fi) * sin(lambda);
	Result[2] = (h + CEarth::meanRadius) * sin(fi);

	return Result;
}