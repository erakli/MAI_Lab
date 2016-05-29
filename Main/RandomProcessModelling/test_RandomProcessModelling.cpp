#include <iostream>

#include "file_output.h"

#include "ShapingFilter.h"
#include "Dorman-Prince_modified.h"

using namespace std;

int main()
{
	cout << "* * * Modelling of ShapingFilter * * *"
		<< endl << endl;

	CDormanPrince_modified Integrator;

	Integrator.setEps_Max(1.0e-13); // ������ ����������� ���������� �����������

	// ���������������� ������
	CShapingFilter
		//Model(hWnd);
		Model;

	TYPE omega = 1.0e+3;	// ������� ��������� ������ ����

	// ���� ���������� �������������� � ����������
	int repeat(0);
	do
	{
		TYPE t, interval;

		cout << "Define time of modelling: "; cin >> t; cout << endl;
		Model.set_t1(t);

		// ���� � ������ ��� ����������, �� ������ ���������� ��
		if (!repeat)
		{
			Model.Generate_WhiteNoise(omega);

			// ����������� ���������� � �������� ��������� ����������
			Integrator.set_correlation_interval(Model.get_correlation_interval());

			cout << "White Noise is generated. For this session max modelling time is "
				<< t << endl << endl;
		}

		cout << "What about output interval (sec)? "; cin >> interval; cout << endl;
		Model.setInterval(interval); // �������� ������

		// ��������� ��������������
		Integrator.Run(Model);

		// ������ ����� ����������� � ����
		to_file(Model.getResult());

		cout << endl << "	Repeat modelling? "; cin >> repeat; cout << endl;

	} while (repeat);

}