#include <iostream>

#include "Functions.h"

#include "Coordinates.h"
#include "Time.h"
#include "SolarSystem.h"

#include "TestSolarWatch.h"

using namespace std;
using namespace Tests;
using namespace Earth;

/* Показ данных */

void Show(const MyTime::Date &date)
{
	cout 
		<< int(date.hour) << ":" << int(date.minute) << ":" << int(date.second) 
		<< "	"
		<< int(date.day) << "." << int(date.month) << "." << date.year;
}

void Show(const CVector &vec){
	int length = vec.getSize();
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

	TYPE
		JD = J2000 + 0.5,
		lambda = MyFunc::Numbers::deg2rad(30);

	TYPE s = StarTime(JD, lambda);

	cout << "\nJD = " << fixed << JD;
	cout << "\nlambda = " << fixed << lambda << endl;

	cout << "\nStarTime = " << fixed << s << endl;

	CVector vec(3);
	vec[0] = 0;
	vec[1] = 0;
	vec[2] = s;

	CVector result(Transform::Geographic2Fix(vec));

	cout << "\nOriginal:	"; Show(vec);
	cout << "\nGeographic2Fix:	"; Show(result);

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
		<< "\nmuEarth		=	" << scientific << CEarth::muEarth
		<< "\nangularVeloc	=	" << scientific << CEarth::angularVeloc
		<< "\nmeanRadius	=	" << fixed << CEarth::meanRadius;

	Final();
}
