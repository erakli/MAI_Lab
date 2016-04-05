#pragma once
#include "Model.h"

#define SIZE 7

class TIntegrator{
protected:
	TYPE Step, t;
	CModel *Model;
public:
	virtual ~TIntegrator(){}

	TIntegrator();

	TYPE getStep() const;
	void setStep(const TYPE &arg);

	virtual void Run(CModel &Mod) = 0; // pure virtual function
};

class CDormanPrince : public TIntegrator{
protected:
	CVector
		c,				// вектор-столбец слева от таблицы
		b,				// вектор-строка снизу таблицы
		b1;				// вектор-строка ниже b
	CMatrix A;			// так называемая нижне тругольная матрица Бутчера
	CVector k[SIZE];	// вспомогательные коэффициенты

	TYPE
		Error,		// Относительная вычислительная ошибка (локальная погрешность)
		Eps_Max,	// максимальная относительная вычислительная ошибка 
		Eps_Global;

	CVector 
		x0,			// начальные значения
		x1, _x1;	// конечные для шага (4 и 5 порядка)

	int x_size;		// длина вектора начальных значений

	TYPE RoundErr;

	virtual TYPE StepCorrection(); // управление длиной шага интегрирования
	void getError(); 
	TYPE RoundingError() const;

	void set_k(int size);

	CVector thick_extradition(TYPE &Teta, TYPE &Step); // плотная выдача

	void set_c();
	void setA();
	void set_b();
	void set_b1();

	unsigned int iter; // счётчик количества итераций

public:

	CDormanPrince();
	void Run(CModel &Mod) override;

	void setEps_Max(const TYPE &arg);
	void setEps(const TYPE &arg);

	TYPE getEps_Max() const;
	TYPE getEps_Global() const;
	TYPE get_iter() const;
};