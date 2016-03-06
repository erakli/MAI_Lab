#include "Integrator.h"
#include <algorithm>
#include <math.h>

CVector SetValues(TYPE *values){
	CVector Res(SIZE);
	for (int i = 0; i < SIZE; i++)
	{
		Res[i] = values[i];
	}
	return Res;
}

/* * * * * * * * * * TIntegrator * * * * * * * * * */
TIntegrator::TIntegrator(){
	Step = 1;
}

TYPE TIntegrator::getStep() const{
	return Step;
}
void TIntegrator::setStep(const TYPE &arg){
	Step = arg;
}

/* * * * * * * * * * CDormanPrince * * * * * * * * * */
CDormanPrince::CDormanPrince(){

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
	Eps = 1.0e-5;
	Eps_Max = 1.0e-17;
	Eps_Global = 0;

	iter = 0; // количество итераций

}

/*
------------- основная функция
*/
void CDormanPrince::Run(CModel &Mod){

	Model = &Mod; // Храним адрес модели для внутренних нужд

	// инициализируем время начальным его значением из модели
	t = Model->get_t0(); 
	x0 = Model->getStart();

	// вычисляем размер фазового вектора
	x_size = x0.getSize(); 

	TYPE tout = t; // Для плотной выдачи
	TYPE PrevStep; // храним знание о предыдущем шаге

	/*
		основной цикл вычисления
	*/
	while (t <= Model->get_t1())
	{
		// необходим контроль количества итераций
		if (iter < 1000) iter++;
		else
			break;

		set_k(x_size);

		CVector sum(x_size), sum_1(sum);

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

		PrevStep = Step; // Запомнили шаг до конца этой итерации
		getEps();
		StepCorrection();	

		// если мы не довольны ошибкой, уточняем шаг с текущим t
		if (Eps > Eps_Max)	continue; // ------------------- основной перевалочный пункт

		Eps_Global += Eps; // считаем глобальную погрешность как сумму локальных

		iter = 0; // обнуляем счётчик количества итераций при успехе шага

		// если приращение координаты менее заданного условия прерываем процесс
		if (Model->Stop_Calculation(t, PrevStep, x0, x1)) break;

		/*
			Плотная выдача. Результаты уходят в матрицу
			результатов модели
		*/
		TYPE Teta;
		CVector Xout; // сюда записываются значения с учётом коэф. плотной выдачи
		while ((tout < t + PrevStep) && (tout <= Model->get_t1()))
		{
			Teta = (tout - t) / PrevStep;
			Xout = thick_extradition(Teta, PrevStep);
			Model->addResult(Xout, tout);
			tout += Model->getInterval();
		}

		x0 = x1; // на выход отдаём результат 4 порядка (принимая его основным)
		t += PrevStep;
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
		k[s].setSize(size);

		CVector sum(size);

		for (int i = 0; i < s; i++) // проходим по строкам A, складывая их
		{
			/* 
				гуляем по вектор функциям.
				sum - сумма (та, что в скобках) произведений коэффициентов для каждой 
				вектор-функции (которые вычисляются под k)
			*/
			for (int j = 0; j < size; j++)
			{
				sum[j] += A[s][i] * k[i][j];
			}
		}

		k[s] = Model->getRight(x0 + sum * Step, t + c[s] * Step);
	}
}

/*
------------- Плотная выдача. 
	Необходима для записи результатов на подшагах.
*/
CVector CDormanPrince::thick_extradition(TYPE &Teta, TYPE &Step){
	TYPE sqrTeta;

	sqrTeta = pow(Teta, 2); // квадрат от тета

	const int b_size = 6;

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
void CDormanPrince::StepCorrection(){
	TYPE min_part =
			std::min<TYPE>
			(5.0, pow(Eps / Eps_Max, 0.2) / 0.9);

	Step /= std::max<TYPE>(0.1, min_part);
}

/*
------------- Получение локальной погрешности
*/
void CDormanPrince::getEps(){

	// числитель и знаменатель дроби под корнем
	CVector numerator(x_size), denominator(x_size), fraction(x_size);
	
	TYPE u = RoundingError(); // вычисление ошибки округления

	for (int i = 0; i < x_size; i++)
	{
		numerator[i] = Step * (x1[i] - _x1[i]);
		denominator[i] =
			std::max<TYPE>(
			std::max<TYPE>(1.0e-5, abs(x1[i])),
			std::max<TYPE>(abs(x0[i]), 2.0 * u / Eps_Max)
			);
		fraction[i] = numerator[i] / denominator[i];
	}

	// воспользовались нахождением длины вектора
	Eps = fraction.getLength() / sqrt((TYPE)x_size);	
	
}

TYPE CDormanPrince::RoundingError(){
	TYPE v(1), u;

	while (1 + v > 1)
	{
		u = v;
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
	Eps = arg;
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