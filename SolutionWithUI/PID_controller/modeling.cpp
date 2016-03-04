#include "modelling.h"

CMatrix PIDModelling(const double t){

	CDormanPrince Integrator;

	Integrator.setStep(1.0e-3);  // ������ �������� ����
	Integrator.setEps_Max(1.0e-17); // ������ ����������� ���������� �����������
	Integrator.setEps(1.0e-5); // ������ ��������� �����������

	// ���������������� ������ (� ������� ��� ������)
	CPID_controller Model;
	//TTestModel Model;

	Model.set_t1(t);
	Model.setInterval(0.1); // �������� ������

	// ��������� ��������������
	Integrator.Run(Model);

	// ������ ����� ����������� � ����
	return Model.getResult();

//	Dorman_to_file(Result, Integrator);
}