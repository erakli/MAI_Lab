#pragma once
#include <vector>
#include "Types.h"

namespace LinearAlgebra{
	typedef std::vector<TYPE> BaseVector;
	typedef std::vector<BaseVector> BaseMatrix;
}

using namespace LinearAlgebra;

class TMatrix;
class TSymmetricMatrix;

// ����� ��� ������� ----------------------------------
class TVector : public BaseVector
{
public:
	// constructor ������
	TVector() : BaseVector(){ 
	} 

	// ������ ������ �������� �����
	TVector(int n) : BaseVector(n){ 
	} 

	// ����������� ����� ������� arg
	TVector(const BaseVector &arg) : BaseVector(arg){ 
	} 

	TYPE getElement(int i) const;
	int getSize() const;
	TYPE getLength() const;

	void setElement(int i, TYPE value);
	void setSize(int i);

	TVector operator + (const TVector &arg);

	TVector operator * (const TYPE num);
	TYPE operator * (const TVector &arg);
	TVector operator * (const TMatrix &arg);

	// ��������� ������������
	TVector crossProduct(const TVector &b);
};


// ����� ��� ������� ----------------------------------
class TMatrix : protected BaseMatrix
{
public:
	// ������ �����������
	TMatrix() : BaseMatrix(){ 
	}

	// constructor
	TMatrix(int n, int m) : BaseMatrix(){ 
		this->setSize(n, m);
	}

	// ����������� �����
	TMatrix(const TMatrix &arg) : BaseMatrix(arg){ 	
	} 

	TYPE getElement(int i, int j) const;
	int getRowCount() const; // ���������� �����
	int getColCount() const; // ���������� ��������

	bool checkSymmetric() const;
	bool checkSquare() const;

	void setSize(int n, int m);
	void setElement(int n, int m, TYPE value);

	TMatrix flip();
	TMatrix inverse(); // �������� ������� ������� ������

	TYPE detGauss() const;
	bool PositiveDef() const;

	BaseVector &operator [] (int i);
	const BaseVector &operator [] (int i) const;

	TMatrix operator + (const TMatrix &arg);

	TMatrix operator * (const TYPE num); // ������� �� �����
	TVector operator * (const TVector &arg);
	TMatrix operator * (const TMatrix &arg);

	TMatrix &operator = (const TMatrix &arg);
};

class TSymmetricMatrix : public TMatrix
{
public:
	TSymmetricMatrix() : TMatrix(){
	}

	// �����������
	TSymmetricMatrix(int n) : TMatrix(){
		this->setSize(n, n);
	}

	// ����������� �����
	TSymmetricMatrix(const TMatrix &arg) : TMatrix(arg){
	}

	// �������� ������� ������� ���������
	TMatrix inverse();

	void setElement(int n, int m, TYPE value);
};