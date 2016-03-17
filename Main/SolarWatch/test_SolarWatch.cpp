#include  "file_output.h"

#include "Time.h"
#include "Integrator.h"

#include "SolarSystem.h"
#include "TestSolarWatch.h"

int main()
{
	if (TESTS)
	{
		Tests::TestTime();
		Tests::TestCoordinates();
		Tests::SolarSystem();
	}

	CDormanPrince Integrator;
	Earth::CEarth Model(2457744.5);

	Integrator.setEps_Max(1.0e-12);
	Model.setInterval(SECINDAY);
	//Model.set_t1(2457468.5, true);

	Integrator.Run(Model);

	// делаем вывод результатов в файл
	CMatrix Result(Model.getResult());

	Dorman_to_file(Result, Integrator);
}
