#include "file_output.h"

#include "pendulum.h"

void Mathematical(TDormanPrince &Integrator);
void Spring(TDormanPrince &Integrator);

int main(){

	TDormanPrince Integrator;

	cout << " * * * Basic laws of physics * * *";

	bool cont;
	do
	{
		bool bMath;
		cout << "\n\nWhat pendulum are we testing? (Mathematical - 0/String - 1) ";
		cin >> bMath; cout << "\n";

		// выбор тестируемого маятника
		(bMath) ? Spring(Integrator) : Mathematical(Integrator);

		cout << "\nContinue? "; cin >> cont;
	} while (cont);

}	// end of main()

void Mathematical(TDormanPrince &Integrator){

	TYPE l, ang, m, fad;

	cout << "Testing mathematical pendulum\n\n"
		<< "	Type length: "; cin >> l;

	cout << "	Starting angle: "; cin >> ang;

	cout << "	Mass: "; cin >> m;

	cout << "	Fading coefficient: "; cin >> fad;


	TMathPendulum MathPendulum(l, ang, m, fad);

	MathPendulum.set_t1(MathPendulum.Period * 5);

	Integrator.Run(MathPendulum);

	TMatrix Result(MathPendulum.getResult());
	Dorman_to_file(Result, Integrator, false);

}	// end of Mathematical(...)

void Spring(TDormanPrince &Integrator){

	TYPE StartPos, mass, k, coeff;
	bool bForceType(false);

	cout << "Testing spring pendulum\n\n"
		<< "	Starting position: "; cin >> StartPos;

	cout << "	Mass: "; cin >> mass;

	cout << "	Elasticity coefficient: "; cin >> k;

	cout << "	Friction coefficient: "; cin >> coeff;

	if (coeff != 0)
	{
		cout << "	Friction force type (slide - 0/viscous - 1): ";
		cin >> bForceType;
	}

	TSpringPendulum SpringPendulum(StartPos, mass, k, coeff, bForceType);

	SpringPendulum.set_t1(SpringPendulum.Period * 5);

	Integrator.Run(SpringPendulum);

	TMatrix Result(SpringPendulum.getResult());
	Dorman_to_file(Result, Integrator, true);

}	// end of Spring(...)