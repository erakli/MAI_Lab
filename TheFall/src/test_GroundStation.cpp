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

#define LSM_TEST

using namespace Eigen;
using namespace MyFunc;
using namespace Transform;
using namespace std;

void Information(const Orbit::Kepler_elements &elements);
MatrixXd GenerateSputnikOrbit(TYPE duration);

int main()
{
	TYPE duration = SECINDAY * 0.5;

	TYPE stddev = 3.3 / 60.0; // перевели угловые минуты в градусы

	MyNormalDistribution::param_type random_params(0.0, deg2rad(stddev));
	DistributionParamVec random_param_vec({ random_params, random_params });

	MatrixXd sputnik_orbit = GenerateSputnikOrbit(duration);
	size_t num_of_results = sputnik_orbit.rows();

	GroundStation ground_station(
		{ 0, deg2rad(18), deg2rad(173) }, PI_HALF - deg2rad(75));

	ground_station.SetRandomErrorParams(random_param_vec);
	ground_station.SetDoRandom(true);
	ground_station.Init(num_of_results);

	Vector3d sputnik_fix_pos;

	for (size_t sec = 0; sec < num_of_results; sec++)
	{
		sputnik_fix_pos = sputnik_orbit.row(sec).head(VEC_SIZE);
		ground_station.SaveObservation(sputnik_fix_pos, sec, sec);
	}

	cout << endl << "Finished" << endl;

#ifdef LSM_TEST
	cout << endl << "Started LSM" << endl;

	ObservationSessionsVector observation_sessions_vec = 
		ground_station.GetObservationSessionsVector();

	VectorXd initial_condition =
		sputnik_orbit.row(observation_sessions_vec.front().start_moment);

	VectorXd observations_disp_vec(2);
	observations_disp_vec << 
		deg2rad(pow(stddev, 2)),
		deg2rad(pow(stddev, 2));

	GravitationField central_field;
	AerodynamicForce aerodynamic_force;
	Sputnik sputnik;

	sputnik.SetMass(50);
	sputnik.SetBallisticCoeff(1.4);

	aerodynamic_force.SetHasRandom(false);

	sputnik.AddForce(&central_field);
	sputnik.AddForce(&aerodynamic_force);
	sputnik.SetInterval(1.0);

	GroundStation observation_model(ground_station);
	observation_model.SetDoRandom(false);

	LeastSquareMethod ls_method;
	ls_method.SetInitialCondition(initial_condition);
	ls_method.SetObservations(ground_station.GetObservations());
	ls_method.SetObservationsError(observations_disp_vec);
	ls_method.SetModel(&sputnik);
	ls_method.SetObservationModel(&observation_model);
	ls_method.SetObservationSessionsVec(observation_sessions_vec);

	MatrixXd log_matrix = ls_method.Run(3.0);

	initial_condition = ls_method.GetInitialCondition();

	cout << " * Saving log_matrix" << endl;
	to_file(log_matrix);

	cout << " * Saving initial_condition" << endl;
	to_file(initial_condition);
#endif

//	cout << " * Saving sputnik_orbit" << endl;
//	to_file(sputnik_orbit);
//	to_file(modules);

	cout << " * Saving observations" << endl;
	to_file(ground_station.GetObservations(), false);

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

	DormanPrinceSolver solver;
	GravitationField central_field;
	AerodynamicForce aerodynamic_force;
	Sputnik sputnik(elements);

	Information(elements);

	sputnik.SetMass(50);
	sputnik.SetBallisticCoeff(1.4);

	sputnik.Set_t1(duration);
	sputnik.SetInterval(1);

	aerodynamic_force.SetHasRandom(false);

	sputnik.AddForce(&central_field);
	sputnik.AddForce(&aerodynamic_force);

	// TODO: добавить установку интервала 
	// кореляции аэродинамической силы
//	solver.SetCorrelationInterval(1.0);
	solver.SetEpsMax(1.0e-13);
	solver.Run(sputnik);

	cout << endl << "sputnik_orbit generated" << endl;

	return sputnik.GetResult(false);
}