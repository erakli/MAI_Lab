#include <iostream>

#include <Constants.h>
#include "Functions.h"

#include "DormanPrinceSolver_fixed.h"
#include "file_output.h"

#include "Time.h"		// для макросов времени
#include "Coordinates.h"
#include "SolarSystem.h"

#include "Gravitation.h"
#include "AerodynamicForce.h"
#include "Sputnik.h"

#include "GroundStation.h"

#include "LeastSquareMethod.h"

using namespace Eigen;
using namespace MyFunc;
using namespace Transform;
using namespace std;

void Information(const Orbit::Kepler_elements &elements);
MatrixXd GenerateSputnikOrbit(TYPE duration);

int main()
{
	TYPE duration = SECINDAY * 0.5;

	MatrixXd sputnik_orbit = GenerateSputnikOrbit(duration);
//	MatrixXd modules = MatrixXd::Zero(1 + num_of_results / 10, 3);
	size_t num_of_results = sputnik_orbit.rows();

	GroundStation ground_station(
		{ 0, deg2rad(18), deg2rad(173) }, PI_HALF - deg2rad(75));
//	MatrixXd observations = MatrixXd::Zero(num_of_results, 3);

	TYPE disp = 3.3 / 60.0; // перевели угловые минуты в градусы

	MyNormalDistribution::param_type random_params(0.0, deg2rad(disp));
	DistributionParamVec random_param_vec(2);
	random_param_vec[0] = random_params;
	random_param_vec[1] = random_params;

	ground_station.SetRandomErrorParams(random_param_vec);
	ground_station.SetDoRandom(false);
	ground_station.Init(num_of_results);

	LeastSquareMethod ls_method;
	//ls_method.SetObservationsError();
	//ls_method.SetModel()

	Vector3d cur_geographic_pos = ground_station.GetGeographicPos();
	MatrixXd fix_positions(num_of_results, 3);

	MatrixXd observed_positions(num_of_results, 4);

	Vector3d sputnik_fix_pos;
//	Vector2d sputnik_horiz_pos;

//	Vector3d result;

	TYPE lambda_start = cur_geographic_pos(2);
	TYPE start_time = 0.0;

	size_t num_of_observations = 0;

	for (size_t sec = 0; sec < num_of_results; sec++)
	{
		sputnik_fix_pos = sputnik_orbit.row(sec).segment(1, VEC_SIZE);
		//if (sec % 10 == 0)
		//{
		//	modules.row(sec / 10) <<
		//		sec,
		//		sputnik_fix_pos.norm(),
		//		sputnik_orbit.row(sec).segment(VEC_SIZE + 1, VEC_SIZE).norm();
		//}

		ground_station.SaveObservation(sputnik_fix_pos, sec);

		if (num_of_observations < ground_station.GetNumOfObservations())
		{
			observed_positions.row(num_of_observations) = sputnik_orbit.row(sec).head(VEC_SIZE + 1);
			num_of_observations = ground_station.GetNumOfObservations();
		}
		
		cur_geographic_pos(2) = lambda_start + StarTime(start_time, sec);
		fix_positions.row(sec) = Geographic2Fix(cur_geographic_pos);
	}

	cout << endl << "Finished" << endl;

//	cout << " * Saving sputnik_orbit" << endl;
//	to_file(sputnik_orbit);
//	to_file(modules);

	cout << " * Saving observations" << endl;
	to_file(ground_station.GetObservations(), false);

	to_file(observed_positions);

//	cout << " * Saving fix_positions" << endl;
//	to_file(fix_positions);

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
//	TYPE alpha_height = 970 + Earth::meanRadius;
//	TYPE pi_height = 40 + Earth::meanRadius;

	TYPE alpha_height = 970 + Earth::meanRadius;
	TYPE pi_height = 40 + Earth::meanRadius;

	TYPE a = (alpha_height + pi_height) / 2.0;
	TYPE e = (alpha_height - pi_height) / (alpha_height + pi_height);

	Orbit::Kepler_elements
		elements = { 0, deg2rad(42), 0, a, e, deg2rad(0) };

	DormanPrinceSolver_fixed solver;
	GravitationField central_field;
	AerodynamicForce aerodynamic_force;
	Sputnik sputnik(elements);

	Information(elements);

	sputnik.SetMass(50);
	sputnik.SetBallisticCoeff(1.4);

	sputnik.Set_t1(duration);
	sputnik.SetInterval(1);

	aerodynamic_force.SetHasRandom(true);

	sputnik.AddForce(&central_field);
	sputnik.AddForce(&aerodynamic_force);

	// TODO: добавить установку интервала 
	// кореляции аэродинамической силы
	solver.SetCorrelationInterval(1.0);
	solver.Run(sputnik);

	cout << endl << "sputnik_orbit generated" << endl;

	return sputnik.GetResult();
}