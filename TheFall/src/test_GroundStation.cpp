#include <iostream>

#include <Constants.h>
#include "Functions.h"

#include "DormanPrinceSolver_fixed.h"
#include "file_output.h"

#include "Time.h"		// дл€ макросов времени
#include "Coordinates.h"
#include "SolarSystem.h"

#include "Gravitation.h"
#include "AerodynamicForce.h"
#include "Sputnik.h"

#include "GroundStation.h"

#include "LeastSquareMethod.h"

#define LSM_TEST
//#define TEST

using namespace Eigen;
using namespace MyFunc;
using namespace Transform;
using namespace std;

void Information(const Orbit::Kepler_elements &elements);
MatrixXd GenerateSputnikOrbit(TYPE duration);

int main()
{
	TYPE duration = SECINDAY * 3;

	TYPE stddev = 3.3 / 60.0; // перевели угловые минуты в градусы

	MyNormalDistribution::param_type random_params(0.0, deg2rad(stddev));
	DistributionParamVec random_param_vec({ random_params, random_params });

	GroundStation ground_station(
		{ 0, deg2rad(18), deg2rad(173) }, PI_HALF - deg2rad(75));

#ifdef LSM_TEST
	VectorXd initial_condition;
	VectorXd true_initial_condition;
	ObservationSessionsVector observation_sessions_vec;
#endif

	{
		MatrixXd sputnik_orbit = GenerateSputnikOrbit(duration);
		size_t num_of_results = sputnik_orbit.rows();

		ground_station.SetRandomErrorParams(random_param_vec);
		ground_station.SetDoRandom(false);
		ground_station.Init(num_of_results);

		Vector3d sputnik_fix_pos;

		for (size_t sec = 0; sec < num_of_results; sec++)
		{
			sputnik_fix_pos = sputnik_orbit.row(sec).head(VEC_SIZE);
			ground_station.SaveObservation(sputnik_fix_pos, sec, sec);
		}

		cout << endl << "Finished" << endl;

		//cout << " * Saving sputnik_orbit" << endl;
		//to_file(sputnik_orbit);
		//to_file(modules);

		cout << " * Saving observations" << endl;
		to_file(ground_station.GetObservations(), false);

#ifdef LSM_TEST
		cout << endl << "Started LSM" << endl;

		observation_sessions_vec =
			ground_station.GetObservationSessionsVector();

		// берЄм вектор состо€ни€ на первый момент наблюдений и слегка варьируем
		true_initial_condition =
			sputnik_orbit.row(observation_sessions_vec.front().start_moment);

		initial_condition = true_initial_condition;
		//Orbit::Kepler_elements another_elements = Orbit::Decart2Kepler(true_initial_condition);
		//another_elements.a += another_elements.a * 1.0e-2;
		//initial_condition = Orbit::Kepler2Decart(another_elements);
#endif
	}

#ifdef LSM_TEST
	VectorXd observations_disp_vec(2);
	observations_disp_vec <<
		//deg2rad(pow(stddev, 2)),
		//deg2rad(pow(stddev, 2));
		1.0, 1.0;	// TODO: временно убрали ошибки измерений

	GravitationField central_field;
	AerodynamicForce aerodynamic_force;
	Sputnik sputnik;

	sputnik.SetMass(50);
	sputnik.SetBallisticCoeff(1.4);

	aerodynamic_force.SetHasRandom(false);

	sputnik.AddForce(&central_field);
	sputnik.AddForce(&aerodynamic_force);
	sputnik.SetInterval(1.0);
	sputnik.SetDisableStopCalculation(true);

	GroundStation observation_model(ground_station);
	observation_model.SetDoRandom(false);

	LeastSquareMethod ls_method;
	ls_method.SetInitialCondition(initial_condition);
	ls_method.SetObservations(ground_station.GetObservations());
	ls_method.SetObservationsError(observations_disp_vec);
	ls_method.SetModel(&sputnik);
	ls_method.SetObservationModel(&observation_model);
	ls_method.SetObservationSessionsVec(observation_sessions_vec);

	Vector6d stop_condition;
	stop_condition <<  2.0, 2.0, 2.0, 0.1, 0.1, 0.1;

	MatrixXd log_matrix = ls_method.Run(stop_condition);

	VectorXd res_initial_condition = ls_method.GetInitialCondition();

	cout << " * Saving log_matrix" << endl;
	to_file(log_matrix);

	MatrixXd initial_together(3, initial_condition.size());
	initial_together <<
		true_initial_condition.transpose(),
		initial_condition.transpose(),
		res_initial_condition.transpose();

	cout << " * Saving initial_conditions" << endl;
	to_file(initial_together);
#endif

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

#ifdef TEST
	Vector6d X = Orbit::Kepler2Decart(elements);
	Orbit::Kepler_elements another_elements = Orbit::Decart2Kepler(X);
	Vector6d X2 = Orbit::Kepler2Decart(another_elements);

	Information(elements);
	cout << "Result X: " << X.transpose() << endl;
	Information(another_elements);
	cout << "Result X2: " << X2.transpose() << endl;
#endif

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
	// корел€ции аэродинамической силы
//	solver.SetCorrelationInterval(1.0);
	solver.SetEpsMax(1.0e-13);
	solver.Run(sputnik);

	cout << endl << "sputnik_orbit generated" << endl;

	return sputnik.GetResult(false);
}