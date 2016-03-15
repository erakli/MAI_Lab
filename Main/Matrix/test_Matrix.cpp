#include "Matrix_classes.h"
#include <iostream>

using namespace std;

static double ClearZero(const double &arg);

void Show(const CVector &vec);
void Show(const CMatrix &arg);

void Fill(CVector &vec);
void Fill(CMatrix &arg);

void Second(const CVector &vec, CVector &n_vec);
void Second(const CMatrix &arg, CMatrix &n_arg);
void Second(CVector &n_vec);
void Second(CMatrix &arg);

void Vector();
void Matrix();

void Test(int n, CMatrix &arg);
void inverseCheck(const CMatrix &arg, CMatrix &test);

int main(){

	cout << " * * * Vector and Matrix operations test * * *";
	
	try{
		bool cont;
		do
		{
			cout << "\n\nWhat do we have now? (vector/matrix) ";
			int bVector;
			cin >> bVector; cout << "\n";

			if (bVector)
			{
				Matrix();
			}
			else
			{
				Vector();
			}

			cout << "\nContinue? "; cin >> cont;
		} while (cont);
	}
	catch(exception &e)
	{
		cerr << "\n	" << e.what() << "\n";
	}
	

} // end of main

void Vector(){

	int n;
	cout << "Vector size: "; cin >> n;

	CVector vec(n);

	//cout << "\nVector: ";
	//Show(vec);

	Fill(vec);

	cout << "\nWhat to do now?\n";
	cout << "	1. Show information\n	2. Set Element\n	3. Set Length\n";
	cout << "	4. +\n	5. *\n	6. Cross Product";

	int choice, num;
	double value;

	do
	{
		cout << "\n\n\nYour choice: "; cin >> choice; cout << "\n";

		switch (choice)
		{
		case 1: // 1. Show information
		{
			cout << "Size: " << vec.getSize() << ", Length: "
				<< vec.getLength() << "\n";
			break;
		}
		case 2: // 2. Set Element
		{
			cout << "What the element? "; cin >> num;
			cout << "For value "; cin >> value;
			vec.setElement(num - 1, value);
			cout << "\nNew vector: ";
			Show(vec);
			break;
		}
		case 3: // 3. Set Length
		{
			cout << "What size? "; cin >> num;
			vec.setSize(num);
			Show(vec);
			break;
		}
		case 4: // 4. +
		{
			cout << "Let's do a little summation.\n";
			CVector n_vec(n);
			Second(vec, n_vec);

			cout << "\nResult = ";
			vec = vec + n_vec;
			Show(vec);
			break;
		}
		case 5: // 5. *
		{
			cout << "Let's do multiplication.\n";
			cout << "What is on the right?\n";
			cout << "	1. Number\n	2. Vector\n	3. Matrix\n\nYour choice: ";
			cin >> num;

			switch (num)
			{
			case 1: // 1. Number
			{
				cout << "Number "; cin >> value;
				cout << "\nResult = ";
				vec = vec * value;
				Show(vec);
				break;
			}
			case 2: // 2. Vector
			{
				CVector n_vec(n);
				Second(vec, n_vec);
				cout << "\nResult = " << vec * n_vec;
				break;
			}
			case 3: // 3. Matrix
			{
				CMatrix n_matr(n, n);
				Second(n_matr);
				cout << "\nResult = ";
				vec = vec * n_matr;
				Show(vec);
				break;
			}
			default:
				break;
			} // 2 switch end

			break;
		}
		case 6: // 6. Cross Product
		{
			CVector n_vec(n);
			Second(vec, n_vec);
			cout << "\nResult = ";
			vec = vec.crossProduct(n_vec);
			Show(vec);
			break;
		}
		default:
			break;
		} // 1 switch end

		cout << "\n\n	- End of action.";
	} while ((choice > 0) && (choice < 7));
} // end of Vector()

void Matrix(){
	int Row, Col;
	cout << "Matrix size (Row, Col): "; cin >> Row >> Col;

	CMatrix matr(Row, Col);

	int mode;
	cout << "Test or manual matrix? "; cin >> mode;
	if (mode)
	{
		//cout << "\nMatrix:\n";
		//Show(matr);

		Fill(matr);
	}
	else
	{
		Test(Row, matr);
	}

	cout << "\nWhat to do now?\n";
	cout << "	1. Show information\n	2. Set Element\n	3. Set Length\n";
	cout << "	4. +\n	5. *\n	6. Flip\n	7. Check Symmetric\n	8. Inverse\n"
		<< "	9. Determinant";

	int choice, num, num_2;
	double value;

	do
	{
		cout << "\n\n\nYour choice: "; cin >> choice; cout << "\n";

		switch (choice)
		{
		case 1: // 1. Show information
		{
			cout << "Row: " << matr.getRowCount() << ", Col: " 
				<< matr.getColCount() << "\n";
			break;
		}
		case 2: // 2. Set Element
		{
			cout << "What the element? "; cin >> num >> num_2;
			cout << "For value "; cin >> value;

			if (matr.checkSymmetric())
			{	
				CSymmetricMatrix temp(matr);
				temp.setElement(num - 1, num_2 - 1, value);
				matr = temp;
			}
			else
			{			
				matr.setElement(num - 1, num_2 - 1, value);
			}
			cout << "\nNew Matrix:\n";
			Show(matr);
			break;
		}
		case 3: // 3. Set Length
		{
			cout << "What size? (Row, Col) "; cin >> num >> num_2;
			matr.setSize(num, num_2);
			Show(matr);
			break;
		}
		case 4: // 4. +
		{
			cout << "Let's do a little summation.\n";
			CMatrix n_matr(Row, Col);
			Second(matr, n_matr);

			cout << "\nResult:\n";
			matr = matr + n_matr;
			Show(matr);
			break;
		}
		case 5: // 5. *
		{
			cout << "Let's do multiplication.\n";
			cout << "What is on the right?\n";
			cout << "	1. Number\n	2. Vector\n	3. Matrix\n\nYour choice: ";
			cin >> num;

			switch (num)
			{
			case 1: // 1. Number
			{
				cout << "Number "; cin >> value;
				cout << "\nResult:\n ";
				Show(matr * value);
				break;
			}
			case 2: // 2. Vector
			{
				CVector n_vec(Col);
				Second(n_vec);
				cout << "\nResult = ";
				Show(matr * n_vec);
				break;
			}
			case 3: // 3. Matrix
			{
				CMatrix n_matr(Row, Col);
				Second(matr, n_matr);
				cout << "\nResult:\n ";
				matr = matr * n_matr;
				Show(matr);
				break;
			}
			default:
				break;
			} // 2 switch end

			break;
		}
		case 6: // 6. Flip
		{
			matr = matr.flip();
			Show(matr);
			break;
		}
		case 7: // 7. Check Symmetric
		{
			cout << "This matrix ";
			matr.checkSymmetric() ? cout << "Symmetric\n" : cout << "Not Symmetric\n";
			break;
		}
		case 8: // 8. Inverse
		{
			double Determinant = matr.detGauss();
			if (Determinant != 0)
			{
				bool Positive = matr.PositiveDef(); // положительно определена?
				if (matr.checkSymmetric() && Positive)	// симметричная матрица?
				{										
					CSymmetricMatrix temp(matr);
					CMatrix test_matrix(matr);
					cout << "I'll show you inverse matrix, boy\n";
					matr = temp.inverse();
					inverseCheck(matr, test_matrix);
				} 
				else	// не симметричная
				{
					cout << "I'll show you inverse matrix, boy\n\n";
					if (!Positive) // определена отрицательно
					{
						cout << "But before we start, you should know that\n"
							<< "it's not a legal (PositiveDef - false) symmetric\n"
							<< "matrix!"
							<< "\nWe'll do the inverse matrix thanks to Gauss\n\n";
					}

					CMatrix test_matrix(matr);
					matr = matr.inverse();
					inverseCheck(matr, test_matrix);
				}
			}
			else
			{
				cout << "Determinant = " << Determinant << "! There is no inverse matrix.";
			}	
			break;
		}
		case 9: // 9. Determinant
		{
			cout << "Determinant = " << matr.detGauss();
			if (matr.checkSymmetric())
			{
				cout << "\nThis matrix Positive Definite - " << matr.PositiveDef();
			}
			break;
		}
		default:
			break;
		} // 1 switch end

		cout << "\n\n	- End of action.";
	} while ((choice > 0) && (choice < 10));
} // end of Matrix()


// Вспомогательные функции -------------------------------------------------------
static double ClearZero(const double &arg){
	if (abs(arg) > 1.0e-014) return arg;
	else return 0;
}

void Show(const CVector &vec){
	int length = vec.getSize();
	for (int i = 0; i < length; i++){
		cout << ClearZero(vec[i]) << "	";
	}
}

void Show(const CMatrix &arg){
	int Row = arg.getRowCount(), Col = arg.getColCount();
	for (int i = 0; i < Row; i++){
		for (int j = 0; j < Col; j++)
		{
			cout << ClearZero(arg[i][j]) << "	";
		}
		cout << "\n";
	}
}

void Fill(CVector &vec){
	int length = vec.getSize();
	cout << "\nFill the vector (length = " << length << "): ";
	for (int i = 0; i < length; i++){
		cin >> vec[i];
	}
}

void Fill(CMatrix &arg){
	int Row = arg.getRowCount(), Col = arg.getColCount();
	cout << "\nFill the matrix [" << Row << "x" << Col <<"]:\n";
	for (int i = 0; i < Row; i++){
		for (int j = 0; j < Col; j++)
		{
			cin >> arg[i][j];
		}
	}
}

void Second(const CVector &vec, CVector &n_vec){
	cout << "How would look a second vector? (new/same) ";
	int same;
	cin >> same; cout << "\n";
	if (same)
	{
		n_vec = vec;
		cout << "Second vector: ";
		Show(n_vec);
	}
	else
	{
		int size;
		cout << "Vector size: "; cin >> size;
		n_vec.setSize(size);
		Fill(n_vec);
	}
}

void Second(const CMatrix &arg, CMatrix &n_arg){
	cout << "How would look a second matrix? (new/same) ";
	int same;
	cin >> same; cout << "\n";
	if (same)
	{
		n_arg = arg;
		cout << "Second matrix:\n";
		Show(n_arg);
	}
	else
	{
		int Row, Col;
		cout << "Matrix size: "; cin >> Row >> Col;
		n_arg.setSize(Row, Col);
		Fill(n_arg);
	}
}

void Second(CVector &n_vec){
	int size;
	cout << "Vector size: "; cin >> size;
	n_vec.setSize(size);
	Fill(n_vec);
}

void Second(CMatrix &arg){
	int Row, Col;
	cout << "Matrix size (Row, Col): "; cin >> Row >> Col;
	arg.setSize(Row, Col);
	Fill(arg);
}

// функции для проверки -----------------------------------
void Test(int n, CMatrix &arg){
	const int size = 4;
	int Res[size][size] =
	{
		{ 1,	0,		-1,		4 },
		{ 0,	4,		4,		4 -1 }, 
		{ -1,	4,		14,		1 }, 
		{ 4,	4,		1,		21 -1 }
	};

	arg.setSize(n, n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			arg[i][j] = Res[i][j];
		}
	}
}

void inverseCheck(const CMatrix &arg, CMatrix &test){
	Show(arg);
	cout << "\n\nNow we check inverse matrix (multiply it on original)";
	cout << "\nOriginal:\n"; Show(test);
	cout << "\nResult of multiplication:\n";
	Show(test * arg);
}