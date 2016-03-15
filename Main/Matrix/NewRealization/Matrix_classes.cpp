#include "Matrix_classes.h"
#include "Functions.h"

#include <string>
//#include <algorithm>
#include <iostream>
//
//using namespace std;
//
//void Show(const CMatrix &arg){
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

CVector &CVector::operator = (const CVector &right){
	CVector Res(right);
	
	UINT newSize = Res.getSize();
	if (size != newSize)
	{
		elements = MyFunc::Pointers::Resize(elements, size, newSize);
		size = newSize;
	}
	
	for (UINT i = 0; i < newSize; i++)
	{
		(*this)[i] = Res[i];
	}
	return *this;
}

/* * * * * * * * перегрузки для матриц * * * * * * * */
CVector &CMatrix::operator [] (UINT i){
	if (i < 0 || i >= rowCount)
	{
		std::string
			error, msg, place, reason, object;
		error = "Error: out_of_range: ";
		place = "CMatrix::operator [](), i = ";
		reason = std::to_string(i);
		object = std::to_string(UINT(this));

		msg = error + place + reason + ", Object = " + object;
		throw std::out_of_range(msg);
	}

	return elements[i];
}

// проверить, нужна ли здесь ссылка
const CVector &CMatrix::operator [] (UINT i) const{
	if (i < 0 || i >= rowCount)
	{
		std::string 
			error, msg, place, reason, object;
		error = "Error: out_of_range: ";
		place = "CMatrix::operator []() const, i = ";
		reason = std::to_string(i);
		object = std::to_string(UINT(this));

		msg = error + place + reason + ", Object = " + object;
		throw std::out_of_range(msg);
	}

	return elements[i];
}

// проверить работоспособность данной перегрузки
CMatrix &CMatrix::operator = (const CMatrix &right){	

	//CMatrix TempThis(*this);
	UINT
		rowCount = right.getRowCount();
		//colCount = right.getColCount();

	delete[] elements;
	elements = new CVector[rowCount];

	for (UINT i = 0; i < rowCount; i++)
	{
		//elements[i] = new TYPE[colCount];
		elements[i] = right[i]; // проверить такую возможность
	}
	
	return *this;
}


/* * * * * * * * вектор * * * * * * * */
// constructor пустой
CVector::CVector(){
	size = 1;
	elements = new TYPE[size];

	elements[size - 1] = 0;
}

// создаём вектор заданной длины
CVector::CVector(UINT n){
	size = n;
	elements = new TYPE[size];

	// опционально, заполняем нулями
	for (UINT i = 0; i < size; i++)
		elements[i] = 0;
}

// конструктор копии вектора arg
CVector::CVector(const CVector &arg){
	size = arg.getSize();
	elements = new TYPE[size];

	for (UINT i = 0; i < size; i++)
		elements[i] = arg[i];
}

CVector::~CVector(){
	if (elements)
		delete[] elements;
}

TYPE CVector::getElement(UINT i) const{
	return (*this)[i];
}

UINT CVector::getSize() const{
	return size;
}

TYPE CVector::getLength() const{
	TYPE res = 0;
	for (UINT i = 0; i < size; i++)
		res += MyFunc::Numbers::pow2((*this)[i]);
	res = sqrt(res);
	return res;
}

void CVector::setElement(UINT i, TYPE value){
	(*this)[i] = value;
}

void CVector::setSize(UINT newSize){
	if (newSize == 0)
	{
		std::string 
			error, msg, place, 
			reason, object;
		error = "Error: length_error: ";
		place = "CVector::setSize(), newSize = ";
		reason = std::to_string(newSize);
		object = std::to_string(UINT(this));

		msg = error + place + reason + ", Object = " + object;
		throw std::length_error(msg);
	}

	elements = MyFunc::Pointers::Resize(elements, size, newSize);
	size = newSize;
}

/* Перегрузки операторов */

TYPE &CVector::operator [] (UINT i){
	if (i < 0 || i > size - 1)
	{
		std::string 
			error, msg, place,
			reason, object;
		error = "Error: out_of_range: ";
		place = "CVector::operator [](), i = ";
		reason = std::to_string(i);
		object = std::to_string(UINT(this));

		msg = error + place + reason + ", Object = " + object;
		throw std::out_of_range(msg);
	}

	return elements[i];
}

const TYPE &CVector::operator [] (UINT i) const{
	if (i < 0 || i > size - 1)
	{
		std::string 
			error, msg, place, 
			reason, object;
		error = "Error: out_of_range: ";
		place = "CVector::operator []() const, i = ";
		reason = std::to_string(i);
		object = std::to_string(UINT(this));

		msg = error + place + reason + ", Object = " + object;
		throw std::out_of_range(msg);
	}

	return elements[i];
}

CVector CVector::operator + (const CVector &arg){
	UINT 
		argSize = arg.getSize(),
		low, high;

	CVector Res(MyFunc::Numbers::max(size, argSize));

	if (size <= argSize)
	{
		low = size;
		high = argSize;

		//CVector Res(high);
		for (UINT i = 0; i < low; i++)
			Res[i] = (*this)[i] + arg[i];

		// дописываем хвостовые элементы
		for (UINT i = low; i < high; i++)
			Res[i] = arg[i];
		//return (Res);
	}
	else
	{
		low = argSize;
		high = size;

		//CVector Res(high);
		for (UINT i = 0; i < low; i++)
			Res[i] = (*this)[i] + arg[i];

		// дописываем хвостовые элементы
		for (UINT i = low; i < high; i++)
			Res[i] = (*this)[i];
		//return (Res);
	}	

	return Res;
}

CVector CVector::operator * (const TYPE num){
	CVector Res(*this);
	for (UINT i = 0; i < Res.getSize(); i++)
		Res[i] = (*this)[i] * num;
	return Res;
}

// скалярное произведение
TYPE CVector::operator * (const CVector &arg){
	if (size != arg.getSize())
	{
		std::string 
			error, msg, place, 
			reason, arg_reason, object;
		error = "Error: out_of_range: ";
		place = "CVector::operator * (const CVector), size = ";
		reason = std::to_string(size);
		arg_reason = std::to_string(arg.getSize());
		object = std::to_string(UINT(this));

		msg = 
			error + place + reason + ", arg.size = " + 
			arg_reason + ", Object = " + object;
		throw std::out_of_range(msg);
	}

	TYPE sum = 0;
	for (UINT i = 0; i < size; i++)
		sum += (*this)[i] * arg[i];
	return sum;
}

/*
	произведение вектора-строки на матрицу. 
	в результат уходит вектор-строка длиной 
	по количеству колонок в матрице
*/
CVector CVector::operator * (const CMatrix &arg){
	UINT size = this->getSize(), n = arg.getColCount();

	if (arg.getRowCount() == size) // равна ли длина вектора высоте матрицы?
	{
		CVector Res(n);
		for (UINT i = 0; i < n; i++)
		{
			for (UINT j = 0; j < size; j++)
			{
				Res[i] += (*this)[j] * arg[j][i];
			}
		}
		return Res;
	}

	// длина не равна высоте
	{
		std::string 
			error, msg, place, 
			reason, arg_reason, object;
		error = "Error: length_error: ";
		place = "CVector::operator * (const CMatrix), size = ";
		reason = std::to_string(size);
		arg_reason = std::to_string(arg.getRowCount());
		object = std::to_string(UINT(this));

		msg = 
			error + place + reason + ", arg.size = " + 
			arg_reason + ", Object = " + object;
		throw std::length_error(msg);
		//return CVector(size); // в результат сбрасывается нулевой вектор
	}
}

// векторное произведение
CVector CVector::crossProduct(const CVector &b) const{
	if (size != 3 || b.getSize() != 3)
	{
		std::string 
			error, msg, place, reason,
			arg_reason, object;
		error = "Error: length_error: ";
		place = "CVector::crossProduct(), size = ";
		reason = std::to_string(size);
		arg_reason = std::to_string(b.getSize());
		object = std::to_string(UINT(this));

		msg = 
			error + place + reason + ", arg.size = " +
			arg_reason + ", Object = " + object;
		throw std::length_error(msg);
	}

	SINT n = 3;
	CVector Res(n), a = *this;
	Res[0] = a[1] * b[2] - a[2] * b[1];
	Res[1] = a[2] * b[0] - a[0] * b[2];
	Res[2] = a[0] * b[1] - a[1] * b[0];
	return Res;
}


/* * * * * * * * матрица * * * * * * * */

// путсой конструктор
CMatrix::CMatrix(){
	rowCount = 1;
	colCount = 1;

	elements = new CVector[rowCount];
	elements[rowCount - 1].setSize(1);

	//elements = new pTYPE[rowCount];
	//elements[rowCount - 1] = new TYPE[colCount];
}

// constructor
CMatrix::CMatrix(UINT n, UINT m){
	rowCount = n;
	colCount = m;

	elements = new CVector[rowCount];
	for (UINT i = 0; i < rowCount; i++)
		elements[i].setSize(colCount);
}

// конструктор копии
CMatrix::CMatrix(const CMatrix &arg){
	rowCount = arg.getRowCount();
	colCount = arg.getColCount();

	elements = new CVector[rowCount];

	for (UINT i = 0; i < rowCount; i++)
	{
		elements[i] = arg[i];

		//for (UINT j = 0; j < colCount; j++)
		//	elements[i][j] = arg[i][j];
	}
}

CMatrix::~CMatrix(){
	if (elements)
	{
		delete[] elements;
	}
}

TYPE CMatrix::getElement(UINT i, UINT j) const{
	return (*this)[i][j];
}

UINT CMatrix::getRowCount() const{
	return rowCount;
}

UINT CMatrix::getColCount() const{
	return colCount;
}

bool CMatrix::checkSymmetric() const{
	UINT Col = getColCount(), Row = getRowCount();
	bool flag = true;
	if (Col == Row)
	{
		UINT i = 0, j;
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

bool CMatrix::checkSquare() const{
	//bool Res;
	//(getColCount() == getRowCount()) ? Res = true : Res = false;
	//return Res;
	return (colCount == rowCount) ? true : false;
}

// посмотреть с удалением строчек
void CMatrix::setSize(UINT n, UINT m){

	// отслеживаем нулевое количество строк
	if (rowCount != n)
	{
		if (n == 0)
		{
			std::string 
				error, msg, place, 
				reason, object;
			error = "Error: length_error: ";
			place = "CMatrix::setSize(), newRowSize = ";
			reason = std::to_string(n);
			object = std::to_string(UINT(this));

			msg = error + place + reason + ", Object = " + object;
			throw std::length_error(msg);
		}

		CMatrix TempThis(*this);
		delete[] elements;

		UINT oldRowCount = rowCount;
		rowCount = n;

		elements = new CVector[rowCount];

		// если мы увеличили размер матрицы, в конце добавляем нули
		if (oldRowCount < rowCount)
		{
			for (UINT i = 0; i < oldRowCount; i++)
				elements[i] = TempThis[i];

			// выстраиваем хвост (добавляем в конец вектора нужного размера)
			for (UINT i = oldRowCount; i < rowCount; i++)
				elements[i].setSize(colCount);
		}
		else // иначе обрезаем имеющуюся матрицу, теряя элементы
		{
			for (UINT i = 0; i < rowCount; i++)
				elements[i] = TempThis[i];
		}
	}

	// вышли из try-catch для RowCount, у строк собственная проверка исключений

	if (colCount != m)
	{
		for (UINT i = 0; i < rowCount; i++)
			elements[i].setSize(m);

		colCount = m;
	}

}

void CMatrix::setElement(UINT n, UINT m, TYPE value){
	(*this)[n][m] = value;
}

CMatrix CMatrix::flip(){
	UINT Col = getColCount(), Row = getRowCount();
	CMatrix Res(Row, Col);

	for (UINT i = 0; i < Row; i++)
	{
		for (UINT j = 0; j < Col; j++)
		{ 
			Res[i][j] = (*this)[j][i];
		}
	}
	return Res;
}

// обращение методом Гаусса
CMatrix CMatrix::inverse() const{
	/*
		закомментированы вспомогательные проверки промежуточных шагов

	*/
	UINT n = getRowCount(); // размерность квадратной матрицы
	CMatrix Ed(n, n), Res(*this);

	// заполняем единичную матрицу
	for (UINT i = 0; i < n; i++)
	{
		Ed[i][i] = 1;
	}

	/* прямой ход */
	for (UINT i = 0; i < n; i++)
	{
		// равен ли диагональный элемент 1
		if (Res[i][i] != 1)
		{
			TYPE divider; // делитель, равный не-единичному диаг. элементу

			// проверили текущий диагональный элемент на 0
			if (Res[i][i] == 0)
			{
				UINT k = i + 1;
				while ((Res[k][i] == 0) && (k < n)) k++;

				/* 
					на выходе из цикла в теории может оказаться так, 
					что весь столбец нулевой. такое возможно, и, в
					принципе, надо сделать проброс исключения на этот
					счёт.

					но это лишь означает, что det = 0. Мы собираемся 
					это проверять снаружи, что исключает такую возможность.
					но она есть, это факт.
					
				*/
				if (Res[k][i] != 0)
				{

					divider = Res[k][i];

					// приводим диагоальный элемент к 1 (делим строку на него)
					for (UINT p = 0; p < n; p++)
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
				for (UINT p = 0; p < n; p++)
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
		for (UINT j = i + 1; j < n; j++) // вертикальный индекс
		{
			if (TYPE left_side = Res[j][i]) // если сбоку не 0
			{
				for (UINT p = 0; p < n; p++) // горизонтальный индекс
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

			if (TYPE right_side = Res[j][i]) // если сбоку не 0
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
} // конец CMatrix CMatrix::inverse()

// вычисление определителя матрицы по методу Гаусса
TYPE CMatrix::detGauss() const{
	if (checkSquare())
	{
		CMatrix temp = *this;
		
		UINT n = getRowCount();
		if (n == 1)
		{
			return temp[0][0]; // в случае, если матрица состоит из одного эл-та
		}

		for (int i = 0; i < n; i++)
		{
			if (temp[i][i] == 0)
			{
				UINT k = i + 1;
				if (k >= n) return 0; // последний элемент оказался нулевым

				while ((k < n) && (temp[k][i] == 0)) k++;

				if (temp[k][i] != 0)
				{
					for (UINT p = i; p < n; p++)	temp[i][p] += temp[k][p];
				}
				else
				{
					return 0;
				}
			} // проверили текущий диагональный элемент на 0

			for (int j = n - 1; j >= i; j--)
			{
				for (UINT p = i + 1; p < n; p++)
				{
					temp[p][j] -= temp[i][j] * (temp[p][i] / temp[i][i]);
				}
			}
		}

		TYPE result = 1;
		for (UINT i = 0; i < n; i++)
		{
			result *= temp[i][i];
		}
		
		return result;
	}
//	else return INFINITY;
//	return NAN;
	else
	{
		std::string 
			error, msg, place,
			reason, object;
		error = "Error: length_error: ";
		place = "CMatrix::detGauss(), checkSquare = ";
		reason = "false";
		object = std::to_string(UINT(this));

		msg = error + place + reason + ", Object = " + object;
		throw std::length_error(msg);
	}
	
}

// определение положительно определённой матрицы
bool CMatrix::PositiveDef() const{
	bool flag = true;

	if (checkSymmetric())
	{
		UINT n = getRowCount();
		for (UINT i = 1; (i <= n) && (flag); i++)
		{
			CMatrix temp = *this;
			temp.setSize(i, i);
			if (temp.detGauss() <= 0) flag = false; // у нас неположительно определённая матрица
		}
	}
	else 
		flag = false;

	return flag;
}

CMatrix CMatrix::operator + (const CMatrix &arg){
	UINT n = arg.getRowCount(), m = arg.getColCount();

	if (n != rowCount && m != colCount)
	{
		std::string 
			error, msg, place, reason,
			arg_reason, object;
		error = "Error: length_error: ";
		place = "CMatrix::operator + (), size = (";
		reason = std::to_string(rowCount) + ", " + std::to_string(colCount);
		arg_reason = std::to_string(n) + ", " + std::to_string(m);
		object = std::to_string(UINT(this));

		msg = 
			error + place + reason + "), arg.size = (" +
			arg_reason + "), Object = " + object;
		throw std::length_error(msg);
	}

	CMatrix Res(n, m);
	for (UINT i = 0; i < n; i++)
	{
		for (UINT j = 0; j < n; j++)
		{
			// первые [] перегружены нами, а вторые берутся из CVector
			Res[i][j] = (*this)[i][j] + arg[i][j];
		}
	}
	return Res;
}

CMatrix CMatrix::operator * (const TYPE num){
	UINT n = getRowCount(), m = getColCount();
	CMatrix Res(n, m);
	for (UINT i = 0; i < n; i++)
	{
		for (UINT j = 0; j < m; j++)
		{
			Res[i][j] = (*this)[i][j] * num;
		}
	}
	return Res;
}

// нужен обработчик на неравенство матриц
CMatrix CMatrix::operator * (const CMatrix &arg){
	UINT n = getRowCount(), m = arg.getColCount(),
		p = getColCount(), // = RowCount у второй матрицы
		p2 = arg.getRowCount();

	/* избыточно, ввести обработчик */
	if (p == p2) // ширина первой матрицы равна высоте второй?
	{
		CMatrix Res(n, m);
		for (UINT i = 0; i < n; i++)
		{
			for (UINT j = 0; j < m; j++)
			{
				for (UINT k = 0; k < p; k++)
				{
					Res[i][j] += (*this)[i][k] * arg[k][j];
				}
			}
		}
		return Res;
	}

	// не равна
	{
		std::string
			error, msg, place, reason,
			arg_reason, object;
		error = "Error: length_error: ";
		place = "CMatrix CMatrix::operator * (), size = (";
		reason = std::to_string(rowCount) + ", " + std::to_string(colCount);
		arg_reason = std::to_string(n) + ", " + std::to_string(m);
		object = std::to_string(UINT(this));

		msg =
			error + place + reason + "), arg.size = (" +
			arg_reason + "), Object = " + object;
		throw std::length_error(msg);
	}
	//return CMatrix(n, m); // возвращаем нулевую матрицу
}


/*
	произведение матрицы на вектор-столбец. (строка на столбец)
	результат - вектор столбец.
*/
// нужен обработчик на неравенство матрицы и вектора
CVector CMatrix::operator * (const CVector &arg){
	UINT n = getRowCount(), m = getColCount(),
		size = arg.getSize(); // длина вектора

	if (size == m) // ширина матрицы свпадает с длиной вектора-столбца?
	{
		CVector Res(n);
		for (UINT i = 0; i < n; i++)
		{
			for (UINT j = 0; j < m; j++)
			{
				Res[i] += (*this)[i][j] * arg[j];
			}
		}
		return Res;
	}

	// не совпадает
	{
		std::string
			error, msg, place, reason,
			arg_reason, object;
		error = "Error: length_error: ";
		place = "CVector CMatrix::operator * (), size = (";
		reason = std::to_string(rowCount) + ", " + std::to_string(colCount);
		arg_reason = std::to_string(size);
		object = std::to_string(UINT(this));

		msg =
			error + place + reason + "), size = " +
			arg_reason + ", Object = " + object;
		throw std::length_error(msg);
	}
	//return CVector(n); // возвращаем нулевой вектор
	
}


/* * * * * * * * Симметричная матрица * * * * * * * */

CMatrix CSymmetricMatrix::inverse(){
	int n = getRowCount(); // размерность квадратной матрицы
	CMatrix matrix_L(n, n);

	matrix_L[0][0] = sqrt((*this)[0][0]);

	/* основной цикл разложения Холецкого */
	for (int i = 1; i < n; i++)
	{	
		matrix_L[i][0] = (*this)[i][0] / matrix_L[0][0]; // вычисляем первый столбец

		// симметричные элементы
		for (int j = 0; j < i; j++)
		{
			TYPE sum = (*this)[i][j]; // временная часть вычисления элемента новой

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
		TYPE sum = (*this)[i][i]; 

		for (int p = 0; p < i; p++)
		{
			sum -= MyFunc::Numbers::pow2(matrix_L[i][p]);
		}
		matrix_L[i][i] = sqrt(sum);	// вычислили диагональные элементы
		//cout << "\n - matrix_L"; Show(matrix_L);
	} // окончание основного цикла


	/* вычисление элементов обратной матрицы */
	CSymmetricMatrix Res(n);
	for (int i = n - 1; i >= 0; i--)
	{
		// диагональные элементы
		TYPE sum = 1 / matrix_L[i][i];

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

void CSymmetricMatrix::setElement(int n, int m, TYPE value){
	(*this)[n][m] = (*this)[m][n] = value;
}