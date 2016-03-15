#pragma once
//#include <vector>

//#include <exception>
#include <math.h>
#include "Types.h"

//namespace LinearAlgebra{
//	typedef std::vector<TYPE> BaseVector;
//	typedef std::vector<BaseVector> BaseMatrix;
//}
//
//using namespace LinearAlgebra;

class CMatrix;
class CSymmetricMatrix;

// класс для вектора ----------------------------------
class CVector
{
private:
	pTYPE elements;
	UINT size;

public:
	// constructor пустой
	CVector();

	// создаём вектор заданной длины
	CVector(UINT n);

	// конструктор копии вектора arg
	CVector(const CVector &arg);

	~CVector();

	TYPE &operator [] (UINT i);
	const TYPE &operator [] (UINT i) const;  // проверить, нужна ли здесь ссылка

	TYPE getElement(UINT i) const;
	UINT getSize() const;
	TYPE getLength() const;

	void setElement(UINT i, TYPE value);
	void setSize(UINT newSize);

	CVector operator + (const CVector &arg);
	//const CVector operator + (const CVector &arg) const;

	CVector operator * (const TYPE num);
	//const CVector operator * (const TYPE num) const;
	TYPE operator * (const CVector &arg);
	CVector operator * (const CMatrix &arg);

	CVector &operator = (const CVector &right);

	// векторное произведение
	CVector crossProduct(const CVector &b) const;
};


typedef CVector* pVector;

// класс для матрицы ----------------------------------
class CMatrix
{
private:
	pVector elements;
	UINT rowCount, colCount;

public:
	// путсой конструктор
	CMatrix();

	// constructor
	CMatrix(UINT n, UINT m);

	// конструктор копии
	CMatrix(const CMatrix &arg); // проверить

	~CMatrix();

	TYPE getElement(UINT i, UINT j) const;
	UINT getRowCount() const; // количество строк
	UINT getColCount() const; // количество столбцов

	bool checkSymmetric() const;
	bool checkSquare() const;

	void setSize(UINT n, UINT m); // закончить
	void setElement(UINT n, UINT m, TYPE value);

	CMatrix flip();
	CMatrix inverse() const; // обратная матрица методом Гаусса

	TYPE detGauss() const;
	bool PositiveDef() const;

	// проверить
	CVector &operator [] (UINT i);
	const CVector &operator [] (UINT i) const; 

	CMatrix operator + (const CMatrix &arg);

	CMatrix operator * (const TYPE num); // матрица на число
	CVector operator * (const CVector &arg);
	CMatrix operator * (const CMatrix &arg);

	CMatrix &operator = (const CMatrix &right);
};

class CSymmetricMatrix : public CMatrix
{
public:
	CSymmetricMatrix() : CMatrix(){
	}

	// конструктор
	CSymmetricMatrix(int n) : CMatrix(){
		this->setSize(n, n);
	}

	// конструктор копии
	CSymmetricMatrix(const CMatrix &arg) : CMatrix(arg){
	}

	// обратная матрица методом Холецкого
	CMatrix inverse();

	void setElement(int n, int m, TYPE value);
};