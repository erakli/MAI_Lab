#include "file_output.h"

#include "pendulum.h"

void Mathematical(CDormanPrince &Integrator);
void Spring(CDormanPrince &Integrator);

void Set_Periods(TYPE &num);

int main(){

	CDormanPrince Integrator;

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

// Тестирование математического маятника
void Mathematical(CDormanPrince &Integrator){

	TYPE num_of_rounds = 5; // количество периодов

	TYPE l, ang, m, fad;

	cout << "Testing mathematical pendulum\n\n"
		<< "	Type length: "; cin >> l;

	cout << "	Starting angle: "; cin >> ang;

	cout << "	Mass: "; cin >> m;

	cout << "	Fading coefficient: "; cin >> fad;

	if (fad != 0) Set_Periods(num_of_rounds);

	CMathPendulum MathPendulum(l, ang, m, fad);

	MathPendulum.set_t1(MathPendulum.Period * num_of_rounds);

	Integrator.Run(MathPendulum);

	CMatrix Result(MathPendulum.getResult());
	Dorman_to_file(Result, Integrator, false);

}	// end of Mathematical(...)

// Тестирование пружинного маятника
void Spring(CDormanPrince &Integrator){

	TYPE num_of_rounds = 5; // количество периодов

	TYPE StartPos, mass, k, coeff(0);
	bool bForceType(false), bFriction;

	cout << "Testing spring pendulum\n\n"
		<< "	Starting position: "; cin >> StartPos;

	cout << "	Mass: "; cin >> mass;

	cout << "	Elasticity coefficient (200 N/m for example): "; cin >> k;

	cout << "\n	Is there friction force? "; cin >> bFriction;

	// формируем коэффициент для одной из сил трения
	if (bFriction)
	{
		cout << "		Friction force type (slide - 0/viscous - 1): ";
		cin >> bForceType;

		if (!bForceType)
			cout << "		Friction coefficient (0.15..0.20 metal on metal): ";
		else
			cout << "		Fading coefficient (0.2 for \"water\", 0.01 for \"air\"): ";

		cin >> coeff;

		Set_Periods(num_of_rounds);
	}

	CSpringPendulum SpringPendulum(StartPos, mass, k, coeff, bForceType);

	SpringPendulum.set_t1(SpringPendulum.Period * num_of_rounds);

	Integrator.Run(SpringPendulum);

	CMatrix Result(SpringPendulum.getResult());
	Dorman_to_file(Result, Integrator);

}	// end of Spring(...)

// Дополнительная функция для задания количества периодов
void Set_Periods(TYPE &num){
	cout << "\n	Type number of pendulum's motion periods (0 - automaticaly): ";
	cin >> num;

	if (num <= 0) num = 10;
}