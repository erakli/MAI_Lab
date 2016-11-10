#include <iostream>

#include "file_output.h"

#include "Functions.h"

#include "Coordinates.h"
#include "Time.h"
#include "SolarSystem.h"

#include "SolarSystemTests.h"

using namespace std;
using namespace Tests;
using namespace MyFunc;

/* Показ данных */

void Show(const MyTime::Date &date)
{
	cout 
		<< int(date.hour) << ":" << int(date.minute) << ":" << int(date.second) 
		<< "	"
		<< int(date.day) << "." << int(date.month) << "." << date.year;
}

void Show(const Eigen::VectorXd &vec){
	int length = vec.size();
	for (int i = 0; i < length - 1; i++)
		cout << fixed << vec[i] << "	";
	cout << fixed << vec[length - 1];
}


/* Вспомогательные функции */

void Tests::Init(const char* Name)
{
	cout.precision(3);
	cout
		<< "\n\n"
		<< " * Test " << Name << " started. * " << endl;
}

void Tests::Final()
{
	cout << "\n\n - finished." << endl;
}


/* Tests */

void Tests::TestCoordinates()
{
	Init("TestCoordinates");

	MyTime::Date date = { 2016, 6, 22, 0, 0, 0 };
	TYPE 
		JD = MyTime::Transformation::DateToJD(date),
		lambda = deg2rad(0);

	TYPE s = StarTime(JD, lambda);

	cout << "\nJD = " << fixed << JD;
	cout << "\nlambda = " << fixed << lambda << endl;
	cout << "\nStarTime = " << fixed << s << endl;

	Eigen::Vector3d vec_geographic;
	vec_geographic[0] = 0;
	vec_geographic[1] = deg2rad(0);
	vec_geographic[2] = deg2rad(0);

	Eigen::Vector3d result_fix(Transform::Geographic2Fix(vec_geographic));

	cout << "\nOriginal:	"; Show(vec_geographic);
	cout << "\nGeographic2Fix:	"; Show(result_fix);

	Eigen::Vector3d dot;
	dot[0] = 1 + Earth::meanRadius;
	dot[1] = 0;
	dot[2] = 0;

	Eigen::Vector3d result_topo = Transform::Fix2Topo(dot, vec_geographic);

	cout << "\ndot:		"; Show(dot);
	cout << "\nFix2Topo:	"; Show(result_topo);

	Eigen::Vector2d result_horiz = Transform::Fix2Horiz(dot, vec_geographic);

	cout << "\nFix2Horiz:	"; Show(result_horiz * DEG_IN_RAD);

	Final();
}

void Tests::TestFix2Horiz()
{
	Init("TestFix2Horiz");

	Eigen::Vector3d center_geographic;
	Eigen::Vector3d center_fix;
	Eigen::Vector3d to_find_vec;

	for (int fi = -2; fi < 3; fi++)
	{
		center_geographic[0] = 0;
		center_geographic[1] = deg2rad(45 * fi);
		center_geographic[2] = deg2rad(0);

		cout << "\ncenter_geographic:	"; Show(center_geographic);

		center_fix = Transform::Geographic2Fix(center_geographic);

		for (int count = 0; count < VEC_SIZE; count++)
		{
			for (size_t i = 0; i < count; i++)
			{
				to_find_vec = center_fix;
				TYPE temp;
				for (int j = -1; j < 2; j++)
				{
					temp = to_find_vec(i);
					to_find_vec(i) = j;

					cout << "\nto_find_vec:		"; Show(to_find_vec);
					cout << "\nFix2Horiz:	"; Show(Transform::Fix2Horiz(to_find_vec, center_geographic) * DEG_IN_RAD);
					to_find_vec(i) = temp;
				}
			}
		}
	}	

	Final();
}

void Tests::TestTime()
{
	Init("TestTime");

	MyTime::Date date = { 2016, 03, 16, 0, 0, 0 };
	TYPE JD = MyTime::Transformation::DateToJD(date);

	cout << "\ndate:	"; Show(date);
	cout << "\nDateToJD = " << fixed << JD;

	Final();
}

void Tests::SolarSystem()
{
	Init("SolarSystem");

	cout 
		<< "\nangularVeloc	=	" << scientific << Earth::angularVeloc
		<< "\nmeanRadius	=	" << fixed << Earth::meanRadius;

	Final();
}
