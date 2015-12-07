#include <iostream>

#include "Quaternion.h"
#include "Matrix_extended.h"


using namespace std;

void Fill(CVector &vec);
void Show(const CVector &vec);
void Show(CQuaternion &Quat);

void Quat_MainTest(short int Choice);
void Quat_Algebra_Test(bool radians);
void Quat_Rotation_Test(bool radians);


/* �������� ���� ��������� */
int main(){

	cout << " * * * Quaternion test has been initialized * * *\n\n\n";

	short int Choice;

	do
	{

		cout << "\n\nChoose action:\n" 
			<< "	1. Quaternion Algebra\n" 
			<< "	2. Vector rotation\n"
			<< "	0. Exit\n"
			<< "\n";
		cin >> Choice;

		Quat_MainTest(Choice);

	} while (Choice);

}

/* ������� ������������ */
void Quat_MainTest(short int Choice){

	bool radians = false; // ���� �� ��, ��� ���� � ��������

	switch (Choice)
	{
	case 1:
		{
			/* �������� ������� ������������ */
			Quat_Algebra_Test(radians);
			break;
		}

	case 2:
		{
			/* ����������� �������� ������� */
			Quat_Rotation_Test(radians);
		}

	default:
		break;
	}
	
}

// ������������ ������� ������������
void Quat_Algebra_Test(bool radians){

	cout << " * * * Testing Quaternion Algebra.\n";
	cout << "Fill in next parametrs:";

	CVector
		first_init(VEC_PART_SIZE), // ��������� ���� ������������
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

	// ��������� ������������
	Result = First * Second;
	cout << "\n\nProduct:";
	Show(Result);

	// ��������
	Result = First + Second;
	cout << "\n\nAdd:";
	Show(Result);

	// ����������
	Result = First.getAdjoint();
	cout << "\n\nAdjoint for First:";
	Show(Result);

	Result = Second.getAdjoint();
	cout << "\n\nAdjoint for Second:";
	Show(Result);

	// ������������
	Result = First;
	Result.Normalize();
	cout << "\n\nNormalize for First:";
	Show(Result);

	Result = Second;
	Result.Normalize();
	cout << "\n\nNormalize for Second:";
	Show(Result);
}

// ������������ �������� ������� � ������� �����������
void Quat_Rotation_Test(bool radians){

	cout << "\n\n\n * * * Testing Quaternion rotation.\n";
	cout << "Fill in next parametrs:";

	CVector
		a_vec(VEC_PART_SIZE), // ���������� ��� ��������
		ro_vec(VEC_PART_SIZE); //���������� �������, ������� �������� ����� ����������� 

	TYPE angle;

	cout << "\n\nRotation angle (in degrees) "; cin >> angle;

	cout << "\nCoordinates of rotation axis\n"; Fill(a_vec);
	cout << "\n\nCoordinates of rotated vector\n"; Fill(ro_vec);

	CVector res_vec(VEC_PART_SIZE);
	CQuaternion Main_Quat(angle, a_vec, radians);

	// ������ ����� ������������� ��������
	res_vec = ro_vec.rotate(Main_Quat);
	cout << "\nRotated vector:\n"; Show(res_vec);

	res_vec = ro_vec.rotate(a_vec, angle, radians);
	cout << "\nRotated vector (with Rodrig formula):\n"; Show(res_vec);
}

/* ��������������� ��������� */
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
	cout << "\nScalar	" << Quat.getScalar();
	cout << "\nVector	"; Show(Quat.getVector());
}