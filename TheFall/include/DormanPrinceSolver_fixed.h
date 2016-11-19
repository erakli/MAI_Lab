#pragma once

#include "DormanPrinceSolver.h"

class DormanPrinceSolver_fixed : public DormanPrinceSolver
{
private:
	// интервал корреляции, в котором мы имеем постоянное значение реализации Случайного Процесса
	TYPE correlation_interval;

	/* 
		Перегружаем коррекцию шага, чтобы она удовлетворяла условиям 
		формирования белого шума
	*/
	TYPE StepCorrection(TYPE Error) override;
	TYPE GetError() override;
public:
	DormanPrinceSolver_fixed();
	DormanPrinceSolver_fixed(TYPE correlation_interval);

	void SetCorrelationInterval(TYPE correlation_interval);
	TYPE GetCorrelationInterval() const;
};