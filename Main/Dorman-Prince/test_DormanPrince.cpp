#include <windows.h>
#include <ShellAPI.h>

#include <iostream>
#include <fstream>

#include "Integrator.h"

#define FILE "output.txt"
#define DELAY 1000

using namespace std;

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

	ofstream fout/*, ftest("test.txt")*/;
	fout.open(FILE);
	if (!fout.is_open())
	{
		cout << "File couldn't been created";
		system("pause");
		exit;
	}

	for (int i = 0; i < Result.getRowCount(); i++)
	{
		for (int j = 0; j < Result.getColCount(); j++)
		{
			fout << Result[i][j] << "	";
		}
		/*ftest <<
			cos(i) / pow(1 + exp(2 * i), 0.5) << "	" <<
			sin(i) / pow(1 + exp(2 * i), 0.5) << "\n";*/
		//ftest << pow(i, 2) / 2 << "\n";
		//ftest << pow(Result[i][0], 3) / 3 << "\n";
		fout << "\n";
	}

	//ftest.close();
	fout.close();
	
	// ------------------------------------------------------------ ���������
	cout << "\n\nProcess have been ended. \n	Number of iterations: " 
		<< Dorman.get_iter()
		<< "\n	Global Eps: " << Dorman.getEps_Global()
		<< "\n\nNow would be opened result file\n";
	Sleep(DELAY);
	// ------------------------------------------------------------ ���������

	ShellExecute(NULL, TEXT("open"), TEXT(FILE), NULL, NULL, SW_RESTORE);
};