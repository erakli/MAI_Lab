#include <iostream>

#include "file_output.h"

#include "PID_model.h"
#include "Dorman-Prince_modified.h"
#include "Stat_linearization.h"

using namespace std;

//extern CMatrix coefficients;
#define  TEST
#ifdef TEST
int main()
{
#ifdef _DEBUG
	SaturationLinearize Nonlinear;

	auto erf = Nonlinear.erf(0.76);
	auto normcdf = Nonlinear.LaplaceFcn(0);
	auto fg = Nonlinear.J0_integral(0, 1, -2.2, 2.2);

	LinearCoeff coeffs = Nonlinear.getCoefficients(2.2, 0, 1);
#endif

	cout << "* * * Modelling dynamic system with PID-controller * * *"
		<< endl << endl;

	CDormanPrince_modified Integrator;

	Integrator.setEps_Max(1.0e-13); // задали максимально допустимую погрешность

	// инициализировали модель
	CPID_controller
		//Model(hWnd);
		Model;

	TYPE omega = 1.0e+3;	// частота генерации Белого Шума
	
	// цикл интерфейса взаимодейтсивя с программой
	int repeat(0);
	do
	{
		TYPE t, interval;

		cout << "Define time of modelling: "; cin >> t; cout << endl;
		Model.set_t1(t);

		// если в первый раз моделируем, то создаём реализацию БШ
		if (!repeat)
		{
			Model.Generate_WhiteNoise(omega);

			// информируем интегратор о величине интервала корреляции
			Integrator.set_correlation_interval(Model.get_correlation_interval());

			cout << "White Noise is generated. For this session max modelling time is "
				<< t << endl << endl;
		}

		cout << "What about output interval (sec)? "; cin >> interval; cout << endl;
		Model.setInterval(interval); // интервал выдачи

		int do_linearization, linearization_type(0);

		cout << "Is the system linearized? (0 - no, 1 - yes) ";
		cin >> do_linearization;

		if (do_linearization)
		{
			cout << "Linearization method (0 - First, 1 - Second) ";
			cin >> linearization_type;
		}

		// активируем процесс линеаризации
		Model.ModelWithLinearisation(do_linearization != 0, linearization_type != 0);

		// запускаем интегрирование
		Integrator.Run(Model);

		// делаем вывод результатов в файл
		to_file(Model.getResult());

		cout << endl << "	Repeat modelling? "; cin >> repeat; cout << endl;

	} while (repeat);

}
#endif
