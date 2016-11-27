#include <Windows.h>
#include <ShellAPI.h>

#include "file_output.h"

#include <fstream>
#include <iostream>

#include <string>

#include "Constants.h"

#define FILE "output"
#define EXTENSION ".txt"

using namespace std;
using namespace Eigen;

// ----------------- нумерация выходных файлов
static short int FirstNum = 0, SecondNum = 0; 

void Dorman_to_file(const MatrixXd &result, const DormanPrinceSolver &integrator,
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
	MatrixXd output_matrix(result);
	output_matrix.rightCols(result.cols() - 1) *= rad2deg;
	fout << output_matrix;

	fout.close();


	// ------------------------------------------------------------ Интерфейс
	cout << "\n\nProcess have been ended. \n	Number of iterations: "
		<< fixed << integrator.GetIter()
		<< "\n	Global Eps: " << scientific << integrator.GetEpsGlobal()
		<< "\n\nNow would be opened result file\n";
	Sleep(DELAY);
	// ------------------------------------------------------------ Интерфейс


	ShellExecuteA(nullptr, "open", FileName, nullptr, nullptr, SW_RESTORE);

	SecondNum++;

	cout << fixed;
}


void to_file(const MatrixXd& result, bool radians)
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
	MatrixXd output_matrix(result);
	output_matrix.rightCols(result.cols() - 1) *= rad2deg;
	fout << output_matrix;

	fout.close();


	ShellExecuteA(nullptr, "open", FileName, nullptr, nullptr, SW_RESTORE);

	SecondNum++;
}

void to_file(const VectorXd& result, bool radians)
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
	int size = result.size();
	for (int i = 0; i < size; i++)
	{
		fout << result[i] * rad2deg;
		fout << "\n";
	}

	fout.close();

	ShellExecuteA(nullptr, "open", FileName, nullptr, nullptr, SW_RESTORE);

	SecondNum++;
}



void to_file_plot(const Eigen::MatrixXd &result)
{
	size_t result_size = result.rows();
	ofstream datafile("C:\\_plot\\matrix.dat");
	ofstream pointsfile("C:\\_plot\\points.dat");
	datafile.precision(20);
	pointsfile.precision(20);

	for (size_t i = 0; i < result_size; i++)
	{
		datafile << result.block(0, 1, i + 1, 3);
		datafile << endl << endl << endl;

		pointsfile << result.row(i).segment(1, VEC_SIZE);
		pointsfile << endl << endl << endl;
	}	
	datafile.close();

	ofstream com("C:\\_plot\\animator.gp");
	com << "set xrange [-7000:7000]" << endl;
	com << "set yrange [-7000:7000]" << endl;
	com << "set zrange [-7000:7000]" << endl;
	com << "unset colorbox" << endl;
	com << "set terminal png size 750, 750" << endl;
	com << "set key off" << endl;
	com << "set size square" << endl;
	com << endl;
	com << "set style line 1 lc rgb '#a2142f' pt 7 ps 1.5 lt 1 lw 1 # --- red" << endl;
	com << endl;
	com << "iterations = " << result_size << endl;
	com << "iterator = 0" << endl;
	com << "load \"C:/_plot/animate.gp\"" << endl;
	com.close();

	ofstream animate("C:\\_plot\\animate.gp");
	animate << "iterator=iterator+1" << endl;
	animate << "if (iterator < iterations)\\" << endl;
	animate << "	set output \"C:/_plot/output/\".iterator.\".png\"; \\" << endl;
	animate << "	splot ";
	animate << "\"C:/_plot/matrix.dat\" index iterator using 1:2:3 w lines, ";
	animate << "\"C:/_plot/points.dat\" index iterator using 1:2:3 w p ls 1; \\" << endl;
	animate << "	reread" << endl;
	animate.close();

	system("\"C:\\Program Files (x86)\\gnuplot\\bin\\gnuplot.exe\" C:\\_plot\\animator.gp");	
}