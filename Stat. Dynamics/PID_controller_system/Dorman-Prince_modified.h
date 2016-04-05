#pragma once

#include "Integrator.h"

class CDormanPrince_modified : public CDormanPrince
{
private:
	// интервал корреляции, в котором мы имеем постоянное значение реализации Случайного Процесса
	TYPE correlation_interval;

	/* 
		Перегружаем коррекцию шага, чтобы она удовлетворяла условиям 
		формирования белого шума
	*/
	TYPE StepCorrection() override;
	void getError() override;
public:
	CDormanPrince_modified();
	CDormanPrince_modified(const TYPE correlation_interval);

	void set_correlation_interval(const TYPE correlation_interval);
};