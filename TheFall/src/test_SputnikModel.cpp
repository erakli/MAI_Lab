#include <iostream>


#include "DormanPrinceSolver.h"
#include "file_output.h"

#include "Time.h"		// для макросов времени
#include "Gravitation.h"
#include "AerodynamicForce.h"
#include "Sputnik.h"

#include "Functions.h"

using namespace MyFunc;
using namespace std;

void Modelling(const TYPE duration, const Orbit::Kepler_elements &elements, Force * force);
void Information(const Orbit::Kepler_elements &elements);
void GravitationTest();
void AerodynamicForceTest();

int main()
{
//	GravitationTest();
	AerodynamicForceTest();
}



void Modelling(const TYPE duration,
               const Orbit::Kepler_elements &elements, Force * force)
{
	DormanPrinceSolver Integrator;
	Integrator.setEps_Max(1.0e-13);

	Sputnik sputnik(elements);
	sputnik.set_t1(duration);
	sputnik.setInterval(SECINMIN);

	sputnik.AddForce(force);

	Integrator.Run(sputnik);

	Dorman_to_file(sputnik.getResult(), Integrator);
}

void Information(const Orbit::Kepler_elements &elements)
{
	cout << "Modelling with parameters:\n"
		<< "	_Omega	= " << elements._Omega << "\n"
		<< "	i	= " << elements.i << "\n"
		<< "	omega	= " << elements.omega << "\n"
		<< "	a	= " << elements.a << "\n"
		<< "	e	= " << elements.e << "\n"
		<< "	teta	= " << elements.teta << "\n"
		<< endl;
}

void GravitationTest()
{
	GravitationField central_field;

	Orbit::Kepler_elements
		elements = { 0, 0, 0, 200, 0, 0 };

	Information(elements);

	TYPE duration = SECINDAY;

	Modelling(duration, elements, &central_field);

	elements.i = deg2rad(90);
	Information(elements);

	Modelling(duration, elements, &central_field);

	elements.a = 500;
	elements.i = 0;
	Information(elements);

	Modelling(duration, elements, &central_field);

	elements.i = deg2rad(90);
	Information(elements);

	Modelling(duration, elements, &central_field);

	elements.i = 0;
	elements.a = 50000;
	Information(elements);

	duration *= 7;

	Modelling(duration, elements, &central_field);
}

void AerodynamicForceTest()
{
	Orbit::Kepler_elements
		elements = { 0, 0, 0, 200, 0, 0 };

	DormanPrinceSolver Integrator;
	GravitationField central_field;
	AerodynamicForce aerodynamic_force;
	Sputnik sputnik(elements);

	Information(elements);

	TYPE duration = SECINDAY;	
	
	sputnik.set_t1(duration);
	sputnik.setInterval(SECINMIN);

	sputnik.AddForce(&central_field);
	sputnik.AddForce(&aerodynamic_force);

	Integrator.setEps_Max(1.0e-13);
	Integrator.Run(sputnik);

	Dorman_to_file(sputnik.getResult(), Integrator);
}
