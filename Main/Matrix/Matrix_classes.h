#pragma once
#include <vector>
#include "Types.h"

class CVector;	// проверить на счёт вектора векторов против вектора BaseVector

namespace LinearAlgebra{
	typedef std::vector<TYPE> BaseVector;
	typedef std::vector<CVector> BaseMatrix;	
}

using namespace LinearAlgebra;

class CMatrix;
class CSymmetricMatrix;

// класс для вектора ----------------------------------
class CVector : public BaseVector
{
public:
	// constructor пустой
	CVector();

	// создаём вектор заданной длины
	CVector(int n);

	// конструктор копии вектора arg
	CVector(const BaseVector& arg);

	static void copyPart(CVector &target, const CVector &orig, const int position);
	static CVector copyPart(const CVector &orig, const int position);
	static CVector copyPart(const CVector &orig, const int First, const int Second);

	TYPE getElement(int i) const;
	int getSize() const;
	TYPE getLength() const;

	void insert(const int position, const TYPE value);
	void insert_toEnd(const CVector& additional);

	void setElement(int i, TYPE value);
	void setSize(int i);

	/* Assembler-style functions */
	static void Add(const CVector &source, CVector &destination);
	static void Add(const CVector &source1, const CVector &source2, CVector &destination);

	static void Sub(const CVector &source, CVector &destination);
	static void Sub(const CVector &source1, const CVector &source2, CVector &destination);

	static void Mult(const TYPE num, CVector &destination);
	static void Mult(const TYPE num, const CVector &source, CVector &destination);

	/* Перегрузки опреаторов */
	CVector operator + (const CVector &arg);

	CVector operator * (const TYPE num);
	CVector operator * (const TYPE num) const;
	TYPE operator * (const CVector &arg);
	TYPE operator * (const CVector &arg) const;
	CVector operator * (const CMatrix &arg);

	// векторное произведение
	CVector crossProduct(const CVector &b) const;
};


// класс для матрицы ----------------------------------
class CMatrix : public BaseMatrix
{
public:
	// путсой конструктор
	CMatrix();

	// constructor
	CMatrix(int n, int m);

	// конструктор копии
	CMatrix(const CMatrix& arg);

	TYPE getElement(int i, int j) const;
	int getRowCount() const; // количество строк
	int getColCount() const; // количество столбцов

	bool checkSymmetric() const;
	bool checkSquare() const;

	void setSize(int n, int m);
	void setElement(int n, int m, TYPE value);

	void add_toEnd(const CMatrix &additional);

	CMatrix flip();
	CMatrix inverse() const; // обратная матрица методом Гаусса

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
	CSymmetricMatrix();

	// конструктор
	CSymmetricMatrix(int n);

	// конструктор копии
	CSymmetricMatrix(const CMatrix& arg);

	// обратная матрица методом Холецкого
	CMatrix inverse();

	void setElement(int n, int m, TYPE value);
};