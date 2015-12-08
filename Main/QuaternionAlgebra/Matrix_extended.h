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

class CQuaternion; // подключили класс кватернионов (опережающая декларация)

// класс для вектора ----------------------------------
class CVector : public BaseVector
{
public:
	// constructor пустой
	CVector() : BaseVector(){ 
	} 

	// создаём вектор заданной длины
	CVector(int n) : BaseVector(n){ 
	} 

	// конструктор копии вектора arg
	CVector(const BaseVector &arg) : BaseVector(arg){ 
	} 

	TYPE getElement(int i) const;
	int getSize() const;
	TYPE getLength() const;

	void setElement(int i, TYPE value);
	void setSize(int i);

	void Normalize();

	CVector operator + (const CVector &arg);
	const CVector operator + (const CVector &arg) const;

	CVector operator * (const TYPE num);
	const CVector operator * (const TYPE num) const;
	TYPE operator * (const CVector &arg);
	CVector operator * (const CMatrix &arg);

	// векторное произведение
	CVector crossProduct(const CVector &b);

	// реализация алгебры кватернионов
	CQuaternion operator * (const CQuaternion &Quat);

	CVector rotate(const CVector &e_vec, TYPE phi, const bool radians);
	CVector rotate(CQuaternion &Quat);
};


// класс для матрицы ----------------------------------
class CMatrix : protected BaseMatrix
{
public:
	// путсой конструктор
	CMatrix() : BaseMatrix(){ 
	}

	// constructor
	CMatrix(int n, int m) : BaseMatrix(){ 
		this->setSize(n, m);
	}

	// конструктор копии
	CMatrix(const CMatrix &arg) : BaseMatrix(arg){ 	
	} 

	TYPE getElement(int i, int j) const;
	int getRowCount() const; // количество строк
	int getColCount() const; // количество столбцов

	bool checkSymmetric() const;
	bool checkSquare() const;

	void setSize(int n, int m);
	void setElement(int n, int m, TYPE value);

	CMatrix flip();
	CMatrix inverse(); // обратная матрица методом Гаусса

	TYPE detGauss() const;
	bool PositiveDef() const;

	BaseVector &operator [] (int i);
	const BaseVector &operator [] (int i) const;  // проверить, нужна ли здесь ссылка

	CMatrix operator + (const CMatrix &arg);

	CMatrix operator * (const TYPE num); // матрица на число
	CVector operator * (const CVector &arg);
	CMatrix operator * (const CMatrix &arg);

	CMatrix &operator = (const CMatrix &arg);
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