#include <iostream>

#include "file_output.h"

#include "ShapingFilter.h"
#include "Dorman-Prince_modified.h"
#include "StatAnalysis.h"

using namespace std;

void MainProcess(
	CShapingFilter& Model, CDormanPrince_modified& Integrator, TYPE omega)
{
	TYPE t, interval;

	cout << "Define time of modelling: "; cin >> t; cout << endl;
	Model.set_t1(t);

	Model.Generate_WhiteNoise(omega);

	// информируем интегратор о величине интервала корреляции
	Integrator.set_correlation_interval(Model.get_correlation_interval());

	cout << "White Noise is generated" << endl;

	cout << "What about output interval (sec)? "; cin >> interval; cout << endl;
	Model.setInterval(interval); // интервал выдачи

	cout << endl << "Modelling started..." << endl;

	// запускаем интегрирование
	Integrator.Run(Model);

	cout <<
		"Modelling has been ended. Realization of Random proccess was obtained.\n"
		<< endl;

	// сохраняем реализацию полученного процесса
	CVector realization = Model.getResult().flip()[3];

	cout << endl;
	cout << "Analysing of realization" << endl;

	TYPE beta;
	cout << "Type in reliability level: "; cin >> beta; cout << endl;

	// займёмся анализом
	CStatAnalyzer analyzer(&realization);

	auto mean = analyzer.MeanEstimation();
	auto mean_borders = analyzer.MeanToleranceInterval(beta);

	cout << "Mean estimation is " << mean << endl;
	cout << "Mean tolearnce borders is ("
		<< mean_borders[0] << "; " << mean_borders[1] << ")\n" << endl;

	auto var = analyzer.VarEstimation();
	auto var_borders = analyzer.VarToleranceInterval(beta);

	cout << "Variance estimation is " << var << endl;
	cout << "Variance tolearnce borders is ("
		<< var_borders[0] << "; " << var_borders[1] << ")\n" << endl;

	cout << " - File 1 opened: realization" << endl;
	to_file(realization);

	cout << " - File 2 opened: correlation function estimation" << endl;
	to_file(analyzer.CorrelationFcnEstimation());

	cout << " - File 3 opened: normalized correlation function"
		<< " estimation and it's tolearnce borders" << endl;
	CMatrix NormCorrelation;
	NormCorrelation.push_back(analyzer.NormCorrelationFcnEstimation());
	NormCorrelation.add_toEnd(analyzer.NormCorrelationFcnToleranceInterval(beta));
	to_file(NormCorrelation.flip());

	cout << " - File 4 opened: reference correlation function" << endl;
	to_file(
		CShapingFilter::getReferenceCorrelationFcn(
			interval, NormCorrelation[0].size()
			)
		);

	auto probability = analyzer.getAcceptedCorrEst() / TYPE(NormCorrelation[0].size());

	cout << "\nProbability of true correlation estimates hit tolerance interval: " 
		<< probability << endl;
}

int main()
{
	cout << "* * * Modelling of ShapingFilter * * *"
		<< endl << endl;

	CDormanPrince_modified Integrator;

	Integrator.setEps_Max(1.0e-13); // задали максимально допустимую погрешность

	// инициализировали модель
	CShapingFilter Model;

	TYPE omega = 1.0e+3;	// частота генерации Белого Шума

	// цикл интерфейса взаимодейтсивя с программой
	int repeat(0);
	do
	{
		MainProcess(Model, Integrator, omega);

		cout << endl << "	Repeat modelling? "; cin >> repeat; cout << endl;
	} while (repeat);

}