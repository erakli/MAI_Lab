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
	else // вышли за диапазон
	{
		//TYPE res(-1);
		//return 0;
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
		return vector[i - 1];
	}
	else // вышли за диапазон
	{
		//TYPE res(-1);
		//return 0;
	}
}


// операторы присвоения

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


// конструкторы

CQuaternion::CQuaternion(TYPE lam_0, TYPE lam_1, TYPE lam_2, TYPE lam_3){

	/* С этим конструктором вообще не понятно */

	vector.setSize(VEC_PART_SIZE);
	vector[0] = lam_1;
	vector[1] = lam_2;
	vector[2] = lam_3;

	scalar = lam_0;

	// lambda_0 выбирается из условия lam_0^2 + lam_1^2 + ... = 1
	//TYPE check;
	//check = vector.getLength();

	/* 
		сделать проверку на check > 1
		в принципе, нужно такое делать? 
	*/

	//scalar = (1 == check + pow2(lam_1)) ? lam_0 : sqrt(1 - check);

}

CQuaternion::CQuaternion(TYPE phi, const CVector &e_vec, const bool radians){

	vector.setSize(VEC_PART_SIZE); // на всякий случай

	CVector axis(e_vec);
	axis.Normalize(); // обязательно нормализуем

	if (radians)
	{
		// считаем в радианах
		scalar = cos(phi / 2);
		vector = axis * sin(phi / 2);
	}
	else
	{
		// считаем, что входной угол в градусах. делаем перевод в радианы
		TYPE angle = MyFunc::Numbers::deg2rad(phi);

		scalar = cos(angle / 2);
		vector = axis * sin(angle / 2);
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
		Res += MyFunc::Numbers::pow2((*this)[i]);
	}

	return Res;
}

TYPE CQuaternion::getLength(){
	return sqrt(getNorm());
}

// вычисление сопряженного кватерниона
CQuaternion CQuaternion::getAdjoint(){

	CQuaternion Res(*this);

	Res.vector = vector * -1;

	Res.Normalize(); // на всякий случай нормализуем сразу же

	return Res;
}

/*
	Нормализация кватерниона - деление каждого элемента на норму

	Аналогично нормализации вектора - деление каждого элемента на модуль
*/
void CQuaternion::Normalize(){

	// делим не на норму а на модуль кватерниона (как с векторами)
	TYPE Norm = getLength();

	for (SINT i = 0; i < QUAT_SIZE; i++)
	{
		(*this)[i] /= Norm;
	}

}