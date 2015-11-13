#pragma once
#include "Model.h"
#include "Types.h"

#define SIZE 7

class TIntegrator{
protected:
	TYPE Step, t;
	TModel *Model;
public:
	TIntegrator();

	TYPE getStep() const;
	void setStep(const TYPE &arg);

	virtual void Run(TModel &Mod) = 0; // pure virtual function
};

class TDormanPrince : public TIntegrator{
private:
	TVector
		c,  // вектор-столбец слева от таблицы
		b,  // вектор-строка снизу таблицы
		b1;  // вектор-строка ниже b
	TMatrix A;  // так называемая нижне тругольная матрица Бутчера
	TVector k[SIZE];  // вспомогательные коэффициенты

	TYPE
		Eps, // Относительная вычислительная ошибка (локальная погрешность)
		Eps_Max, // максимальная относительная вычислительная ошибка 
		Eps_Global;

	TVector 
		x0, // начальные значения
		x1, _x1; // конечные для шага (4 и 5 порядка)

	int x_size; // длина вектора начальных значений

	void StepCorrection(); // управление длиной шага интегрирования
	void getEps(); 
	TYPE RoundingError();

	void set_k(int size);

	TVector thick_extradition(TYPE &Teta, TYPE &Step); // плотная выдача

	void set_c();
	void setA();
	void set_b();
	void set_b1();

	unsigned int iter; // счётчик количества итераций

public:

	TDormanPrince();
	void Run(TModel &Mod);

	void setEps_Max(const TYPE &arg);
	void setEps(const TYPE &arg);

	TYPE getEps_Max() const;
	TYPE getEps_Global() const;
	TYPE get_iter() const;
};