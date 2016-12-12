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
#define INITIALS
#define EVOLUTION
#define FALLING

using namespace Eigen;
using namespace MyFunc;
using namespace Transform;
using namespace std;

void Information(const Orbit::Kepler_elements &elements);
MatrixXd GenerateSputnikOrbit(TYPE duration);
MatrixXd GenerateSputnikOrbit(const VectorXd& initial_conditions, TYPE t0, TYPE t1, bool with_time = false);

int main()
{
	TYPE duration = SECINDAY * 30;

	TYPE stddev =
		//0.5;
		3.3 / 60.0; // перевели угловые минуты в градусы

	MyNormalDistribution::param_type random_params(0.0, deg2rad(stddev));
	DistributionParamVec random_param_vec({ random_params, random_params });

	GroundStation ground_station(
		{ 0, deg2rad(18), deg2rad(173) }, PI_HALF - deg2rad(75));

#ifdef LSM_TEST
	VectorXd initial_condition;
	VectorXd true_initial_condition;
	ObservationSessionsVector observation_sessions_vec;
#endif

//	{
		MatrixXd sputnik_orbit = GenerateSputnikOrbit(duration);
		size_t num_of_results = sputnik_orbit.rows();

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

		//cout << " * Saving sputnik_orbit" << endl;
		//to_file(sputnik_orbit);

		//cout << " * Saving observations" << endl;
		//to_file(ground_station.GetObservations(), false);

#ifdef LSM_TEST
		cout << endl << "Started LSM" << endl;

		ObservationSession lsm_start_session = ground_station.GetObservationSessionsVector().front();

		// берЄм только последнее измерение
		observation_sessions_vec.assign(
			1, lsm_start_session);

//		observation_sessions_vec = ground_station.GetObservationSessionsVector();
		//ObservationSession lsm_start_session = observation_sessions_vec.front();

		// берЄм вектор состо€ни€ на первый момент наблюдений и слегка варьируем
		true_initial_condition =
			sputnik_orbit.row(lsm_start_session.start_moment);

		//Vector6d init_delta;
		//init_delta << 11.0, -4.0, -12.0, -0.01, 0.003, -0.007;

		//initial_condition = true_initial_condition;
//		initial_condition += init_delta;

		Orbit::Kepler_elements another_elements = Orbit::Decart2Kepler(true_initial_condition);
		another_elements.a += another_elements.a * 1.0e-2;
		another_elements.e -= another_elements.e * 1.0e-2;
		another_elements.i += another_elements.i * 1.0e-2;
		another_elements.omega += another_elements.omega * 1.0e-3;
		another_elements._Omega -= another_elements._Omega * 1.0e-3;
		another_elements.teta += another_elements.teta * 1.0e-3;
		initial_condition = Orbit::Kepler2Decart(another_elements);
#endif
//	}

#ifdef LSM_TEST
	VectorXd observations_disp_vec(2);
	observations_disp_vec <<
		pow(deg2rad(stddev), 2),
		pow(deg2rad(stddev), 2);
		//1.0, 1.0;	// TODO: временно убрали ошибки измерений

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
	sputnik.SetStart(initial_condition);

#ifdef TEST
	DormanPrinceSolver_fixed solver;

	sputnik.Set_t0(observation_sessions_vec.front().start_moment);
	sputnik.Set_t1(observation_sessions_vec.back().end_moment);

	solver.SetCorrelationInterval(1.0);
	//solver.SetEpsMax(1.0e-13);
	solver.Run(sputnik);

	to_file(sputnik_orbit);
	to_file(sputnik.GetResult());
	return 0;
#endif

	GroundStation observation_model(ground_station);
	observation_model.SetDoRandom(false);

	LeastSquareMethod ls_method;
	ls_method.SetInitialCondition(initial_condition);
	// TODO: возьмЄм только последний участок измерений
	ls_method.SetObservations(ground_station.GetObservations().topRows(lsm_start_session.GetDuration()));
	//ls_method.SetObservations(ground_station.GetObservations());
	ls_method.SetObservationsError(observations_disp_vec);
	ls_method.SetModel(&sputnik);
	ls_method.SetObservationModel(&observation_model);
	ls_method.SetObservationSessionsVec(observation_sessions_vec);


	TYPE pos_delta = 1.0e-6;
	TYPE veloc_delta = 1.0e-6;
	VectorXd delta(6);
	delta << 
		pos_delta, pos_delta, pos_delta, 
		veloc_delta, veloc_delta, veloc_delta;

	ls_method.SetDelta(delta);
	ls_method.SetDeltaObserve(delta * 100.0);

	Vector6d stop_condition;
	stop_condition << 1.0e-3, 1.0e-3, 1.0e-3, 1.0e-3, 1.0e-3, 1.0e-3;

	MatrixXd log_matrix = ls_method.Run(stop_condition);

	VectorXd res_initial_condition = ls_method.GetInitialCondition();

#ifdef LOG_MATRIX
	cout << " * Saving log_matrix" << endl;
	to_file(log_matrix);
#endif

#ifdef INITIALS
	MatrixXd initial_together(3, initial_condition.size());
	initial_together <<
		true_initial_condition.transpose(),
		initial_condition.transpose(),
		res_initial_condition.transpose();

	cout << " * Saving initial_conditions" << endl;
	to_file(initial_together);
#endif

#ifdef EVOLUTION
	MatrixXd initial_evolution;
	initial_evolution.resizeLike(log_matrix);
	initial_evolution.row(0) = log_matrix.row(0) + initial_condition.transpose() - true_initial_condition.transpose();

	for (size_t i = 1; i < initial_evolution.rows(); i++)
	{
		initial_evolution.row(i) = initial_evolution.row(i - 1) + log_matrix.row(i);
	}

	cout << " * Saving initial_evolution" << endl;
	to_file(initial_evolution);
#endif

#ifdef FALLING
	cout << endl << "Modelling fall of sputnik" << endl;

	MatrixXd orbit_result;
	MatrixXd pos_matrix;
	TYPE t0 = lsm_start_session.start_moment;
	TYPE t1 = t0 + SECINDAY * 30;
	TYPE min;
	size_t min_idx;
	VectorXd min_vec;
	Vector3d temp_vec;
	Vector3d fall_coord;

	MatrixXd fall_results(30, 3);
	MatrixXd fall_fix(30, 3);
	//MatrixXd fall_test(30, 3);
	size_t num_of_fall = 0;

	TYPE JD;

	for (size_t i = 0; i < 30; i++)
	{
		cout << endl << "Num of falling - " << i << endl;

		// со временем смоделируем
		orbit_result = 
			GenerateSputnikOrbit(res_initial_condition, t0, t1, true).bottomLeftCorner(15, VEC_SIZE + 1);
		pos_matrix = orbit_result.rightCols(VEC_SIZE);

		min_vec = pos_matrix.rowwise().stableNorm();
		min_vec.array() -= Earth::meanRadius;
		min = min_vec.cwiseAbs().minCoeff(&min_idx);

		cout << "min_idx = " << min_idx << endl;
		cout << "min_vec:" << endl << min_vec << endl;

		temp_vec = pos_matrix.row(min_idx);
		if (min > 0.5)
			continue;

		JD = orbit_result(min_idx, 0) / SECINDAY + J2000;

		fall_fix.row(num_of_fall) = temp_vec;

		fall_coord = Decart2Spher(temp_vec);
		fall_results.row(num_of_fall) = Spher2Geographic(fall_coord, JD);

		num_of_fall++;
	}

	cout << " * Saving fall_results" << endl;
	to_file(MatrixXd(fall_fix.topRows(num_of_fall)));
	to_file(MatrixXd(fall_results.topRows(num_of_fall)));

	fall_results.rightCols(2) *= DEG_IN_RAD;

	VectorXd mean_vec;
	mean_vec = fall_results.rightCols(2).colwise().mean();

	MatrixXd K_matrix(2, 2);
	MatrixXd centered;
	centered = fall_results.rightCols(2).rowwise() - mean_vec.transpose();

	TYPE temp;

	for (size_t i = 0; i < 2; i++)
	{

		for (size_t j = i; j < 2; j++)
		{
			temp = (centered.col(i).array() * centered.col(j).array()).sum();
			K_matrix(i, j) = temp / (num_of_fall - 1);

			if (j != i)
				K_matrix(j, i) = K_matrix(i, j);
		}
	}

//	TYPE corr_coeff = K_matrix(1, 0) / sqrt(K_matrix(0, 0) * K_matrix(1, 1));

	to_file(mean_vec);
	to_file(K_matrix);

#endif

#endif

//	system("pause");
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
		elements = { 0, deg2rad(42), 0, a, e, deg2rad(0) };

	Information(elements);

#ifdef TEST
	//Vector6d X = Orbit::Kepler2Decart(elements);
	//Orbit::Kepler_elements another_elements = Orbit::Decart2Kepler(X);
	//Vector6d X2 = Orbit::Kepler2Decart(another_elements);

	//Information(elements);
	//cout << "Result X: " << X.transpose() << endl;
	//Information(another_elements);
	//cout << "Result X2: " << X2.transpose() << endl;
#endif

	return GenerateSputnikOrbit(Orbit::Kepler2Decart(elements), 0.0, duration);
}



MatrixXd GenerateSputnikOrbit(const VectorXd& initial_conditions, TYPE t0, TYPE t1, bool with_time)
{
	cout << endl << "GenerateSputnikOrbit()" << endl;

	DormanPrinceSolver_fixed solver;
	GravitationField central_field;
	AerodynamicForce aerodynamic_force;
	Sputnik sputnik;

	sputnik.SetStart(initial_conditions);

	sputnik.SetMass(50);
	sputnik.SetBallisticCoeff(1.4);

	sputnik.Set_t0(t0);
	sputnik.Set_t1(t1);
	sputnik.SetInterval(1.0);

	aerodynamic_force.SetHasRandom(true);

	sputnik.AddForce(&central_field);
	sputnik.AddForce(&aerodynamic_force);

	// TODO: добавить установку интервала 
	// корел€ции аэродинамической силы
	solver.SetCorrelationInterval(1.0);
	//	solver.SetEpsMax(1.0e-13);
	solver.Run(sputnik);

	cout << "sputnik_orbit generated" << endl << endl;

	return sputnik.GetResult(with_time);
}