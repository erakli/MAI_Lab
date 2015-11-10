#include "file_output.h"

#include <fstream>
#include <cstring>
#include <algorithm>

#define FILE "output"
#define EXTENSION ".txt"

void Dorman_to_file(const TMatrix &Result, const TDormanPrince &Integrator,
					bool radians){

	static short int FirstNum = 0, SecondNum = 0;

	// ----------------- ��������� �������� ������
	char cFNum[2], cSNum[2];

	if (SecondNum > 9)
	{
		SecondNum = 0;
		FirstNum++;
	}

	cFNum[0] = FirstNum + '0';
	cFNum[1] = 0;

	cSNum[0] = SecondNum + '0';
	cSNum[1] = 0;


	// ----------------- ������������ ����� ��������� �����
	char FileName[14];

	strcpy(FileName, FILE);
	strcat(FileName, cFNum);
	strcat(FileName, cSNum);
	strcat(FileName, EXTENSION);


	// ----------------- �������� ��������� �����
	ofstream fout;
	fout.open(FileName);
	if (!fout.is_open())
	{
		cout << "File couldn't been created";
		system("pause");
		exit(1);
	}


	/*
		��������� �������� ������ � �������

			�� ��������� ����� 1. ���� ��������� ������
			������ � �������� (radians = false), �� ���������
			������ ����� � ��������
	*/
	TYPE rad2deg;
	(radians) ? rad2deg = 1 : rad2deg = 180 / PI;

	
	// ----------------- ���������� �����
	int ColCount = Result.getColCount();
	for (int i = 0; i < Result.getRowCount(); i++)
	{
		fout << Result[i][0] << "	";	// �����

		for (int j = 1; j < ColCount - 1; j++)
		{
			fout << Result[i][j] * rad2deg << "	";
		}
		fout << Result[i][ColCount - 1] * rad2deg;
		fout << "\n";
	}

	fout.close();


	// ------------------------------------------------------------ ���������
	cout << "\n\nProcess have been ended. \n	Number of iterations: "
		<< Integrator.get_iter()
		<< "\n	Global Eps: " << Integrator.getEps_Global()
		<< "\n\nNow would be opened result file\n";
	Sleep(DELAY);
	// ------------------------------------------------------------ ���������


	ShellExecuteA(NULL, "open", FileName, NULL, NULL, SW_RESTORE);

	SecondNum++;
}