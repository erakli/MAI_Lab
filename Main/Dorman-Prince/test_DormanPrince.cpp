#include "file_output.h"

int main(){
	// ------------------------------------------------------------ ���������
	cout << "Integrating with Dorman and Prince (4(5) order)\n\n"
		<< "Please, choose type of an Aristorf's orbit (0 - small, other - big): ";
	int orbit; 
	cin >> orbit;
	// ------------------------------------------------------------ ���������

	TDormanPrince Dorman;

	Dorman.setStep(1.0e-3);  // ������ �������� ����
	Dorman.setEps_Max(1.0e-17); // ������ ����������� ���������� �����������
	Dorman.setEps(1.0e-5); // ������ ��������� �����������

	// ���������������� ������ (� ������� ��� ������)
	TArenstorfModel Model(orbit);
	//TTestModel Model;
	
	Model.set_t1(Model.Period * 5); // ��������� ������������ �� 5 ��������
	Model.setInterval(0.1); // �������� ������

	// ------------------------------------------------------------ ���������
	cout << "Starting values:\n" << "	Eps_Max = " << Dorman.getEps_Max() <<
		"\n	orbit type (small/big) = " << orbit << 
		"\n	t1 = " << Model.get_t1() << "\n";
	Sleep(DELAY);
	cout << "\n\nProcess started";
	// ------------------------------------------------------------ ���������

	// ��������� ��������������
	Dorman.Run(Model); 

	// ������ ����� ����������� � ����
	TMatrix Result(Model.getResult());

	Dorman_to_file(Result, Dorman);
};