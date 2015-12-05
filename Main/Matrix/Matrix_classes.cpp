#include "Matrix_classes.h"
#include <math.h>
//#include <string>
//#include <algorithm>
//#include <iostream>
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

	���������� �������� ������� � ����������� ���������� ��������

*/


/* * * * * * * * ���������� ��� ������ * * * * * * * */
BaseVector &CMatrix::operator [] (int i){
	return BaseMatrix::operator [] (i);
}

// ���������, ����� �� ����� ������
const BaseVector &CMatrix::operator [] (int i) const{
	return BaseMatrix::operator [] (i);
}

CMatrix &CMatrix::operator = (const CMatrix &arg){
	CMatrix Res(arg);
	for (int i = 0; i < getRowCount(); i++)
	{
		(*this)[i] = Res[i];
	}
	return *this;
}


/* * * * * * * * ������ * * * * * * * */
TYPE CVector::getElement(int i) const{
	return (*this)[i];
}

int CVector::getSize() const{
	return size();
}

TYPE CVector::getLength() const{
	TYPE res = 0;
	for (int i = 0; i < getSize(); i++)
		res += pow((*this)[i], 2);
	res = sqrt(res);
	return res;
}

void CVector::setElement(int i, TYPE value){
	(*this)[i] = value;
}

void CVector::setSize(int i){
	this->resize(i, 0); // ����� �������� ����������� 0
}

CVector CVector::operator + (const CVector &arg){
	// ���������, �������� ���������� ����� ��������
	/*int s = std::min<int>
		(getSize(), arg.getSize());*/
	int s = this->getSize();
	CVector Res(s);
	for (int i = 0; i < Res.getSize(); i++)
		Res[i] = (*this)[i] + arg[i];
	return Res;
}

const CVector CVector::operator + (const CVector &arg) const{
	int s = this->getSize();
	CVector Res(s);
	for (int i = 0; i < Res.getSize(); i++)
		Res[i] = (*this)[i] + arg[i];
	return Res;
}

CVector CVector::operator * (const TYPE num){
	CVector Res(getSize());
	for (int i = 0; i < getSize(); i++)
		Res[i] = (*this)[i] * num;
	return Res;
}

const CVector CVector::operator * (const TYPE num) const{
	CVector Res(getSize());
	for (int i = 0; i < getSize(); i++)
		Res[i] = (*this)[i] * num;
	return Res;
}

// ��������� ������������
TYPE CVector::operator * (const CVector &arg){
	/*int s = std::min<int>
		(getSize(), arg.getSize());*/
	int s = this->getSize();
	TYPE sum = 0;
	for (int i = 0; i < s; i++)
		sum += (*this)[i] * arg[i];
	return sum;
}

/*
	������������ �������-������ �� �������. 
	� ��������� ������ ������-������ ������ 
	�� ���������� ������� � �������
*/
CVector CVector::operator * (const CMatrix &arg){
	int size = this->getSize(), n = arg.getColCount();

	if (arg.getRowCount() == size) // ����� �� ����� ������� ������ �������?
	{
		CVector Res(n);
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < size; j++)
			{
				Res[i] += (*this)[j] * arg[j][i];
			}
		}
		return Res;
	}
	else // ����� �� ����� ������
	{
		return CVector(size); // � ��������� ������������ ������� ������
	}
}

// ��������� ������������
CVector CVector::crossProduct(const CVector &b){
	int n = 3;
	CVector Res(n), a = *this;
	Res[0] = a[1] * b[2] - a[2] * b[1];
	Res[1] = a[2] * b[0] - a[0] * b[2];
	Res[2] = a[0] * b[1] - a[1] * b[0];
	return Res;
}



/* * * * * * * * ������� * * * * * * * */

TYPE CMatrix::getElement(int i, int j) const{
	return (*this)[i][j];
}

int CMatrix::getRowCount() const{
	return size();
}

int CMatrix::getColCount() const{
	return (getRowCount() > 0) ? (*this)[0].size() : 0;
}

bool CMatrix::checkSymmetric() const{
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

bool CMatrix::checkSquare() const{
	bool Res;
	(getColCount() == getRowCount()) ? Res = true : Res = false;
	return Res;
}

void CMatrix::setSize(int n, int m){
	this->BaseMatrix::resize(n);
	for (int i = 0; i < n; i++)
		(*this)[i].resize(m);
}

void CMatrix::setElement(int n, int m, TYPE value){
	(*this)[n][m] = value;
}

CMatrix CMatrix::flip(){
	int Col = getColCount(), Row = getRowCount();
	CMatrix Res(Row, Col);
	for (int i = 0; i < Row; i++)
	{
		for (int j = 0; j < Col; j++)
		{ 
			Res[i][j] = (*this)[j][i];
		}
	}
	return Res;
}

// ��������� ������� ������
CMatrix CMatrix::inverse(){
	/*
		���������������� ��������������� �������� ������������� �����

	*/
	int n = getRowCount(); // ����������� ���������� �������
	CMatrix Ed(n, n), Res(*this);

	// ��������� ��������� �������
	for (int i = 0; i < n; i++)
	{
		Ed[i][i] = 1;
	}

	/* ������ ��� */
	for (int i = 0; i < n; i++)
	{
		// ����� �� ������������ ������� 1
		if (Res[i][i] != 1)
		{
			TYPE divider; // ��������, ������ ��-���������� ����. ��������

			// ��������� ������� ������������ ������� �� 0
			if (Res[i][i] == 0)
			{
				int k = i + 1;
				while ((Res[k][i] == 0) && (k < n)) k++;

				/* 
					�� ������ �� ����� � ������ ����� ��������� ���, 
					��� ���� ������� �������. ����� ��������, �, �
					��������, ���� ������� ������� ���������� �� ����
					����.

					�� ��� ���� ��������, ��� det = 0. �� ���������� 
					��� ��������� �������, ��� ��������� ����� �����������.
					�� ��� ����, ��� ����.
					
				*/
				if (Res[k][i] != 0)
				{

					divider = Res[k][i];

					// �������� ����������� ������� � 1 (����� ������ �� ����)
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
			else // ������������ ������� (!= 0 && != 1)
			{
				divider = Res[i][i];

				// �������� ����������� ������� � 1 (����� ������ �� ����)
				for (int p = 0; p < n; p++)
				{
					Ed[i][p] /= divider;
					Res[i][p] /= divider;
					/*cout << "\n - Ed"; Show(Ed);
					cout << "\n - Res"; Show(Res);
					cout << "End step (p = " << p << ")\n";*/
				}
			}
		} // ���������� ������������ ������� � 1

		// �������� ������� � ������������ ����
		for (int j = i + 1; j < n; j++) // ������������ ������
		{
			if (TYPE left_side = Res[j][i]) // ���� ����� �� 0
			{
				for (int p = 0; p < n; p++) // �������������� ������
				{
					/*cout << "\nNew step (j = " << j << ", " << "p = " << p << ")\n";
					cout << "Sboku " << left_side << " Sverhu " << Res[i][p];*/

					if (Ed[i][p]) // ���� ������ �� 0
					{
						Ed[j][p] -= Ed[i][p] * left_side;
						//cout << "\n - Ed"; Show(Ed);
					}

					if (Res[i][p]) // ���� ������ �� 0
					{
						Res[j][p] -= Res[i][p] * left_side;
						//cout << "\n - Res"; Show(Res);
					}
				}
			}
		}
	} // ����� ������� ����

	/* �������� ��� */
	for (int i = n - 1; i > 0; i--) // ������������ ������
	{
		for (int j = i - 1; j >= 0; j--) // ������������ ������
		{

			if (TYPE right_side = Res[j][i]) // ���� ����� �� 0
			{
				for (int k = n - 1; k >= 0; k--) // �������������� ������
				{
					/*cout << "\nNew step (j = " << j << ", " << "k = " << k << ")\n";
					cout << "Sboku " << right_side << " Snizu " << Res[i][k];*/

					if (Ed[i][k]) // ���� ����� �� 0
					{
						Ed[j][k] -= Ed[i][k] * right_side;
						//cout << "\n - Ed"; Show(Ed);
					}

					if (Res[i][k]) // ���� ����� �� 0
					{
						Res[j][k] -= Res[i][k] * right_side;
						//cout << "\n - Res"; Show(Res);
					}
				}
			}

		}
	} // �����

	return Ed;
} // ����� CMatrix CMatrix::inverse()

// ���������� ������������ ������� �� ������ ������
TYPE CMatrix::detGauss() const{
	if (checkSquare())
	{
		CMatrix temp = *this;
		
		int n = getRowCount();
		if (n == 1)
		{
			return temp[0][0]; // � ������, ���� ������� ������� �� ������ ��-��
		}

		for (int i = 0; i < n; i++)
		{
			if (temp[i][i] == 0)
			{
				int k = i + 1;
				if (k >= n) return 0; // ��������� ������� �������� �������

				while ((k < n) && (temp[k][i] == 0)) k++;

				if (temp[k][i] != 0)
				{
					for (int p = i; p < n; p++)	temp[i][p] += temp[k][p];
				}
				else
				{
					return 0;
				}
			} // ��������� ������� ������������ ������� �� 0

			for (int j = n - 1; j >= i; j--)
			{
				for (int p = i + 1; p < n; p++)
				{
					temp[p][j] -= temp[i][j] * (temp[p][i] / temp[i][i]);
				}
			}
		}

		TYPE result = 1;
		for (int i = 0; i < n; i++)
		{
			result *= temp[i][i];
		}
		
		return result;
	}
	else return INFINITY;
}

// ����������� ������������ ����������� �������
bool CMatrix::PositiveDef() const{
	bool flag = true;
	if (checkSymmetric())
	{
		int n = getRowCount();
		for (int i = 1; (i <= n) && (flag); i++)
		{
			CMatrix temp = *this;
			temp.setSize(i, i);
			if (temp.detGauss() <= 0) flag = false; // � ��� �������������� ����������� �������
		}
	}
	else flag = false;

	return flag;
}

CMatrix CMatrix::operator + (const CMatrix &arg){
	int n = arg.getRowCount(), m = arg.getColCount();
	CMatrix Res(n, m);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			// ������ [] ����������� ����, � ������ ������� �� BaseVector
			Res[i][j] = (*this)[i][j] + arg[i][j];
		}
	}
	return Res;
}

CMatrix CMatrix::operator * (const TYPE num){
	int n = getRowCount(), m = getColCount();
	CMatrix Res(n, m);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			Res[i][j] = (*this)[i][j] * num;
		}
	}
	return Res;
}

CMatrix CMatrix::operator * (const CMatrix &arg){
	int n = getRowCount(), m = arg.getColCount(),
		p = getColCount(), // = RowCount � ������ �������
		p2 = arg.getRowCount();

	/* ���������, ������ ���������� */
	if (p == p2) // ������ ������ ������� ����� ������ ������?
	{
		CMatrix Res(n, m);
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
	else // �� �����
	{
		return CMatrix(n, m); // ���������� ������� �������
	}
	
}


/*
	������������ ������� �� ������-�������. (������ �� �������)
	��������� - ������ �������.
*/
CVector CMatrix::operator * (const CVector &arg){
	int n = getRowCount(), m = getColCount(),
		size = arg.getSize(); // ����� �������
	if (size == m) // ������ ������� �������� � ������ �������-�������?
	{
		CVector Res(n);
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < m; j++)
				{
					Res[i] += (*this)[i][j] * arg[j];
				}
			}
			return Res;
	}
	else // �� ���������
	{
		return CVector(n); // ���������� ������� ������
	}
	
}


/* * * * * * * * ������������ ������� * * * * * * * */

CMatrix CSymmetricMatrix::inverse(){
	int n = getRowCount(); // ����������� ���������� �������
	CMatrix matrix_L(n, n);

	matrix_L[0][0] = sqrt((*this)[0][0]);

	/* �������� ���� ���������� ��������� */
	for (int i = 1; i < n; i++)
	{	
		matrix_L[i][0] = (*this)[i][0] / matrix_L[0][0]; // ��������� ������ �������

		// ������������ ��������
		for (int j = 0; j < i; j++)
		{
			TYPE sum = (*this)[i][j]; // ��������� ����� ���������� �������� �����

			for (int p = 0; p < j; p++)
			{
				sum -= matrix_L[i][p] * matrix_L[j][p];
				//cout << "\nsum " << i << " " << p << " = " << sum;
			}
			// ��������� ������������ ��������
			matrix_L[i][j] = sum / matrix_L[j][j];
			//cout << "\n - matrix_L"; Show(matrix_L);
		}


		// ������������ ��������
		TYPE sum = (*this)[i][i]; 

		for (int p = 0; p < i; p++)
		{
			sum -= pow(matrix_L[i][p], 2);
		}
		matrix_L[i][i] = sqrt(sum);	// ��������� ������������ ��������
		//cout << "\n - matrix_L"; Show(matrix_L);
	} // ��������� ��������� �����


	/* ���������� ��������� �������� ������� */
	CSymmetricMatrix Res(n);
	for (int i = n - 1; i >= 0; i--)
	{
		// ������������ ��������
		TYPE sum = 1 / matrix_L[i][i];

		for (int k = i + 1; k < n; k++)
		{
			sum -= matrix_L[k][i] * Res[k][i];
		}

		Res[i][i] = sum / matrix_L[i][i];
		//cout << "\n - Res"; Show(Res);


		// �������������� �������
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