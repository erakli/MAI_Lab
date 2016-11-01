#include "ShapingFilter.h"
#include "DormanPrinceSolver_fixed.h"

#include "file_output.h"

using namespace std;

int main()
{
	ShapingFilter shaping_filter;
	DormanPrinceSolver_fixed integrator;
	TYPE omega = 1.0e+3;	// частота генерации Белого Шума

	shaping_filter.setInterval(1);
	shaping_filter.set_t1(1000);
	shaping_filter.Generate_WhiteNoise(omega);

	integrator.setEps_Max(1.0e-13);
	integrator.SetCorrelationInterval(shaping_filter.GetCorrelationInterval());

	integrator.Run(shaping_filter);

	to_file(shaping_filter.getResult());
}