#pragma once
#include <list>
#include "Matrix_classes.h"

// граница количества результатов, с которой начинаем записывать в List
#define LISTLIMIT 1.0e+6

namespace ResultArray
{
	typedef std::list<CVector> List;
}

using namespace ResultArray;

class CModel
{
protected:
	CVector StartValues;

	int
		s_size; // длина вектора StartValues

	TYPE 
		Interval, // должен ли быть интервал между знач. задан тут?
		t0, t1;

	List Result;	// двунаправленный список
	CMatrix Result_Matrix;	// вектор векторов

	/* 
		если используем для хранения результатов матрицу, то считаем последнюю 
		заполненную позицию (на случай преждевременного завершения интегрирования) */
	int result_matrix_position;
	bool large_result_flag;	// если ожидается более 1 млн. позиций результатов, используем List

	// Остановка интегрирования при малых изменениях приращения координаты
	TYPE stop_condition;
	unsigned short int stop_count, stop_count_max;
	bool stop_flag;

public:
	virtual ~CModel(){}

	CModel();

	virtual CVector getRight(const CVector &X, TYPE t) const = 0;

	virtual void addResult(CVector &X, TYPE t);

	// инкапсуляция в чистом виде
	CVector getStart() const;
	TYPE getInterval() const;
	TYPE get_t0() const;
	TYPE get_t1() const;
	CMatrix getResult();

	CVector getLastResult();

	void clearResult();

	/* 
		использовать после задания времени интегрирования и интервала выдачи. 
		определяет, куда будет производиться запись результатов: в List или матрицу */
	void setResultType();

	void setStart(CVector &arg);
	void setInterval(const TYPE &arg);
	void set_t0(const TYPE &arg);
	void set_t1(const TYPE &arg);

	virtual bool Stop_Calculation(TYPE t, TYPE Step, CVector &PrevStep, CVector &CurStep);

};

class TArenstorfModel : public CModel
{
private:
	TYPE m, M;
public:
	TYPE Period;  // Период обращения конкретной орбиты
	int orbit; // Выбор орбиты (малая/большая)

	TArenstorfModel(int variant);
	CVector getRight(const CVector &X, TYPE t) const override;
};