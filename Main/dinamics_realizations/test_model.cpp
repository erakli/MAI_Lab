#include "file_output.h"

#include "pendulum.h"

void Mathematical(TDormanPrince &Integrator);
void Spring(TDormanPrince &Integrator);

int main(){

	TDormanPrince Integrator;

	cout << " * * * Basic laws of physics * * *\n\n";

	bool cont;
	do
	{
		cout << "What pendulum are we testing? (Mathematical/String) ";
		int bMath;
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



}	// end of Spring(...)