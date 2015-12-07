#include "Quaternion.h"
#include "Functions.h"

/* * * * * * * * CQuaternion * * * * * * * */

TYPE &CQuaternion::operator [] (SINT i){
	if (i == 0)
	{
		return scalar;
	}
	else if ((i > 0) && (i < QUAT_SIZE))
	{
		return vector[i - 1];
	}
	else // ����� �� ��������
	{
		//TYPE res(-1);
		//return 0;
	}
}

// ���������, ����� �� ����� ������
const TYPE &CQuaternion::operator [] (SINT i) const{
	if (i == 0)
	{
		return scalar;
	}
	else if ((i > 0) && (i < QUAT_SIZE))
	{
		return vector[i - 1];
	}
	else // ����� �� ��������
	{
		//TYPE res(-1);
		//return 0;
	}
}


// ��������� ����������

CQuaternion &CQuaternion::operator = (const TYPE scalar){
	this->scalar = scalar;

	return *this;
}

CQuaternion &CQuaternion::operator = (const CVector &vector){
	this->vector = vector;

	return *this;
}

CQuaternion &CQuaternion::operator = (const CQuaternion &Quat){
	scalar = Quat.getScalar();
	vector = Quat.getVector();

	return *this;
}


// ������������

CQuaternion::CQuaternion(TYPE lam_0, TYPE lam_1, TYPE lam_2, TYPE lam_3){

	/* � ���� ������������� ������ �� ������� */

	vector.setSize(VEC_PART_SIZE);
	vector[0] = lam_1;
	vector[1] = lam_2;
	vector[2] = lam_3;

	scalar = lam_0;

	// lambda_0 ���������� �� ������� lam_0^2 + lam_1^2 + ... = 1
	//TYPE check;
	//check = vector.getLength();

	/* 
		������� �������� �� check > 1
		� ��������, ����� ����� ������? 
	*/

	//scalar = (1 == check + pow2(lam_1)) ? lam_0 : sqrt(1 - check);

}

CQuaternion::CQuaternion(TYPE phi, const CVector &e_vec, const bool radians){

	vector.setSize(VEC_PART_SIZE); // �� ������ ������

	CVector axis(e_vec);
	axis.Normalize(); // ����������� �����������

	if (radians)
	{
		// ������� � ��������
		scalar = cos(phi / 2);
		vector = axis * sin(phi / 2);
	}
	else
	{
		// �������, ��� ������� ���� � ��������. ������ ������� � �������
		TYPE angle = deg2rad(phi);

		scalar = cos(angle / 2);
		vector = axis * sin(angle / 2);
	};

}


// ���������� ����������

CQuaternion CQuaternion::operator + (const CQuaternion &Quat){

	CQuaternion Res;

	Res.scalar = scalar + Quat.scalar;
	Res.vector = vector + Quat.vector;

	return Res;
}

// ������������� ������������ ������������
CQuaternion CQuaternion::operator * (const CQuaternion &Quat){

	CQuaternion Res;

	TYPE
		lamb_0 = scalar,
		mu_0 = Quat.scalar;

	CVector
		lamb(vector),
		mu(Quat.vector);

	Res.scalar = lamb_0 * mu_0 - lamb * mu;

	Res.vector = mu * lamb_0 + lamb * mu_0 + lamb.crossProduct(mu);

	return Res;
}

// ��������� ����������� �� ������
CQuaternion CQuaternion::operator * (const CVector &vec){

	CQuaternion Res;

	TYPE
		lamb_0 = scalar;

	CVector
		lamb(vector);

	Res.scalar = -(lamb * vec);
	Res.vector = vec * lamb_0 + lamb.crossProduct(vec);

	return Res;
}


// "��������" �������

const TYPE CQuaternion::getScalar() const{
	return scalar;
}

const CVector CQuaternion::getVector() const{
	return vector;
}


// ��������� ������� �����������

TYPE CQuaternion::getNorm(){
	TYPE Res = 0;

	// ��������� ������ ������
	for (SINT i = 0; i < QUAT_SIZE; i++)
	{
		Res += pow2((*this)[i]);
	}

	return Res;
}

TYPE CQuaternion::getLength(){
	return sqrt(getNorm());
}

// ���������� ������������ �����������
CQuaternion CQuaternion::getAdjoint(){

	CQuaternion Res(*this);

	Res.vector = vector * -1;

	Res.Normalize(); // �� ������ ������ ����������� ����� ��

	return Res;
}

/*
	������������ ����������� - ������� ������� �������� �� �����

	���������� ������������ ������� - ������� ������� �������� �� ������
*/
void CQuaternion::Normalize(){

	// ����� �� �� ����� � �� ������ ����������� (��� � ���������)
	TYPE Norm = getLength();

	for (SINT i = 0; i < QUAT_SIZE; i++)
	{
		(*this)[i] /= Norm;
	}

}