#pragma once
#include "Matrix_classes.h"
#include "Types.h"

class CModel
{
protected:
	CVector StartValues;
	int s_size; // длина вектора StartValues
	TYPE 
		Interval, // должен ли быть интервал между знач. задан тут?
		t0, t1;
	CMatrix Result;

	// Остановка интегрирования при малых изменениях приращения координаты
	TYPE stop_condition;
	unsigned short int stop_count, stop_count_max;
	bool stop_flag;

public:
	CModel();

	virtual CVector getRight(CVector &X, TYPE t) const = 0;

	void addResult(CVector &X, TYPE t);

	// инкапсуляция в чистом виде
	CVector getStart() const;
	TYPE getInterval() const;
	TYPE get_t0() const;
	TYPE get_t1() const;
	CMatrix getResult() const;

	void setStart(CVector &arg);
	void setInterval(const TYPE &arg);
	void set_t0(const TYPE &arg);
	void set_t1(const TYPE &arg);

	virtual bool Stop_Calculation(TYPE t, TYPE Step, CVector &PrevStep, CVector &CurStep) = 0;

};

class TArenstorfModel : public CModel
{
private:
	TYPE m, M;
public:
	TYPE Period;  // Период обращения конкретной орбиты
	int orbit; // Выбор орбиты (малая/большая)

	TArenstorfModel(int variant);
	CVector getRight(CVector &X, TYPE t) const;

	// заглушка
	bool Stop_Calculation(TYPE t, TYPE Step, CVector &PrevStep, CVector &CurStep){ return false; };
};