#include "file_output.h"
#include <iostream>
#include "DormanPrinceSolver.h"
#include "ArenstorfModel.h"

using namespace std;



class TestModel : public Model
{
public:
	TestModel()
	{
		SetStartValuesSize(1, 1);
	}

	Eigen::VectorXd GetRight(const Eigen::VectorXd &X, TYPE t) const
	{
		Eigen::VectorXd res(1);
		res << exp(t);
		return res;
	}
};



int main()
{
	// ------------------------------------------------------------ Интерфейс
	cout << "Integrating with Dorman and Prince (4(5) order)\n\n"
		<< "Please, choose type of an Aristorf's orbit (0 - small, other - big): ";
	int orbit; 
	cin >> orbit;
	// ------------------------------------------------------------ Интерфейс

	DormanPrinceSolver Dorman;

	Dorman.SetStep(1.0e-3);  // задали величину шага
	Dorman.SetEpsMax(1.0e-17); // задали максимально допустимую погрешность
//	Dorman.setEps(1.0e-5); // задали начальную погрешность


	Eigen::MatrixXd res(100, 2);
	TYPE t;
	for (int i = 0; i < 100; i++)
	{
		t = i / 10.0;
		res.row(i) << t, exp(t);
	}
	to_file(res);

	TestModel test_model;
	test_model.Set_t1(10);
	test_model.SetInterval(0.1);
	Dorman.Run(test_model);
	to_file(test_model.GetResult());


	// инициализировали модель (в скобках тип орбиты)
	ArenstorfModel Model(orbit);
	//TTestModel Model;
	
	Model.Set_t1(Model.m_period * 5); // проверяем устойчивость на 5 периодов
	Model.SetInterval(0.1); // интервал выдачи

	// ------------------------------------------------------------ Интерфейс
	cout << "Starting values:\n" << "	Eps_Max = " << Dorman.GetEpsMax() <<
		"\n	orbit type (small/big) = " << orbit << 
		"\n	t1 = " << Model.Get_t1() << "\n";
	//Sleep(DELAY);
	cout << "\n\nProcess started";
	// ------------------------------------------------------------ Интерфейс

	try
	{
		// запускаем интегрирование
		Dorman.Run(Model);
	}
	catch (exception &e)
	{
		cerr << "\n	" << e.what() << "\n";
	}

	// делаем вывод результатов в файл
	Eigen::MatrixXd Result(Model.GetResult());

	Dorman_to_file(Result, Dorman);
};