#include  "file_output.h"

#include "Functions.h"

#include "Time.h"
#include "Integrator.h"

#include "SolarSystem.h"
#include "TestSolarWatch.h"

#include "Gnomon.h"

using namespace MyFunc;

int main()
{
	if (TESTS)
	{
		Tests::TestTime();
		Tests::TestCoordinates();
		Tests::SolarSystem();
	}

	//CDormanPrince Integrator;
	//Earth::CEarth Model;

	//Integrator.setEps_Max(1.0e-12);
	//Model.setInterval(SECINDAY);
	////Model.set_t1(2457468.5, true);

	//Integrator.Run(Model);

	//Model.setStart(CVector::copyPart(Model.getLastResult(), 1, 7));

	//// делаем вывод результатов в файл
	//CMatrix Result(Model.getResult());

	//Dorman_to_file(Result, Integrator);

	MyTime::Date date = { 2016, 6, 22, 0, 0, 0 };
	TYPE JD = MyTime::Transformation::DateToJD(date);

	CGnomon gnom(Numbers::deg2rad(55.75222), Numbers::deg2rad(37.61556), 3);

	// делаем вывод результатов в файл
	CMatrix Result(gnom.GetShadowForDate(JD));

	/*CMatrix Result(1, 0);
	Result[0] = gnom.GetLightTimeForYear(1);*/

	to_file(Result);
}
