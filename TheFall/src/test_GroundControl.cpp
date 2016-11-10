#include <iostream>

#include <Constants.h>
#include "Functions.h"

#include "DormanPrinceSolver.h"
#include "file_output.h"

#include "Time.h"		// для макросов времени
#include "Coordinates.h"
#include "SolarSystem.h"

#include "Gravitation.h"
#include "AerodynamicForce.h"
#include "Sputnik.h"

#include "GroundStation.h"

using namespace Eigen;
using namespace MyFunc;
using namespace Transform;
using namespace std;

void Information(const Orbit::Kepler_elements &elements);
MatrixXd GenerateSputnikOrbit(TYPE duration);

int main()
{
	TYPE duration = SECINDAY / 2.0;

	MatrixXd sputnik_orbit = GenerateSputnikOrbit(duration);

	GroundStation ground_station;
	ground_station._geographic_pos << 0, deg2rad(18), deg2rad(173);
	ground_station._vision_zone_angle = deg2rad(150);
	ground_station.observations.resize(int(ceil(duration) + 1), 2);

	Vector3d cur_geographic_pos = ground_station._geographic_pos;
//	MatrixXd fix_positions;
//	fix_positions.resize(int(ceil(duration) + 1), 3);

	Vector3d sputnik_fix_pos;
	Vector2d sputnik_horiz_pos;

	TYPE lambda_start = ground_station._geographic_pos(2);
	TYPE start_time = 0.0;

	for (size_t sec = 0; sec < int(ceil(duration) + 1); sec++)
	{
		cur_geographic_pos(2) = lambda_start + StarTime(start_time, sec);

		sputnik_fix_pos = sputnik_orbit.row(sec).segment(1, VEC_SIZE);
		sputnik_horiz_pos = Fix2Horiz(sputnik_fix_pos, cur_geographic_pos);

		// TODO: добавить проверку на попадание элевации в конус видимости НИП

		ground_station.observations.row(sec) = sputnik_horiz_pos * (180.0 / PI);
//		fix_positions.row(sec) = Geographic2Fix(cur_geographic_pos);
	}

	to_file(sputnik_orbit);
	to_file(ground_station.observations);
	//to_file(fix_positions);
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



MatrixXd GenerateSputnikOrbit(TYPE duration)
{
	TYPE alpha_height = 970 + Earth::meanRadius;
	TYPE pi_height = 140 + Earth::meanRadius;

	TYPE a = (alpha_height + pi_height) / 2.0;
	TYPE e = (alpha_height - pi_height) / (alpha_height + pi_height);

	Orbit::Kepler_elements
		elements = { 0, deg2rad(42), 0, a, e, deg2rad(180) };

	DormanPrinceSolver Integrator;
	GravitationField central_field;
	AerodynamicForce aerodynamic_force;
	Sputnik sputnik(elements);

	Information(elements);

	sputnik.SetMass(50);
	sputnik.SetBallisticCoeff(1.4);

	sputnik.set_t1(duration);
	sputnik.setInterval(1);

	sputnik.AddForce(&central_field);
	sputnik.AddForce(&aerodynamic_force);

	Integrator.setEps_Max(1.0e-13);
	Integrator.Run(sputnik);

	return sputnik.getResult();
}