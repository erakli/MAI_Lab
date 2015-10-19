#pragma once
#include <vector>

namespace LinearAlgebra{
	typedef std::vector<double> BaseVector;
	typedef std::vector<BaseVector> BaseMatrix;
}

using namespace LinearAlgebra;

class TMatrix;
class TSymmetricMatrix;

// класс для вектора ----------------------------------
class TVector : public BaseVector{
public:
	// constructor пустой
	TVector() : BaseVector(){ 
	} 

	// создаём вектор заданной длины
	TVector(int n) : BaseVector(n){ 
	} 

	// конструктор копии вектора arg
	TVector(const BaseVector &arg) : BaseVector(arg){ 
	} 

	double getElement(int i) const;
	int getSize() const;
	double getLength() const;

	void setElement(int i, double value);
	void setSize(int i);

	TVector operator + (const TVector &arg);

	TVector operator * (const double num);
	double operator * (const TVector &arg);
	TVector operator * (const TMatrix &arg);

	// векторное произведение
	TVector crossProduct(const TVector &b);
};


// класс для матрицы ----------------------------------
class TMatrix : protected BaseMatrix{
public:
	// путсой конструктор
	TMatrix() : BaseMatrix(){ 
	}

	// constructor
	TMatrix(int n, int m) : BaseMatrix(){ 
		this->setSize(n, m);
	}

	// конструктор копии
	TMatrix(const TMatrix &arg) : BaseMatrix(arg){ 	
	} 

	double getElement(int i, int j) const;
	int getRowCount() const; // количество строк
	int getColCount() const; // количество столбцов

	bool checkSymmetric() const;
	bool checkSquare() const;

	void setSize(int n, int m);
	void setElement(int n, int m, double value);

	TMatrix flip();
	TMatrix inverse(); // обратная матрица методом Гаусса

	double detGauss() const;
	bool PositiveDef() const;

	BaseVector &operator [] (int i);
	const BaseVector &operator [] (int i) const;

	TMatrix operator + (const TMatrix &arg);

	TMatrix operator * (const double num); // матрица на число
	TVector operator * (const TVector &arg);
	TMatrix operator * (const TMatrix &arg);

	TMatrix &operator = (const TMatrix &arg);
};

class TSymmetricMatrix : public TMatrix{
public:
	TSymmetricMatrix() : TMatrix(){
	}

	// конструктор
	TSymmetricMatrix(int n) : TMatrix(){
		this->setSize(n, n);
	}

	// конструктор копии
	TSymmetricMatrix(const TMatrix &arg) : TMatrix(arg){
	}

	// обратная матрица методом Холецкого
	TMatrix inverse();

	void setElement(int n, int m, double value);
};