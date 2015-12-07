#pragma once
#include <vector>
#include "Types.h"

namespace LinearAlgebra{
	typedef std::vector<TYPE> BaseVector;
	typedef std::vector<BaseVector> BaseMatrix;
}

using namespace LinearAlgebra;

class CMatrix;
class CSymmetricMatrix;

class CQuaternion; // ���������� ����� ������������ (����������� ����������)

// ����� ��� ������� ----------------------------------
class CVector : public BaseVector
{
public:
	// constructor ������
	CVector() : BaseVector(){ 
	} 

	// ������ ������ �������� �����
	CVector(int n) : BaseVector(n){ 
	} 

	// ����������� ����� ������� arg
	CVector(const BaseVector &arg) : BaseVector(arg){ 
	} 

	TYPE getElement(int i) const;
	int getSize() const;
	TYPE getLength() const;

	void setElement(int i, TYPE value);
	void setSize(int i);

	CVector operator + (const CVector &arg);
	const CVector operator + (const CVector &arg) const;

	CVector operator * (const TYPE num);
	const CVector operator * (const TYPE num) const;
	TYPE operator * (const CVector &arg);
	CVector operator * (const CMatrix &arg);

	// ��������� ������������
	CVector crossProduct(const CVector &b);

	// ���������� ������� ������������
	CQuaternion operator * (const CQuaternion &Quat);

	CVector rotate(const CVector &e_vec, TYPE phi, const bool radians);
	CVector rotate(CQuaternion &Quat);
};


// ����� ��� ������� ----------------------------------
class CMatrix : protected BaseMatrix
{
public:
	// ������ �����������
	CMatrix() : BaseMatrix(){ 
	}

	// constructor
	CMatrix(int n, int m) : BaseMatrix(){ 
		this->setSize(n, m);
	}

	// ����������� �����
	CMatrix(const CMatrix &arg) : BaseMatrix(arg){ 	
	} 

	TYPE getElement(int i, int j) const;
	int getRowCount() const; // ���������� �����
	int getColCount() const; // ���������� ��������

	bool checkSymmetric() const;
	bool checkSquare() const;

	void setSize(int n, int m);
	void setElement(int n, int m, TYPE value);

	CMatrix flip();
	CMatrix inverse(); // �������� ������� ������� ������

	TYPE detGauss() const;
	bool PositiveDef() const;

	BaseVector &operator [] (int i);
	const BaseVector &operator [] (int i) const;  // ���������, ����� �� ����� ������

	CMatrix operator + (const CMatrix &arg);

	CMatrix operator * (const TYPE num); // ������� �� �����
	CVector operator * (const CVector &arg);
	CMatrix operator * (const CMatrix &arg);

	CMatrix &operator = (const CMatrix &arg);
};

class CSymmetricMatrix : public CMatrix
{
public:
	CSymmetricMatrix() : CMatrix(){
	}

	// �����������
	CSymmetricMatrix(int n) : CMatrix(){
		this->setSize(n, n);
	}

	// ����������� �����
	CSymmetricMatrix(const CMatrix &arg) : CMatrix(arg){
	}

	// �������� ������� ������� ���������
	CMatrix inverse();

	void setElement(int n, int m, TYPE value);
};