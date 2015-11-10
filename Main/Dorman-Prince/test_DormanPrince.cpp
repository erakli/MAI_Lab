#include "file_output.h"

int main(){
	// ------------------------------------------------------------ Интерфейс
	cout << "Integrating with Dorman and Prince (4(5) order)\n\n"
		<< "Please, choose type of an Aristorf's orbit (0 - small, other - big): ";
	int orbit; 
	cin >> orbit;
	// ------------------------------------------------------------ Интерфейс

	TDormanPrince Dorman;

	Dorman.setStep(1.0e-3);  // задали величину шага
	Dorman.setEps_Max(1.0e-17); // задали максимально допустимую погрешность
	Dorman.setEps(1.0e-5); // задали начальную погрешность

	// инициализировали модель (в скобках тип орбиты)
	TArenstorfModel Model(orbit);
	//TTestModel Model;
	
	Model.set_t1(Model.Period * 5); // проверяем устойчивость на 5 периодов
	Model.setInterval(0.1); // интервал выдачи

	// ------------------------------------------------------------ Интерфейс
	cout << "Starting values:\n" << "	Eps_Max = " << Dorman.getEps_Max() <<
		"\n	orbit type (small/big) = " << orbit << 
		"\n	t1 = " << Model.get_t1() << "\n";
	Sleep(DELAY);
	cout << "\n\nProcess started";
	// ------------------------------------------------------------ Интерфейс

	// запускаем интегрирование
	Dorman.Run(Model); 

	// делаем вывод результатов в файл
	TMatrix Result(Model.getResult());

	Dorman_to_file(Result, Dorman);
};