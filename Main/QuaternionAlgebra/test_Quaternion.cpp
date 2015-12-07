#include <iostream>

#include "Quaternion.h"
#include "Matrix_extended.h"


using namespace std;

void Fill(CVector &vec);
void Show(const CVector &vec);
void Show(CQuaternion &Quat);

void Quat_MainTest();
void Quat_Algebra_Test(bool radians);
void Quat_Rotation_Test(bool radians);


/* ќсновное тело программы */
int main(){

	cout << " * * * Quaternion test initialized\n\n\n";

	short int Continue_Decide;

	do
	{

		Quat_MainTest();

		cout << "Start again? ";
		cin >> Continue_Decide;

	} while (Continue_Decide);

}

/* ‘ункции тестировани€ */
void Quat_MainTest(){

	bool radians = false; // флаг на то, что углы в градусах

	/* ѕроверка алгебры кватернионов */
	Quat_Algebra_Test(radians);

	/* ќрганизаци€ поворота вектора */
	Quat_Rotation_Test(radians);

}

// “естирование алгебры кватернионов
void Quat_Algebra_Test(bool radians){

	cout << "Testing Quaternion Algebra.\n";
	cout << "Fill in next parametrs:\n\n";

	CVector
		first_init(VEC_PART_SIZE), // параметры двух кватернионов
		second_init(VEC_PART_SIZE);

	TYPE first_angle, second_angle;

	cout << "\n\nParameters of First Quaterion (angle and axis)\n";
	cin >> first_angle;
	Fill(first_init);

	cout << "\n\nParameters of Second Quaterion (angle and axis)\n";
	cin >> second_angle;
	Fill(second_init);

	CQuaternion
		First(first_angle, first_init, radians),
		Second(second_angle, second_init, radians),
		Result;

	// умножение кватернионов
	Result = First * Second;
	cout << "\nProduct:";
	Show(Result);

	// сложение
	Result = First + Second;
	cout << "\nAdd:";
	Show(Result);

	// сопр€жение
	Result = First.getAdjoint();
	cout << "\nAdjoint for First:";
	Show(Result);

	Result = Second.getAdjoint();
	cout << "\nAdjoint for Second:";
	Show(Result);

	// нормирование
	Result = First;
	Result.Normalize();
	cout << "\nNormalize for First:";
	Show(Result);

	Result = Second;
	Result.Normalize();
	cout << "\nNormalize for Second:";
	Show(Result);
}

// “естирование поворота вектора с помощью кватерниона
void Quat_Rotation_Test(bool radians){

	cout << "\n\nTesting Quaternion rotation.\n";
	cout << "Fill in next parametrs:\n\n";

	CVector
		a_vec(VEC_PART_SIZE), // координаты оси вращени€
		ro_vec(VEC_PART_SIZE); //координаты вектора, поворот которого будет совершатьс€ 

	TYPE angle;

	cout << "Rotation angle (in degrees) "; cin >> angle;

	cout << "\nCoordinates of rotation axis\n"; Fill(a_vec);
	cout << "\n\nCoordinates of rotated vector\n"; Fill(ro_vec);

	CVector res_vec(VEC_PART_SIZE);
	CQuaternion Main_Quat(angle, a_vec, radians);

	// вектор после осуществлени€ поворота (после нормировани€?)
	res_vec = ro_vec.rotate(Main_Quat);

	cout << "\nRotated vector:\n"; Show(res_vec);
}

/* ¬спомогательные процедуры */
void Fill(CVector &vec){
	int length = vec.getSize();
	for (int i = 0; i < length; i++){
		cin >> vec[i];
	}
}

void Show(const CVector &vec){
	int length = vec.getSize();
	for (int i = 0; i < length; i++){
		cout << vec[i] << "	";
	}
}

void Show(CQuaternion &Quat){
	cout << "\nScalar part = " << Quat.getScalar();
	cout << "\nVector part: "; Show(Quat.getVector());
}