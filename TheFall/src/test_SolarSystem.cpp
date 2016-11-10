#include "SolarSystemTests.h"
#include <cstdlib>

int main()
{
	Tests::TestTime();
	Tests::TestCoordinates();
	Tests::TestFix2Horiz();
	Tests::SolarSystem();

	system("pause");
}
