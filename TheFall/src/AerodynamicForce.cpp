#include "AerodynamicForce.h"

#include "Constants.h"
#include <SolarSystem.h>

#include "DormanPrinceSolver_fixed.h"
#include "ShapingFilter.h"
#include <file_output.h>

using namespace Eigen;

//#define CONSOLE_OUTPUT

#ifdef CONSOLE_OUTPUT
#include <iostream>
using namespace std;
#endif

#ifdef DEBUG
#include <list>
std::list<Eigen::VectorXd> aerodynamic_right_parts_list;
#endif


#define CORRELATION_INTERVAL 1.0



DensityModelParams::DensityModelParams()
{
	height = 0.0;
	A = 0.0;
	k1 = 0.0;
	k2 = 0.0;
}



AerodynamicForce::AerodynamicForce()
{
	ballistic_coeff = 0.0;

	SetHasRandom(true);

	density_params[0].height = 0.0;
	density_params[1].height = 20.0 * 1000;
	density_params[2].height = 60.0 * 1000;
	density_params[3].height = 100.0 * 1000;
	density_params[4].height = 150.0 * 1000;
	density_params[5].height = 300.0 * 1000;
	density_params[6].height = 600.0 * 1000;
	density_params[7].height = 900.0 * 1000;

	density_params[0].A = 1.225;
	density_params[1].A = 0.891e-1;
	density_params[2].A = 2.578e-4;
	density_params[3].A = 4.061e-7;
	density_params[4].A = 2.130e-9;
	density_params[5].A = 4.764e-11;
	density_params[6].A = 8.726e-13;
	density_params[7].A = 6.367e-14;

	density_params[0].k1 = -0.2639e-8;
	density_params[1].k1 = 0.4407e-9;
	density_params[2].k1 = -0.2560e-8;
	density_params[3].k1 = 0.1469e-8;
	density_params[4].k1 = 0.8004e-10;
	density_params[5].k1 = 0.7111e-11;
	density_params[6].k1 = 0.1831e-11;
	density_params[7].k1 = 0;

	density_params[0].k2 = 0.7825e-4;
	density_params[1].k2 = 0.16375e-3;
	density_params[2].k2 = 0.5905e-4;
	density_params[3].k2 = 0.1787e-3;
	density_params[4].k2 = 0.3734e-4;
	density_params[5].k2 = 0.1547e-4;
	density_params[6].k2 = 0.9280e-5;
	density_params[7].k2 = 0.9540e-5;
}

AerodynamicForce::AerodynamicForce(bool has_random) : AerodynamicForce()
{
	this->has_random = has_random;
}



void AerodynamicForce::Init(int argc, void** argv)
{
	if (argc != 2)
		return;

	int param_count = *(static_cast<int*>(argv[0]));
	TYPE* params = static_cast<TYPE*>(argv[1]);

	if (param_count != 2)
		return;

	GenerateRandomRealization(params[0]);
	ballistic_coeff = params[1];
}



Vector3d AerodynamicForce::getRight(const Vector6d& X, TYPE t) const
{
	Vector3d pos, veloc;
	pos = X.head(VEC_SIZE);
	veloc = X.tail(VEC_SIZE);

	Vector3d earth_ang_veloc(0.0, 0.0, Earth::angularVeloc);

	Vector3d atmospheric_veloc;
	atmospheric_veloc = veloc - earth_ang_veloc.cross(pos);

	TYPE scalar_part = 
		-atmospheric_veloc.norm() * GetDensity(pos, t) * 
		ballistic_coeff / 2.0 * 
		1.0e+3;

	Vector3d right_part;
	right_part = scalar_part * atmospheric_veloc;

#ifdef DEBUG
//	VectorXd res(4);
//	res << t, right_part;
//	aerodynamic_right_parts_list.push_back(res);
#endif

	return right_part;
}



void AerodynamicForce::SetBallisticCoeff(TYPE new_ballistic_coeff)
{
	ballistic_coeff = new_ballistic_coeff;
}



void AerodynamicForce::SetHasRandom(bool has_random)
{
	this->has_random = has_random;
}



TYPE AerodynamicForce::GetDensity(const Vector3d& X, TYPE t) const
{
	// TODO: перевели в м
	TYPE height = (X.norm() - Earth::meanRadius) * 1000;

	int layer;

	for (layer = 0; layer < ATMO_LAYERS - 1; layer++)
	{
		if (density_params[layer].height > height)
		{
			if (layer > 0)
				layer--;
			break;
		}
	}

	TYPE layer_dist = height - density_params[layer].height;
	TYPE e = exp(
		density_params[layer].k1 * pow(layer_dist, 2) - 
		density_params[layer].k2 * layer_dist
		);
	TYPE density = density_params[layer].A * e;

	if (has_random == true)
	{
		TYPE random = random_process_realization(int(t / CORRELATION_INTERVAL));
		density *= 1 + random;
	}

	// кг/м^3
	return density;
}



void AerodynamicForce::GenerateRandomRealization(TYPE t1)
{
	if (has_random == true)
	{
		ShapingFilter shaping_filter;
		DormanPrinceSolver_fixed integrator;

//		TYPE omega = 2 * PI / CORRELATION_INTERVAL;	// частота генерации Белого Шума
		TYPE omega = 1.0e+1;

		shaping_filter.SetInterval(CORRELATION_INTERVAL);
		shaping_filter.Set_t1(t1 + CORRELATION_INTERVAL + 10);
		shaping_filter.Generate_WhiteNoise(omega);

		TYPE corr_interval = shaping_filter.GetCorrelationInterval();
		integrator.SetCorrelationInterval(corr_interval);

		integrator.Run(shaping_filter);

		random_process_realization = shaping_filter.GetResult().rightCols(1);

#ifdef CONSOLE_OUTPUT
		cout << endl;
		cout << "shaping_filter.GetResult():" << endl;
		cout << shaping_filter.GetResult().topRows(10);
		cout << endl;

		//cout << endl;
		//cout << "random_process_realization:" << endl;
		//cout << random_process_realization.head(10);
		//cout << endl;

		//system("pause");
#endif
	}
}



#ifdef DEBUG
Eigen::MatrixXd AerodynamicForce::GetRightPartsList() const
{
	Eigen::MatrixXd res = Eigen::MatrixXd::Zero(aerodynamic_right_parts_list.size(), 4);
	size_t i = 0;

	for (std::list<Eigen::VectorXd>::const_iterator
		it = aerodynamic_right_parts_list.begin();
		it != aerodynamic_right_parts_list.end();
	++it)
	{
		res.row(i) = *it;
		i++;
	}

	return res;
}
#endif