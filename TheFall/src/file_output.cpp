#include <Windows.h>
#include <ShellAPI.h>

#include "file_output.h"

#include <fstream>
#include <iostream>

#include <string>

#include "Constants.h"

#define FILE "output"
#define EXTENSION ".txt"

#define COLCOUNT 7

using namespace std;
using namespace Eigen;

// ----------------- нумерация выходных файлов
static short int FirstNum = 0, SecondNum = 0; 

void Dorman_to_file(const VectorList &Result, const DormanPrinceSolver &Integrator,
					bool radians){

	// ----------------- нумерация выходных файлов
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


	// ----------------- формирование имени выходного файла
	char FileName[14];

	strcpy(FileName, FILE);
	strcat(FileName, cFNum);
	strcat(FileName, cSNum);
	strcat(FileName, EXTENSION);


	// ----------------- создание выходного файла
	ofstream fout;
	fout.open(FileName);
	if (!fout.is_open())
	{
		cout << "File couldn't been created";
		system("pause");
		exit(1);
	}


	/*
		Множитель перевода радиан в градусы

			По умолчанию равен 1. Если результат вывода
			выбран в градусах (radians = false), то результат
			вывода будет в градусах
	*/
	TYPE rad2deg;
	(radians) ? rad2deg = 1 : rad2deg = 180 / PI;

	fout.precision(20);

	// ----------------- заполнение файла
	VectorXd vector;
	int ColCount = Result.begin()->size();

	for (	VectorList::const_iterator line = Result.begin(); 
			line != Result.end(); 
			++line)
	{
		vector = *line;
		fout << vector(0) << "	";	// время

		for (int j = 1; j < ColCount - 1; j++)
		{
			fout << vector(j) * rad2deg << "	";
		}

		fout << vector(ColCount - 1) * rad2deg;
		fout << "\n";
	}

	fout.close();


	// ------------------------------------------------------------ Интерфейс
	cout << "\n\nProcess have been ended. \n	Number of iterations: "
		<< fixed << Integrator.get_iter()
		<< "\n	Global Eps: " << scientific << Integrator.getEps_Global()
		<< "\n\nNow would be opened result file\n";
	Sleep(DELAY);
	// ------------------------------------------------------------ Интерфейс


	ShellExecuteA(nullptr, "open", FileName, nullptr, nullptr, SW_RESTORE);

	SecondNum++;

	cout << fixed;
}


void to_file(const VectorList& Result, bool radians)
{
	// ----------------- нумерация выходных файлов
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


	// ----------------- формирование имени выходного файла
	char FileName[14];

	strcpy(FileName, FILE);
	strcat(FileName, cFNum);
	strcat(FileName, cSNum);
	strcat(FileName, EXTENSION);


	// ----------------- создание выходного файла
	ofstream fout;
	fout.open(FileName);
	if (!fout.is_open())
	{
		throw std::exception();
	}


	/*
		Множитель перевода радиан в градусы

		По умолчанию равен 1. Если результат вывода
		выбран в градусах (radians = false), то результат
		вывода будет в градусах
	*/
	TYPE rad2deg;
	(radians) ? rad2deg = 1 : rad2deg = 180 / PI;

	fout.precision(20);

	// ----------------- заполнение файла
	VectorXd vector;
	int ColCount = Result.begin()->size();

	for (	VectorList::const_iterator line = Result.begin();
			line != Result.end();
			++line)
	{
		vector = *line;
		fout << vector(0) << "	";	// время

		for (int j = 1; j < ColCount - 1; j++)
		{
			fout << vector(j) * rad2deg << "	";
		}

		fout << vector(ColCount - 1) * rad2deg;
		fout << "\n";
	}

	fout.close();


	ShellExecuteA(nullptr, "open", FileName, nullptr, nullptr, SW_RESTORE);

	SecondNum++;
}

void to_file(const VectorXd& Result, bool radians)
{
	// ----------------- нумерация выходных файлов
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


	// ----------------- формирование имени выходного файла
	char FileName[14];

	strcpy(FileName, FILE);
	strcat(FileName, cFNum);
	strcat(FileName, cSNum);
	strcat(FileName, EXTENSION);


	// ----------------- создание выходного файла
	ofstream fout;
	fout.open(FileName);
	if (!fout.is_open())
	{
		throw std::exception();
	}


	/*
		Множитель перевода радиан в градусы

		По умолчанию равен 1. Если результат вывода
		выбран в градусах (radians = false), то результат
		вывода будет в градусах
	*/
	TYPE rad2deg;
	(radians) ? rad2deg = 1 : rad2deg = 180 / PI;

	fout.precision(20);

	// ----------------- заполнение файла
	int size = Result.size();
	for (int i = 0; i < size; i++)
	{
			fout << Result[i] * rad2deg;
			fout << "\n";
	}

	fout.close();

	ShellExecuteA(nullptr, "open", FileName, nullptr, nullptr, SW_RESTORE);

	SecondNum++;
}

//void Read_from_file(const char* FileName, CMatrix& target, const UINT PredictSize)
//{
//	// ----------------- открытие входного файла
//	ifstream file_in;
//	file_in.open(FileName);
//
//	if (!file_in.is_open())
//	{
//		throw std::exception();
//	}
//
//	// пытаемся предсказать размер входных данных
//	target.reserve(PredictSize);
//
//	string 
//		buffer,
//		delitimer("	"),
//		end_of_string;
//
//	string::size_type start_to_find, found;
//
//	while (true)
//	{
//		getline(file_in, buffer);
//
//		if (!file_in.eof())
//		{
//			CVector row_from_file;
//			row_from_file.reserve(COLCOUNT);
//
//			start_to_find = 0;
//
//			while (true)
//			{
//				found = buffer.find(delitimer, start_to_find + 1);
//				if (found != string::npos)
//				{
//					row_from_file.push_back(
//						stod(
//							buffer.substr(start_to_find, found - start_to_find)
//						));
//
//					start_to_find = found;
//				}
//				else
//				{
//					// последний элемент добиваем
//					row_from_file.push_back(
//						stod(buffer.substr(start_to_find)));
//					break;
//				}
//			}
//
//			target.push_back(row_from_file);
//		}
//		else
//			break;
//	}
//
//	file_in.close();
//
//}
