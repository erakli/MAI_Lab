#include <iostream>

#include "Quaternion.h"
#include "Matrix_extended.h"


using namespace std;

void Fill(CVector &vec);
void Show(const CVector &vec);
void Output(CQuaternion &Quat);

int main(){

	cout << " * * * Quaternion test initialized\n\n\n";

	cout << "Fill in next parametrs:\n\n";

	TYPE angle;

	CVector
		a_vec(VEC_PART_SIZE), // координаты оси вращения
		ro_vec(VEC_PART_SIZE), //координаты вектора, поворот которого будет совершаться 

		first_init(VEC_PART_SIZE), // параметры двух кватернионов
		second_init(VEC_PART_SIZE);

	TYPE first_angle, second_angle;

	cout << "Rotation angle (in degrees) "; cin >> angle;

	cout << "\nCoordinates of rotation axis\n"; Fill(a_vec);
	cout << "\n\nCoordinates of rotated vector\n"; Fill(ro_vec);

	cout << "\n\nParameters of First Quaterion (angle and axis)\n"; Fill(first_init);
	cout << "\n\nParameters of Second Quaterion (angle and axis)\n"; Fill(second_init);


	CQuaternion 
		First(first_init[0], first_init[1], first_init[2], first_init[3]),
		Second(second_init[0], second_init[1], second_init[2], second_init[3]),
		Result;



}

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

void Output(CQuaternion &Quat){
	cout << "\nScalar part = " << Quat.getScalar();
	cout << "\nVector part: "; Show(Quat.getVector());
}