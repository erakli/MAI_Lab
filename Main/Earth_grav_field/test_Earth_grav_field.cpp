#include <iostream>

#include "file_output.h"
#include "Integrator.h"
#include "Time.h"		// для макросов времени
#include "Sputnik.h"

#include "Functions.h"

using namespace MyFunc::Numbers;
using namespace Earth;
using namespace std;

void Modelling(const TYPE duration, const Orbit::Kepler_elements &elements, CGravitation_field &field);
void Information(const Orbit::Kepler_elements &elements);

int main()
{
	CGravitation_field central_field;
	CNormal_field normal_field;
	CNormal_spheric normal_spheric_field;
	CAnomalous_spheric anomalous_spheric_field;

	Orbit::Kepler_elements
		elements = { 0, 0, 0, 200, 0, 0 };

	Information(elements);

	TYPE duration = SECINDAY;

	Modelling(duration, elements, central_field);
	Modelling(duration, elements, normal_field);
	Modelling(duration, elements, normal_spheric_field);
	Modelling(duration, elements, anomalous_spheric_field);

	elements.i = deg2rad(90);
	Information(elements);

	Modelling(duration, elements, central_field);
	Modelling(duration, elements, normal_field);
	Modelling(duration, elements, normal_spheric_field);
	Modelling(duration, elements, anomalous_spheric_field);

	elements.a = 500;
	elements.i = 0;
	Information(elements);

	Modelling(duration, elements, central_field);
	Modelling(duration, elements, normal_field);
	Modelling(duration, elements, normal_spheric_field);
	Modelling(duration, elements, anomalous_spheric_field);

	elements.i = deg2rad(90);
	Information(elements);

	Modelling(duration, elements, central_field);
	Modelling(duration, elements, normal_field);
	Modelling(duration, elements, normal_spheric_field);
	Modelling(duration, elements, anomalous_spheric_field);

	elements.i = 0;
	elements.a = 50000;
	Information(elements);

	duration *= 7;

	Modelling(duration, elements, central_field);
	Modelling(duration, elements, normal_field);
	Modelling(duration, elements, normal_spheric_field);
	Modelling(duration, elements, anomalous_spheric_field);
}


void Modelling(const TYPE duration,
	const Orbit::Kepler_elements &elements, CGravitation_field &field)
{
	CDormanPrince Integrator;
	Integrator.setEps_Max(1.0e-13);

	CSputnik sputnik(elements);
	sputnik.set_t1(duration);
	sputnik.setInterval(SECINMIN);

	sputnik.addForce(field);

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