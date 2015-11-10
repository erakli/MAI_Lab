#include "Model.h"

/* * * * * * * * * * TModel * * * * * * * * * */

TModel::TModel(){
	Interval = 0.1; // ��������� �� ������ ����
	t0 = 0;
	t1 = 5;
}

void TModel::addResult(TVector &X, TYPE t){
	int Row = Result.getRowCount();
	TVector compile(s_size + 1); // ������ ���������� + �����

	/*
		�� ��������, ����� ������ ����������, 
		������� ����� ��������� ������ � �������, 
		�� ����������� � � ����
	*/
	Result.setSize(Row + 1, s_size + 1);

	compile[0] = t; // ������ ��������� ��� ����� - ��� �������� �������
	for (int i = 1; i < s_size + 1; i++)
	{
		compile[i] = X[i - 1];
	}

	Result[Row] = compile; // ��������� ������ ������ ���� �������� �������� ������
}

// ----- ��������
TVector TModel::getStart() const{
	return StartValues;
}

TYPE TModel::getInterval() const{
	return Interval;
}

TYPE TModel::get_t0() const{
	return t0;
}

TYPE TModel::get_t1() const{
	return t1;
}

TMatrix TModel::getResult() const{
	return Result;
}

void TModel::setStart(TVector &arg){
	StartValues = arg;
}

void TModel::setInterval(const TYPE &arg){
	Interval = arg;
}

void TModel::set_t0(const TYPE &arg){
	t0 = arg;
}

void TModel::set_t1(const TYPE &arg){
	t1 = arg;
}
// ----- ����� �������


/* * * * * * * * * * TArenstorfModel * * * * * * * * * */

TArenstorfModel::TArenstorfModel(int variant){

	StartValues.setSize(4);
	s_size = StartValues.getSize();

	m = 0.012277471;
	M = 1 - m;

	orbit = variant;

	StartValues[0] = 0.994; // y1
	StartValues[1] = 0;     // y2
	StartValues[2] = 0;     // y1'
	if (orbit) // �������� ������� ������
	{
		StartValues[3] = -2.00158510637908252240537862224; // y2'
		Period = 17.0652165601579625588917206249;
	}
	else // ����� �����
	{
		StartValues[3] = -2.0317326295573368357302057924; // y2'	
		Period = 11.124340337266085134999734047;
	}
}

TVector TArenstorfModel::getRight(TVector &X, TYPE t) const{
	TVector Y(s_size);
	TYPE
		R[2] = 
		{
			pow(pow(X[0] + m, 2) + pow(X[1], 2), 1.5),
			pow(pow(X[0] - M, 2) + pow(X[1], 2), 1.5)
		};

	Y[0] = X[2]; // v1 = y1' - ������ ����������. ����� �������������� ������� y1
	Y[1] = X[3]; // v2 = y2'
	Y[2] = X[0] + 2 * X[3] - M * (X[0] + m) / R[0] - m * (X[0] - M) / R[1];
	Y[3] = X[1] - 2 * X[2] - M * X[1] / R[0] - m * X[1] / R[1];
	return Y; // ��������
}