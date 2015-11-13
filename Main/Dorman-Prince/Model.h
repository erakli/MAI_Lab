#pragma once
#include "Matrix_classes.h"
#include "Types.h"

class TModel
{
protected:
	TVector StartValues;
	int s_size; // ����� ������� StartValues
	TYPE 
		Interval, // ������ �� ���� �������� ����� ����. ����� ���?
		t0, t1;
	TMatrix Result;

	// ��������� �������������� ��� ����� ���������� ���������� ����������
	TYPE stop_condition;
	unsigned short int stop_count, stop_count_max;
	bool stop_flag;

public:
	TModel();

	virtual TVector getRight(TVector &X, TYPE t) const = 0;

	void addResult(TVector &X, TYPE t);

	// ������������ � ������ ����
	TVector getStart() const;
	TYPE getInterval() const;
	TYPE get_t0() const;
	TYPE get_t1() const;
	TMatrix getResult() const;

	void setStart(TVector &arg);
	void setInterval(const TYPE &arg);
	void set_t0(const TYPE &arg);
	void set_t1(const TYPE &arg);

	virtual bool Stop_Calculation(TYPE t, TYPE Step, TVector &PrevStep, TVector &CurStep) = 0;

};

class TArenstorfModel : public TModel
{
private:
	TYPE m, M;
public:
	TYPE Period;  // ������ ��������� ���������� ������
	int orbit; // ����� ������ (�����/�������)

	TArenstorfModel(int variant);
	TVector getRight(TVector &X, TYPE t) const;

	// ��������
	bool Stop_Calculation(TYPE t, TYPE Step, TVector &PrevStep, TVector &CurStep){ return false; };
};