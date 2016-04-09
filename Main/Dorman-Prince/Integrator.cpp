#include <algorithm>
#include <math.h>

#include "Integrator.h"

CVector SetValues(TYPE *values){
	CVector Res(SIZE);
	for (int i = 0; i < SIZE; i++)
	{
		Res[i] = values[i];
	}
	return Res;
}

/* * * * * * * * * * TIntegrator * * * * * * * * * */
TIntegrator::TIntegrator()
{
	Model = nullptr;

	t = 0;
	Step = 1;
}

TYPE TIntegrator::getStep() const
{
	return Step;
}
void TIntegrator::setStep(const TYPE &arg)
{
	Step = arg;
}

/* * * * * * * * * * CDormanPrince * * * * * * * * * */
CDormanPrince::CDormanPrince()
{
	// инициализируем все коэффициенты
	c.setSize(SIZE);
	A.setSize(SIZE, SIZE);
	b.setSize(SIZE);
	b1.setSize(SIZE);

	// заполняем
	set_c();
	set_b();
	set_b1();
	setA();

	Step = 1.0e-3;
	Error = 1.0e-5;
	Eps_Max = 1.0e-17;
	Eps_Global = 0;

	iter = 0; // количество итераций

	RoundErr = RoundingError();	// ошибка округления
}

/*
------------- основная функция
*/
void CDormanPrince::Run(CModel &Mod)
{
	Model = &Mod; // Храним адрес модели для внутренних нужд
	Model->setResultType();	// задаём тип контейнера для хранения результатов

	// инициализируем время начальным его значением из модели
	t = Model->get_t0(); 
	x0 = Model->getStart();

	// вычисляем размер фазового вектора
	x_size = x0.getSize(); 

	TYPE
		t_end = Model->get_t1(),
		tout = t;			// Для плотной выдачи
	TYPE NewStep;			// храним знание о новом шаге на эту итерацию

	UINT local_iter(0);

	/*
		основной цикл вычисления
	*/
	while (t <= t_end)
	{
		// необходим контроль количества итераций
		if (local_iter < 1000)
		{
			iter++;
			local_iter++;
		}
		else
			break;

		set_k(x_size);

		CVector sum(x_size), sum_1(x_size);

		for (int i = 0; i < x_size; i++) // проходим по элементам вектора Х
		{
			for (int j = 0; j < SIZE; j++) // собираем воедино все k
			{
				sum[i] += b[j] * k[j][i];
				sum_1[i] += b1[j] * k[j][i];
			}
		}

		/*
			прибавляем к вектору начальных условий
			вектор результатов интегрирования.
			для 4 и 5 порядка
		*/
		x1 = x0 + sum * Step;
		_x1 = x0 + sum_1 * Step;

		getError();
		NewStep = StepCorrection();	// Запомнили шаг до конца этой итерации
		//if (NewStep > RoundErr)
			Step = NewStep;
		//else
		//	Step = Eps_Max;	// TODO: тут надо подумать, что в случае 0 шага делать

		// если мы не довольны ошибкой, уточняем шаг с текущим t
		if (Error > Eps_Max) continue; // ------------------- основной перевалочный пункт

		Eps_Global += Error; // считаем глобальную погрешность как сумму локальных

		local_iter = 0; // обнуляем счётчик количества итераций при успехе шага

		// если приращение координаты менее заданного условия прерываем процесс
		if (Model->Stop_Calculation(t, NewStep, x0, x1)) break;

		/*
			Плотная выдача. Результаты уходят в матрицу
			результатов модели
		*/
		TYPE Teta;
		CVector Xout; // сюда записываются значения с учётом коэф. плотной выдачи
		while ((tout < t + NewStep) && (tout <= t_end))
		{
			Teta = (tout - t) / NewStep;
			Xout = thick_extradition(Teta, NewStep);
			Model->addResult(Xout, tout);
			tout += Model->getInterval();
		}

		x0 = x1; // на выход отдаём результат 4 порядка (принимая его основным)
		t += NewStep;
	}
}

/*
------------- Вычисление k-элементов
*/
void CDormanPrince::set_k(int size){

	k[0] = Model->getRight(x0, t);

	for (int s = 1; s < SIZE; s++) // двигаемся по вектору вниз (по строкам)
	{
		// инициализируем элементы-векторы вектора вспомогательных коэфф.
		//k[s].setSize(size);

		CVector set_k_sum(size);

		for (int i = 0; i < s; i++) // проходим по строкам A, складывая их
		{
			/* 
				гуляем по вектор функциям.
				set_k_sum - сумма (та, что в скобках) произведений коэффициентов для каждой 
				вектор-функции (которые вычисляются под k)
			*/
			for (int j = 0; j < size; j++)
			{
				set_k_sum[j] += A[s][i] * k[i][j];
			}
		}

		k[s] = Model->getRight(x0 + set_k_sum * Step, t + c[s] * Step);
	}
}

/*
------------- Плотная выдача. 
	Необходима для записи результатов на подшагах.
*/
CVector CDormanPrince::thick_extradition(TYPE &Teta, TYPE &Step){
	TYPE sqrTeta;

	sqrTeta = pow(Teta, 2); // квадрат от тета

	static const auto b_size = 6;

	CVector b(b_size);

	b[0] = Teta *
		(1.0 + Teta *
		(-1337.0 / 480 + Teta * (1039.0 / 360 + Teta * (-1163.0 / 1152))));

	b[1] = 0;

	b[2] = 100.0 * sqrTeta *
		(1054.0 / 9275 + Teta * (-4682.0 / 27825 + Teta * (379.0 / 5565))) / 3;

	b[3] = -5.0 * sqrTeta * (27.0 / 40 + Teta * (-9.0 / 5 + Teta * (83.0 / 96))) / 2;

	b[4] = 18225.0 * sqrTeta *
		(-3.0 / 250 + Teta * (22.0 / 375 + Teta * (-37.0 / 600))) / 848;

	b[5] = -22.0 * sqrTeta *
		(-3.0 / 10 + Teta * (29.0 / 30 + Teta * (-17.0 / 24))) / 7;


	CVector sum(x_size);
	for (int i = 0; i < x_size; i++)
	{
		for (int j = 0; j < b_size; j++)
		{
			sum[i] += b[j] * k[j][i];
		}
	}

	return x0 + sum * Step;

}

/*
------------- Коррекция текущего шага на основе погрешности
*/
TYPE CDormanPrince::StepCorrection(){
	TYPE min_part =
			std::min<TYPE>
			(5.0, pow(Error / Eps_Max, 0.2) / 0.9);

	return Step / std::max<TYPE>(0.1, min_part);
}

/*
------------- Получение локальной погрешности
*/
void CDormanPrince::getError(){

	// числитель и знаменатель дроби под корнем
	CVector numerator(x_size), denominator(x_size), fraction(x_size);
	
	//TYPE u = RoundingError(); // вычисление ошибки округления

	for (int i = 0; i < x_size; i++)
	{
		numerator[i] = Step * (x1[i] - _x1[i]);
		denominator[i] =
			std::max<TYPE>(
			std::max<TYPE>(1.0e-5, abs(x1[i])),
			std::max<TYPE>(abs(x0[i]), 2.0 * RoundErr / Eps_Max)
			);
		fraction[i] = numerator[i] / denominator[i];
	}

	// воспользовались нахождением длины вектора
	Error = fraction.getLength() / sqrt(TYPE(x_size));	
	
}

TYPE CDormanPrince::RoundingError() const{
	TYPE v(1), u(1);

	while (1 + v > 1)
	{
		u =	v;
		v /= 2;
	}

	return u;
}

// -------------- вспомогательные коэффициенты
void CDormanPrince::set_c(){
	TYPE prep[SIZE] = { 0, 0.2, 0.3, 0.8, 8.0 / 9, 1, 1 };
	c = SetValues(prep);
}

void CDormanPrince::setA(){
	TYPE prep[SIZE][SIZE] =
	{
		{},
		{ 0.2 },
		{ 3.0 / 40, 9.0 / 40 },
		{ 44.0 / 45, -56.0 / 15, 32.0 / 9 },
		{ 19372.0 / 6561, -25360.0 / 2187, 64448.0 / 6561, -212.0 / 729 },
		{ 9017.0 / 3168, -355.0 / 33, 46732.0 / 5247, 49.0 / 176, -5103.0 / 18656 },
		{ 35.0 / 384, 0, 500.0 / 1113, 125.0 / 192, -2187.0 / 6784, 11.0 / 84, 0 }
	};

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < i; j++)
		{
			A[i][j] = prep[i][j];
		}
	}
}

void CDormanPrince::set_b(){
	TYPE prep[SIZE] = 
	{ 35.0 / 384, 0, 500.0 / 1113, 125.0 / 192, -2187.0 / 6784, 11.0 / 84, 0 };
	b = SetValues(prep);
}

void CDormanPrince::set_b1(){
	TYPE prep[SIZE] =
	{ 5179.0 / 57600, 0, 7571.0 / 16695, 393.0 / 640, -92097.0 / 339200, 187.0 / 2100, 1.0 / 40 };
	b1 = SetValues(prep);
}


// ------------ инкапсуляция
void CDormanPrince::setEps_Max(const TYPE &arg){
	Eps_Max = arg;
}

void CDormanPrince::setEps(const TYPE &arg){
	Error = arg;
}

TYPE CDormanPrince::getEps_Max() const{
	return Eps_Max;
}

TYPE CDormanPrince::get_iter() const{
	return iter;
}

TYPE CDormanPrince::getEps_Global() const{
	return Eps_Global;
}