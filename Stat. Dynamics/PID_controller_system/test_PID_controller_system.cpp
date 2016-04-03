#include "file_output.h"

#include "PID_model.h"
#include "Dorman-Prince_modified.h"


int main()
{
	CDormanPrince_modified Integrator;

	Integrator.setEps_Max(1.0e-13); // ������ ����������� ���������� �����������

	// ���������������� ������
	CPID_controller
		//Model(hWnd);
		Model;

	TYPE t = 50;

	Model.set_t1(t);
	Model.setInterval(0.1); // �������� ������

	TYPE omega = 1.0e+3;	// ������� ��������� ������ ����

	Model.Generate_WhiteNoise(omega);

	// ����������� ���������� � �������� ��������� ����������
	Integrator.set_correlation_interval(Model.get_correlation_interval());

	// ��������� ��������������
	Integrator.Run(Model);

	// ������ ����� ����������� � ����
	to_file(Model.getResult());
}