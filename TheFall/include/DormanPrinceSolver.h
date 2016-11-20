#pragma once

#include "Integrator.h"
#include "LinearAlgebra.h"

#define SIZE 7

class DormanPrinceSolver : public Integrator
{
protected:
	Eigen::VectorXd
		m_c,				// вектор-столбец слева от таблицы
		m_b,				// вектор-строка снизу таблицы
		m_b1;				// вектор-строка ниже m_b
	Eigen::MatrixXd m_A;	// так называемая нижне тругольная матрица Бутчера
	Eigen::MatrixXd m_k;	// вспомогательные коэффициенты

	TYPE
//		Error,		// Относительная вычислительная ошибка (локальная погрешность)
		m_eps_max,	// максимальная относительная вычислительная ошибка 
		m_eps_global;

	Eigen::VectorXd
		x0,			// начальные значения
		x1, _x1;	// конечные для шага (4 и 5 порядка)

	unsigned x_size;		// длина вектора начальных значений

	TYPE m_rounding_error;

protected:
	virtual TYPE StepCorrection(TYPE Error); // управление длиной шага интегрирования
	virtual TYPE GetError();
	TYPE RoundingError() const;

	void SetK(int size);

	void SaveSubstepResult(TYPE &tout, TYPE delta, TYPE new_step, TYPE t_end);
	Eigen::VectorXd ThickExtradition(TYPE &Teta, TYPE Step); // плотная выдача

	void Set_c();
	void SetA();
	void Set_b();
	void Set_b1();

	unsigned iter; // счётчик количества итераций

public:

	DormanPrinceSolver();
	void Run(Model &model) override;

	void SetEpsMax(TYPE arg);

	TYPE GetEpsMax() const;
	TYPE GetEpsGlobal() const;
	TYPE GetIter() const;
};
