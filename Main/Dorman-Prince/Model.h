#pragma once
#include "Matrix_classes.h"
#include "Types.h"

class TModel
{
protected:
	TVector StartValues;
	int s_size; // длина вектора StartValues
	TYPE 
		Interval, // должен ли быть интервал между знач. задан тут?
		t0, t1;
	TMatrix Result;
public:
	TModel();

	virtual TVector getRight(TVector &X, TYPE t) const = 0;

	void addResult(TVector &X, TYPE t);

	// инкапсуляция в чистом виде
	TVector getStart() const;
	TYPE getInterval() const;
	TYPE get_t0() const;
	TYPE get_t1() const;
	TMatrix getResult() const;

	void setStart(TVector &arg);
	void setInterval(const TYPE &arg);
	void set_t0(const TYPE &arg);
	void set_t1(const TYPE &arg);

};

class TArenstorfModel : public TModel
{
private:
	TYPE m, M;
public:
	TYPE Period;  // Период обращения конкретной орбиты
	int orbit; // Выбор орбиты (малая/большая)

	TArenstorfModel(int variant);
	TVector getRight(TVector &X, TYPE t) const;
};