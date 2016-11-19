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
	TYPE duration = SECINDAY * 13;
	size_t num_of_results = int(ceil(duration) + 1);

	MatrixXd sputnik_orbit = GenerateSputnikOrbit(duration);
	MatrixXd modules = MatrixXd::Zero(1 + num_of_results / 10, 3);

	GroundStation ground_station(
		{ 0, deg2rad(18), deg2rad(173) }, PI_HALF - deg2rad(75));
//	ground_station._geographic_pos << 0, deg2rad(18), deg2rad(173);
//	ground_station._vision_zone_angle = PI_HALF - deg2rad(75);
//	ground_station.observations.resize(num_of_results, 3);
//	TYPE _vision_zone_angle = PI_HALF - deg2rad(75);
//	MatrixXd observations = MatrixXd::Zero(num_of_results, 3);

	ground_station.Init(num_of_results);

	Vector3d cur_geographic_pos = ground_station.GetGeographicPos();
	MatrixXd fix_positions(num_of_results, 3);

	Vector3d sputnik_fix_pos;
//	Vector2d sputnik_horiz_pos;

//	Vector3d result;

	TYPE lambda_start = cur_geographic_pos(2);
	TYPE start_time = 0.0;

//	size_t num_of_observations = 0;

	for (size_t sec = 0; sec < num_of_results; sec++)
	{
		sputnik_fix_pos = sputnik_orbit.row(sec).segment(1, VEC_SIZE);
		if (sec % 10 == 0)
		{
			modules.row(sec / 10) <<
				sec,
				sputnik_fix_pos.norm(),
				sputnik_orbit.row(sec).segment(VEC_SIZE + 1, VEC_SIZE).norm();
		}

		ground_station.SaveObservation(sputnik_fix_pos, sec);

		//sputnik_horiz_pos = Fix2Horiz(sputnik_fix_pos, cur_geographic_pos);

		//// проверку на попадание элевации в конус видимости НИП
		//if (sputnik_horiz_pos(0) >= _vision_zone_angle)
		//{
		//	result << sputnik_orbit(sec, 0), sputnik_horiz_pos * DEG_IN_RAD;

		//	observations.row(num_of_observations) = result;
		//	num_of_observations++;
		//}
		
		cur_geographic_pos(2) = lambda_start + StarTime(start_time, sec);
		fix_positions.row(sec) = Geographic2Fix(cur_geographic_pos);
	}

//	observations.conservativeResize(num_of_observations, NoChange);

	cout << endl << "Finished" << endl;

	cout << " * Saving sputnik_orbit" << endl;
	to_file(sputnik_orbit);
	to_file(modules);

	cout << " * Saving observations" << endl;
	to_file(ground_station.GetObservations());
//	to_file(observations);

	cout << " * Saving fix_positions" << endl;
	to_file(fix_positions);

	system("pause");
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
	TYPE pi_height = 40 + Earth::meanRadius;

	TYPE a = (alpha_height + pi_height) / 2.0;
	TYPE e = (alpha_height - pi_height) / (alpha_height + pi_height);

	Orbit::Kepler_elements
		elements = { 0, deg2rad(42), 0, a, e, deg2rad(0) };

	DormanPrinceSolver Integrator;
	GravitationField central_field;
	AerodynamicForce aerodynamic_force;
	Sputnik sputnik(elements);

	Information(elements);

	sputnik.SetMass(50);
	sputnik.SetBallisticCoeff(1.4);

	sputnik.Set_t1(duration);
	sputnik.SetInterval(1);

	sputnik.AddForce(&central_field);
	sputnik.AddForce(&aerodynamic_force);

	Integrator.SetEpsMax(1.0e-13);
	Integrator.Run(sputnik);

	cout << endl << "sputnik_orbit generated" << endl;

	return sputnik.GetResult();
}