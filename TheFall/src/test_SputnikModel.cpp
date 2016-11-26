#include <iostream>


#include "DormanPrinceSolver.h"
#include "file_output.h"

#include "Time.h"		// для макросов времени
#include <SolarSystem.h>
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
void OverallTest();

int main()
{
//	GravitationTest();
//	AerodynamicForceTest();
	OverallTest();

	system("pause");
}



void Modelling(const TYPE duration,
               const Orbit::Kepler_elements &elements, Force * force)
{
	DormanPrinceSolver Integrator;
	Integrator.SetEpsMax(1.0e-13);

	Sputnik sputnik(elements);
	sputnik.Set_t1(duration);
	sputnik.SetInterval(SECINMIN);

	sputnik.AddForce(force);

	Integrator.Run(sputnik);

	Dorman_to_file(sputnik.GetResult(), Integrator);
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
		elements = { 0, 0, 0, 100, 0, 0 };

	DormanPrinceSolver Integrator;
	GravitationField central_field;
	AerodynamicForce aerodynamic_force;
	Sputnik sputnik(elements);

	Information(elements);

	TYPE duration = SECINDAY * 3;	
	
	sputnik.SetMass(50);
	sputnik.SetBallisticCoeff(1.4);

	sputnik.Set_t1(duration);
	sputnik.SetInterval(SECINMIN);

	sputnik.AddForce(&central_field);
	sputnik.AddForce(&aerodynamic_force);

	Integrator.SetEpsMax(1.0e-13);
	Integrator.Run(sputnik);

	Dorman_to_file(sputnik.GetResult(), Integrator);
}



void OverallTest()
{
	TYPE alpha_height = 450 + Earth::meanRadius;
	TYPE pi_height = 40 + Earth::meanRadius;

	TYPE a = (alpha_height + pi_height) / 2.0;
	TYPE e = (alpha_height - pi_height) / (alpha_height + pi_height);

	Orbit::Kepler_elements
		elements = { 0, deg2rad(42), 0, a, e, deg2rad(0) };

	DormanPrinceSolver Integrator;
	GravitationField central_field;
	AerodynamicForce aerodynamic_force;
	Sputnik sputnik(elements);

#ifdef DEBUG
	Vector6d X = Orbit::Kepler2Decart(elements);
	aerodynamic_force.SetBallisticCoeff(1.4);
	aerodynamic_force.GenerateRandomRealization(100);
	aerodynamic_force.SetHasRandom(true);
	Eigen::Vector3d res = aerodynamic_force.getRight(X, 50.0);
	TYPE norm = res.norm();
#endif

	Information(elements);

	TYPE duration = SECINDAY;

	sputnik.SetMass(50);
	sputnik.SetBallisticCoeff(1.4);

	sputnik.Set_t1(duration);
	sputnik.SetInterval(30.0);

	sputnik.AddForce(&central_field);
	sputnik.AddForce(&aerodynamic_force);

	Integrator.SetEpsMax(1.0e-13);
	Integrator.Run(sputnik);

#ifdef DEBUG
	//to_file(aerodynamic_force.GetRightPartsList());
	//to_file(sputnik.GetRightPartsList());
#endif

	cout << endl << "sputnik_orbit generated" << endl;

	Dorman_to_file(sputnik.GetResult(), Integrator);
}