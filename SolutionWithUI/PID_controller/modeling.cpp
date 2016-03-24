#include "modelling.h"

CMatrix PIDModelling(const TYPE t, HWND hWnd){

	CDormanPrince Integrator;

	Integrator.setStep(1.0e-3);  // задали величину шага
	Integrator.setEps_Max(1.0e-17); // задали максимально допустимую погрешность
	Integrator.setEps(1.0e-5); // задали начальную погрешность

	// инициализировали модель
	CPID_controller Model(hWnd);
	//TTestModel Model;

	Model.set_t1(t);
	Model.setInterval(0.1); // интервал выдачи

	// запускаем интегрирование
	Integrator.Run(Model);

	// делаем вывод результатов в файл
	return Model.getResult();

//	Dorman_to_file(Result, Integrator);
}