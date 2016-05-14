#include "file_output.h"

#include "PID_model.h"
#include "Dorman-Prince_modified.h"
#include "Stat_linearization.h"

//extern CMatrix coefficients;

int main()
{
#ifdef _DEBUG
	SaturationLinearize Nonlinear;

	auto erf = Nonlinear.erf(0.76);
	auto normcdf = Nonlinear.LaplaceFcn(0);
	auto fg = Nonlinear.J0_integral(0, 1, -2.2, 2.2);

	LinearCoeff coeffs = Nonlinear.getCoefficients(2.2, 0, 1);
#endif

	CDormanPrince_modified Integrator;

	Integrator.setEps_Max(1.0e-13); // задали максимально допустимую погрешность

	// инициализировали модель
	CPID_controller
		//Model(hWnd);
		Model;

	TYPE 
		//t = 10;
		t = 500 * 2;

	Model.set_t1(t);
	Model.setInterval(0.1); // интервал выдачи

	TYPE omega = 1.0e+3;	// частота генерации Белого Шума

	Model.Generate_WhiteNoise(omega);

	// активируем процесс линеаризации
	Model.ModelWithLinearisation(true, false);

	// информируем интегратор о величине интервала корреляции
	Integrator.set_correlation_interval(Model.get_correlation_interval());

	// запускаем интегрирование
	Integrator.Run(Model);

	// делаем вывод результатов в файл
	to_file(Model.getResult());
}