#include "SolarSystemTests.h"

#include <iostream>
using namespace std;

int main()
{
	Tests::TestTime();
	Tests::TestCoordinates();
	Tests::TestFix2Horiz();
	Tests::SolarSystem();

	cout << "\nPress any key to exit...";
	int a; cin >> a;
}
