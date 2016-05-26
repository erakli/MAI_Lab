#include "Model.h"
#include "Dorman-Prince_modified.h"
#include <WhiteNoise.h>
#include <file_output.h>

class CFilter : public CModel
{
private:
	TYPE
		K_filter,			// ����������� � ��������� ������������ �������
		T_filter,			// ����������� � ����������� ������������ �������
		xi_filter;			// ���������� ��������������� ������������ �������

	// �������� ���������� ������ ����
	TYPE correlation_interval_WhiteNoise;

	// ���������� ������ ���� �� �� ����� ������������� � �������� ���������� ����������
	CVector WhiteNoise;

	TYPE getWhiteNoise(cTYPE t) const;

	/*
	*	����������� ������
	*/
	void ShapingFilter(CVector &RightPart, TYPE x1, TYPE x2, TYPE input) const;

public:
	CFilter();

	// ��������� (�����)������ ����. ������ ���������� ����� ��������������
	void Generate_WhiteNoise(const TYPE omega);
	TYPE get_correlation_interval() const;

	CVector getRight(const CVector &X, TYPE t) const override;
	bool Stop_Calculation(TYPE t, TYPE Step, CVector &PrevStep, CVector &CurStep) override;
};

TYPE CFilter::getWhiteNoise(cTYPE t) const
{
	TYPE index_WN;
	modf(t / correlation_interval_WhiteNoise, &index_WN);

	return WhiteNoise[int(index_WN)];
}

void CFilter::ShapingFilter(CVector& RightPart, TYPE x1, TYPE x2, TYPE input) const
{
	RightPart.push_back(x2);
	RightPart.push_back(
		(input * K_filter - 2 * T_filter * xi_filter * x2 - x1) / pow(T_filter, 2)
		);
}

CFilter::CFilter()
{
	StartValues.setSize(2);
	s_size = StartValues.getSize();

	StartValues[0] = 0;		// x1
	StartValues[1] = 0;		// x2

	/* ������������ � ��������� � ����������� ������������ ������� */
	K_filter = 4 / sqrt(7);
	T_filter = 1 / 7.0;
	xi_filter = 1;

	correlation_interval_WhiteNoise = 0;
}

void CFilter::Generate_WhiteNoise(const TYPE omega)
{
	TYPE dt(0);

	WhiteNoise = Get_WhiteNoise(omega, t0, t1, dt);

	correlation_interval_WhiteNoise = dt;
}

TYPE CFilter::get_correlation_interval() const
{
	return correlation_interval_WhiteNoise;
}

CVector CFilter::getRight(const CVector& X, TYPE t) const
{
	/* ��������� ������������� ������������������ ������ ������ ������� �� */
	TYPE x1, x2;

	x1 = X[0];
	x2 = X[1];

	TYPE nu = getWhiteNoise(t);

	/* ��������� �������������� ������ ��� ���������� �������� �� ���� ������� */
	CVector Y;
	Y.reserve(s_size);

	ShapingFilter(Y, x1, x2, nu);

	return Y;
}

bool CFilter::Stop_Calculation(TYPE t, TYPE Step, CVector& PrevStep, CVector& CurStep)
{
	return false;
}

CMatrix get_K(CVector &realization)
{
	auto
		n = realization.getSize(),
		k_max = n - 120;

	TYPE mean = 0;
	for (auto i = 0; i < n; i++)
		mean += realization[i];
	mean /= n;

	CVector K(k_max);
	TYPE sum;

	for (auto k = 0; k < k_max; k++)
	{
		sum = 0;
		for (auto i = 0; i < n - k; i++)
		{
			sum += (realization[i] - mean) * (realization[i + k] - mean);
		}
		K[k] = sum / (n - k - 1);
	}

	CMatrix res(2, k_max);

	res[0] = K;

	return res.flip();
}

//#define UIRS
#ifdef UIRS
int main()
{
	CDormanPrince_modified Integrator;

	Integrator.setEps_Max(1.0e-13); // ������ ����������� ���������� �����������

	// ���������������� ������
	CFilter
		//Model(hWnd);
		Model;

	TYPE
		//t = 10;
		t = 300;

	Model.set_t1(t);
	Model.setInterval(0.001); // �������� ������

	TYPE omega = 1.0e+3;	// ������� ��������� ������ ����

	Model.Generate_WhiteNoise(omega);

	// ����������� ���������� � �������� ��������� ����������
	Integrator.set_correlation_interval(Model.get_correlation_interval());

	// ��������� ��������������
	Integrator.Run(Model);

	CMatrix result(Model.getResult());

	to_file(result);

	CMatrix temp(result.flip());
	CVector for_K(temp[1]);

	// ������ ����� ����������� � ����
	to_file(get_K(for_K));
}
#endif