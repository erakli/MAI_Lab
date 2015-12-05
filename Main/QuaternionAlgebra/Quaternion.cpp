#include "Quaternion.h"
#include "Functions.h"

/* * * * * * * * CQuaternion * * * * * * * */

// конструкторы

CQuaternion::CQuaternion(TYPE lam_0, TYPE lam_1, TYPE lam_2, TYPE lam_3){

	vector.setSize(VEC_PART_SIZE);
	vector[0] = lam_1;
	vector[1] = lam_2;
	vector[2] = lam_3;

	// lambda_0 выбирается из условия lam_0^2 + lam_1^2 + ... = 1
	TYPE check;
	check = vector.getLength();

	/* 
		сделать проверку на check > 1
		в принципе, нужно такое делать? 
	*/

	scalar = (1 == check + pow2(lam_1)) ? lam_0 : sqrt(1 - check);

}

CQuaternion::CQuaternion(TYPE phi, const CVector &e_vec, const bool radians){

	vector.setSize(VEC_PART_SIZE); // на всякий случай

	if (radians)
	{
		// считаем в радианах
		scalar = cos(phi / 2);
		vector = e_vec * sin(phi / 2);
	}
	else
	{
		// считаем, что входной угол в градусах. делаем перевод в радианы
		TYPE angle = deg2rad(phi);

		scalar = cos(angle / 2);
		vector = e_vec * sin(angle / 2);
	};

}


// перегрузка операторов

CQuaternion CQuaternion::operator + (const CQuaternion &Quat){

	CQuaternion Res;

	Res.scalar = scalar + Quat.scalar;
	Res.vector = vector + Quat.vector;

	return Res;
}

// Кватернионное произведение кватернионов
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

// умножение кватерниона на вектор
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

TYPE &CQuaternion::operator [] (SINT i){
	if (i == 0)
	{
		return scalar;
	}
	else if ((i > 0) && (i < QUAT_SIZE))
	{
		return vector[i];
	}
	else // вышли за диапазон
	{
		TYPE res(-1);
		return res;
	}
}

// проверить, нужна ли здесь ссылка
const TYPE &CQuaternion::operator [] (SINT i) const{
	if (i == 0)
	{
		return scalar;
	}
	else if ((i > 0) && (i < QUAT_SIZE))
	{
		return vector[i];
	}
	else // вышли за диапазон
	{
		TYPE res(-1);
		return res;
	}
}


// операторы присвоения

CQuaternion &CQuaternion::operator = (const TYPE scalar){
	this->scalar = scalar;

	return *this;
}

CQuaternion &CQuaternion::operator = (const CVector vector){
	this->vector = vector;

	return *this;
}


// "Свойства" доступа

const TYPE CQuaternion::getScalar() const{
	return scalar;
}

const CVector CQuaternion::getVector() const{
	return vector;
}


// Остальные функции кватерниона

TYPE CQuaternion::getNorm(){
	TYPE Res = 0;

	// проверить нижний индекс
	for (SINT i = 0; i < QUAT_SIZE; i++)
	{
		Res += pow2((*this)[i]);
	}

	return Res;
}

// вычисление сопряженного кватерниона
CQuaternion CQuaternion::getAdjoint(){

	CQuaternion Res(*this);

	Res.vector = vector * -1;

	return Res;
}

/*
	Нормализация кватерниона - деление каждого элемента на норму

	Аналогично нормализации вектора - деление каждого элемента на модуль
*/
void CQuaternion::Normalize(){

	TYPE Norm = getNorm();

	for (SINT i = 0; i < QUAT_SIZE; i++)
	{
		(*this)[i] /= Norm;
	}

}