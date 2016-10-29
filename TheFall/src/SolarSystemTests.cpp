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

	Eigen::VectorXd vec(3);
	vec[0] = 1;
	vec[1] = deg2rad(90);
	vec[2] = deg2rad(90);

	Eigen::VectorXd result(Transform::Geographic2Fix(vec));

	cout << "\nOriginal:	"; Show(vec);
	cout << "\nGeographic2Fix:	"; Show(result);

	cout << "\n\nFix2Topo" << endl;

	Eigen::VectorXd dot(3);
	dot[0] = 1;
	dot[1] = 0;
	dot[2] = 1;

	result = Transform::Fix2Topo(dot, vec);

	cout << "\nFix2Topo:	"; Show(result);

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
		<< "\nangularVeloc	=	" << scientific << CEarth::angularVeloc
		<< "\nmeanRadius	=	" << fixed << CEarth::meanRadius;

	Final();
}
