#include "file_output.h"

#include "pendulum.h"

int main(){

	TYPE l, ang, m;

	cout << "Testing mathematical pendulum"
		<< "/n	Type length: "; cin >> l;

	cout << "/n		Starting angle: "; cin >> ang;

	cout << "/n		Mass: "; cin >> m;


	TDormanPrince Integrator;

	Integrator.setStep(1.0e-3);
	Integrator.setEps_Max(1.0e-17);
	Integrator.setEps(1.0e-5);

	TMathPendulum Model(l, ang, m);

	Model.set_t1(Model.Period * 5);
	Model.setInterval(0.1);

	Integrator.Run(Model);

	TMatrix Result(Model.getResult());

	Dorman_to_file(Result, Integrator);
}