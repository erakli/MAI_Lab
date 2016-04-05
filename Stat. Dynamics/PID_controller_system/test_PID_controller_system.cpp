#include "file_output.h"

#include "PID_model.h"
#include "Dorman-Prince_modified.h"


int main()
{
	CDormanPrince_modified Integrator;

	Integrator.setEps_Max(1.0e-7); // задали максимально допустимую погрешность

	// инициализировали модель
	CPID_controller
		//Model(hWnd);
		Model;

	TYPE t = 500;

	Model.set_t1(t);
	Model.setInterval(0.1); // интервал выдачи

	TYPE omega = 1.0e+3;	// частота генерации Белого Шума

	Model.Generate_WhiteNoise(omega);

	// информируем интегратор о величине интервала корреляции
	Integrator.set_correlation_interval(Model.get_correlation_interval());

	// запускаем интегрирование
	Integrator.Run(Model);

	// делаем вывод результатов в файл
	to_file(Model.getResult());
}