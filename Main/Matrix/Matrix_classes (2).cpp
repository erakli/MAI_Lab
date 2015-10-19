#include "Matrix_classes.h"
#include <math.h>
#include <string>
#include <algorithm>
//#include <iostream>
//
//using namespace std;
//
//void Show(const TMatrix &arg){
//	cout << "\n";
//	int Row = arg.getRowCount(), Col = arg.getColCount();
//	for (int i = 0; i < Row; i++){
//		for (int j = 0; j < Col; j++)
//		{
//			cout << "	" << arg[i][j];
//		}
//		cout << "\n";
//	}

/*

	нерешённая проблема связана с округлением наименьших разрядов

*/


/* * * * * * * * перегрузки для матриц * * * * * * * */
BaseVector &TMatrix::operator [] (int i){
	return BaseMatrix::operator [] (i);
}

const BaseVector &TMatrix::operator [] (int i) const{
	return BaseMatrix::operator [] (i);
}

TMatrix &TMatrix::operator = (const TMatrix &arg){
	TMatrix Res(arg);
	for (int i = 0; i < getRowCount(); i++)
	{
		(*this)[i] = Res[i];
	}
	return *this;
}


/* * * * * * * * вектор * * * * * * * */
double TVector::getElement(int i) const{
	return (*this)[i];
}

int TVector::getSize() const{
	return size();
}

double TVector::getLength() const{
	double res = 0;
	for (int i = 0; i < getSize(); i++)
		res += pow((*this)[i], 2);
	res = sqrt(res);
	return res;
}

void TVector::setElement(int i, double value){
	(*this)[i] = value;
}

void TVector::setSize(int i){
	this->resize(i, 0); // новые элементы заполняются 0
}

TVector TVector::operator + (const TVector &arg){
	// избыточно, добавить обработчки приёма значения
	int s = std::min<int>
		(getSize(), arg.getSize());
	TVector Res(s);
	for (int i = 0; i < Res.getSize(); i++)
		Res[i] = (*this)[i] + arg[i];
	return Res;
}

TVector TVector::operator * (const double num){
	TVector Res(getSize());
	for (int i = 0; i < getSize(); i++)
		Res[i] = (*this)[i] * num;
	return Res;
}

// скалярное произведение
double TVector::operator * (const TVector &arg){
	int s = std::min<int>
		(getSize(), arg.getSize());
	double sum = 0;
	for (int i = 0; i < s; i++)
		sum += (*this)[i] * arg[i];
	return sum;
}

/*
	произведение вектора-строки на матрицу. 
	в результат уходит вектор-строка длиной 
	по количеству колонок в матрице
*/
TVector TVector::operator * (const TMatrix &arg){
	int size = this->getSize(), n = arg.getColCount();

	if (arg.getRowCount() == size) // равна ли длина вектора высоте матрицы?
	{
		TVector Res(n);
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < size; j++)
			{
				Res[i] += (*this)[j] * arg[j][i];
			}
		}
		return Res;
	}
	else // длина не равна высоте
	{
		return TVector(size); // в результат сбрасывается нулевой вектор
	}
}

// векторное произведение
TVector TVector::crossProduct(const TVector &b){
	int n = 3;
	TVector Res(n), a = *this;
	Res[0] = a[1] * b[2] - a[2] * b[1];
	Res[1] = a[2] * b[0] - a[0] * b[2];
	Res[2] = a[0] * b[1] - a[1] * b[0];
	return Res;
}



/* * * * * * * * матрица * * * * * * * */

double TMatrix::getElement(int i, int j) const{
	return (*this)[i][j];
}

int TMatrix::getRowCount() const{
	return size();
}

int TMatrix::getColCount() const{
	return (getRowCount() > 0) ? (*this)[0].size() : 0;
}

bool TMatrix::checkSymmetric() const{
	int Col = getColCount(), Row = getRowCount();
	bool flag = true;
	if (Col == Row)
	{
		int i = 0, j;
		while ((i < Row) && flag)
		{
			j = i + 1;
			while (j < Col)
			{
				if ((*this)[i][j] != (*this)[j][i]){
					flag = false;
					break;
				}
				j++;
			} // while (j < Col)
			i++;
		} // while ((i < Row) && flag)
	}
	else
	{
		flag = false;
	}
	
	return flag;
}

bool TMatrix::checkSquare() const{
	bool Res;
	(getColCount() == getRowCount()) ? Res = true : Res = false;
	return Res;
}

void TMatrix::setSize(int n, int m){
	this->BaseMatrix::resize(n);
	for (int i = 0; i < n; i++)
		(*this)[i].resize(m);
}

void TMatrix::setElement(int n, int m, double value){
	(*this)[n][m] = value;
}

TMatrix TMatrix::flip(){
	int Col = getColCount(), Row = getRowCount();
	TMatrix Res(Row, Col);
	for (int i = 0; i < Row; i++)
	{
		for (int j = 0; j < Col; j++)
		{ 
			Res[i][j] = (*this)[j][i];
		}
	}
	return Res;
}

// обращение методом Гаусса
TMatrix TMatrix::inverse(){
	/*
		закомментированы вспомогательные проверки промежуточных шагов

	*/
	int n = getRowCount(); // размерность квадратной матрицы
	TMatrix Ed(n, n), Res(*this);

	// заполняем единичную матрицу
	for (int i = 0; i < n; i++)
	{
		Ed[i][i] = 1;
	}

	/* прямой ход */
	for (int i = 0; i < n; i++)
	{
		// равен ли диагональный элемент 1
		if (Res[i][i] != 1)
		{
			double divider; // делитель, равный не-единичному диаг. элементу

			// проверили текущий диагональный элемент на 0
			if (Res[i][i] == 0)
			{
				int k = i + 1;
				while ((Res[k][i] == 0) && (k < n)) k++;

				/* 
					на выходе из цикла в теории может оказаться так, 
					что весь столбец нулевой. такое возможно, и, в
					принципе, надо сделать проброс исключения на этот
					счёт.

					но это лишь означает, что det = 0. Мы собираемся 
					это проверять снаружи, что исключает такую возможность.
					но она есть,  это факт.
					
				*/
				if (Res[k][i] != 0)
				{

					divider = Res[k][i];

					// приводим диагоальный элемент к 1 (делим строку на него)
					for (int p = 0; p < n; p++)
					{
						Res[i][p] += Res[k][p] / divider;
						Ed[i][p] += Ed[k][p] / divider;
						/*cout << "\n - Res"; Show(Res);
						cout << "\n - Ed"; Show(Ed);
						cout << "End step (p = " << p << ")\n";*/
					}
				}
			}
			else // диагональный элемент (!= 0 && != 1)
			{
				divider = Res[i][i];

				// приводим диагоальный элемент к 1 (делим строку на него)
				for (int p = 0; p < n; p++)
				{
					Ed[i][p] /= divider;
					Res[i][p] /= divider;
					/*cout << "\n - Ed"; Show(Ed);
					cout << "\n - Res"; Show(Res);
					cout << "End step (p = " << p << ")\n";*/
				}
			}
		} // приравняли диагональный элемент к 1

		// приводим матрицу к треугольному виду
		for (int j = i + 1; j < n; j++) // вертикальный индекс
		{
			if (double left_side = Res[j][i]) // если сбоку не 0
			{
				for (int p = 0; p < n; p++) // горизонтальный индекс
				{
					/*cout << "\nNew step (j = " << j << ", " << "p = " << p << ")\n";
					cout << "Sboku " << left_side << " Sverhu " << Res[i][p];*/

					if (Ed[i][p]) // если сверху не 0
					{
						Ed[j][p] -= Ed[i][p] * left_side;
						//cout << "\n - Ed"; Show(Ed);
					}

					if (Res[i][p]) // если сверху не 0
					{
						Res[j][p] -= Res[i][p] * left_side;
						//cout << "\n - Res"; Show(Res);
					}
				}
			}
		}
	} // конец прямого хода

	/* обратный ход */
	for (int i = n - 1; i > 0; i--) // диагональный индекс
	{
		for (int j = i - 1; j >= 0; j--) // вертикальный индекс
		{

			if (double right_side = Res[j][i]) // если сбоку не 0
			{
				for (int k = n - 1; k >= 0; k--) // горизонтальный индекс
				{
					/*cout << "\nNew step (j = " << j << ", " << "k = " << k << ")\n";
					cout << "Sboku " << right_side << " Snizu " << Res[i][k];*/

					if (Ed[i][k]) // если снизу не 0
					{
						Ed[j][k] -= Ed[i][k] * right_side;
						//cout << "\n - Ed"; Show(Ed);
					}

					if (Res[i][k]) // если снизу не 0
					{
						Res[j][k] -= Res[i][k] * right_side;
						//cout << "\n - Res"; Show(Res);
					}
				}
			}

		}
	} // конец

	return Ed;
} // конец TMatrix TMatrix::inverse()

// вычисление определителя матрицы по методу Гаусса
double TMatrix::detGauss() const{
	if (checkSquare())
	{
		TMatrix temp = *this;
		
		int n = getRowCount();
		if (n == 1)
		{
			return temp[0][0]; // в случае, если матрица состоит из одного эл-та
		}

		for (int i = 0; i < n; i++)
		{
			if (temp[i][i] == 0)
			{
				int k = i + 1;
				while ((temp[k][i] == 0) && (k < n)) k++;
				if (temp[k][i] != 0)
				{
					for (int p = i; p < n; p++)	temp[i][p] += temp[k][p];
				}
				else
				{
					return 0;
				}
			} // проверили текущий диагональный элемент на 0

			for (int j = n - 1; j >= i; j--)
			{
				for (int p = i + 1; p < n; p++)
				{
					temp[p][j] -= temp[i][j] * (temp[p][i] / temp[i][i]);
				}
			}
		}

		double result = 1;
		for (int i = 0; i < n; i++)
		{
			result *= temp[i][i];
		}
		
		return result;
	}
	else return INFINITY;
}

// определение положительно определённой матрицы
bool TMatrix::PositiveDef() const{
	bool flag = true;
	if (checkSymmetric())
	{
		int n = getRowCount();
		for (int i = 1; (i <= n) && (flag); i++)
		{
			TMatrix temp = *this;
			temp.setSize(i, i);
			if (temp.detGauss() <= 0) flag = false; // у нас неположительно определённая матрица
		}
	}
	else flag = false;

	return flag;
}

TMatrix TMatrix::operator + (const TMatrix &arg){
	int n = arg.getRowCount(), m = arg.getColCount();
	TMatrix Res(n, m);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			// первые [] перегружены нами, а вторые берутся из BaseVector
			Res[i][j] = (*this)[i][j] + arg[i][j];
		}
	}
	return Res;
}

TMatrix TMatrix::operator * (const double num){
	int n = getRowCount(), m = getColCount();
	TMatrix Res(n, m);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			Res[i][j] = (*this)[i][j] * num;
		}
	}
	return Res;
}

TMatrix TMatrix::operator * (const TMatrix &arg){
	int n = getRowCount(), m = arg.getColCount(),
		p = getColCount(), // = RowCount у второй матрицы
		p2 = arg.getRowCount();

	/* избыточно, ввести обработчик */
	if (p == p2) // ширина первой матрицы равна высоте второй?
	{
		TMatrix Res(n, m);
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < m; j++)
				{
					for (int k = 0; k < p; k++)
					{
						Res[i][j] += (*this)[i][k] * arg[k][j];
					}
				}
			}
			return Res;
	}
	else // не равна
	{
		return TMatrix(n, m); // возвращаем нулевую матрицу
	}
	
}


/*
	произведение матрицы на вектор-столбец. (строка на столбец)
	результат - вектор столбец.
*/
TVector TMatrix::operator * (const TVector &arg){
	int n = getRowCount(), m = getColCount(),
		size = arg.getSize(); // длина вектора
	if (size == m) // ширина матрицы свпадает с длиной вектора-столбца?
	{
		TVector Res(n);
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < m; j++)
				{
					Res[i] += (*this)[i][j] * arg[j];
				}
			}
			return Res;
	}
	else // не совпадает
	{
		return TVector(n); // возвращаем нулевой вектор
	}
	
}


/* * * * * * * * Симметричная матрица * * * * * * * */

TMatrix TSymmetricMatrix::inverse(){
	int n = getRowCount(); // размерность квадратной матрицы
	TMatrix matrix_L(n, n);

	matrix_L[0][0] = sqrt((*this)[0][0]);

	/* основной цикл разложения Холецкого */
	for (int i = 1; i < n; i++)
	{	
		matrix_L[i][0] = (*this)[i][0] / matrix_L[0][0]; // вычисляем первый столбец

		// симметричные элементы
		for (int j = 0; j < i; j++)
		{
			double sum = (*this)[i][j]; // временная часть вычисления элемента новой

			for (int p = 0; p < j; p++)
			{
				sum -= matrix_L[i][p] * matrix_L[j][p];
				//cout << "\nsum " << i << " " << p << " = " << sum;
			}
			// остальные симметричные элементы
			matrix_L[i][j] = sum / matrix_L[j][j];
			//cout << "\n - matrix_L"; Show(matrix_L);
		}


		// диагональные элементы
		double sum = (*this)[i][i]; 

		for (int p = 0; p < i; p++)
		{
			sum -= pow(matrix_L[i][p], 2);
		}
		matrix_L[i][i] = sqrt(sum);	// вычислили диагональные элементы
		//cout << "\n - matrix_L"; Show(matrix_L);
	} // окончание основного цикла


	/* вычисление элементов обратной матрицы */
	TSymmetricMatrix Res(n);
	for (int i = n - 1; i >= 0; i--)
	{
		// диагональные элементы
		double sum = 1 / matrix_L[i][i];

		for (int k = i + 1; k < n; k++)
		{
			sum -= matrix_L[k][i] * Res[k][i];
		}

		Res[i][i] = sum / matrix_L[i][i];
		//cout << "\n - Res"; Show(Res);


		// симметрические элменты
		for (int j = i - 1; j >= 0; j--)
		{
			sum = 0;
			for (int k = j + 1; k < n; k++)
			{
				sum += matrix_L[k][j] * Res[k][i];
			}
			Res[j][i] = Res[i][j] = -1 / matrix_L[j][j] * sum;
			//cout << "\n - Res"; Show(Res);
		}
	}

	return Res;
}

void TSymmetricMatrix::setElement(int n, int m, double value){
	(*this)[n][m] = (*this)[m][n] = value;
}