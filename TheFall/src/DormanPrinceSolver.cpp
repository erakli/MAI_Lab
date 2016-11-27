#include "DormanPrinceSolver.h"

#include <algorithm>
#include <math.h>

#define CONSOLE_OUTPUT

#ifdef CONSOLE_OUTPUT
#include <iostream>
using namespace std;
#endif

Eigen::VectorXd SetValues(TYPE *values)
{
	Eigen::VectorXd Res(SIZE);
	for (int i = 0; i < SIZE; i++)
	{
		Res[i] = values[i];
	}
	return Res;
}



DormanPrinceSolver::DormanPrinceSolver()
{
	// инициализируем все коэффициенты
	m_c.resize(SIZE);
	m_A.resize(SIZE, SIZE);
	m_b.resize(SIZE);
	m_b1.resize(SIZE);

	// заполняем
	Set_c();
	Set_b();
	Set_b1();
	SetA();

	step = 1.0e-3;
//	Error = 1.0e-5;
	m_eps_max = 1.0e-17;
	m_eps_global = 0;

	iter = 0; // количество итераций

	m_rounding_error = RoundingError();	// ошибка округления
}

/*
------------- основная функция
*/
void DormanPrinceSolver::Run(Model &model)
{
	p_model = &model; // Храним адрес модели для внутренних нужд
	p_model->Init(0, nullptr);

	// инициализируем время начальным его значением из модели
	t = p_model->Get_t0();
	x0 = p_model->GetStart();

	// вычисляем размер фазового вектора
	x_size = x0.size();

	m_k.resize(SIZE, x_size);

	TYPE
		t_end = p_model->Get_t1(),
		tout = t;			// Для плотной выдачи

	TYPE out_delta = p_model->GetInterval();

	TYPE new_step;			// храним знание о новом шаге на эту итерацию
	TYPE error;
	UINT local_iter(0);

	Eigen::VectorXd sum(x_size);
	Eigen::VectorXd sum_1(x_size);

#ifdef CONSOLE_OUTPUT
	cout << endl << endl;
	cout << "DormanPrinceSolver::Run" << endl;
	cout << "	t_end = " << t_end << endl;
	cout << "	x0: " << x0.transpose() << endl;
#endif

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

		SetK(x_size);

		sum.fill(0.0);
		sum_1.fill(0.0);

		for (size_t i = 0; i < x_size; i++) // проходим по элементам вектора Х
		{
			for (size_t j = 0; j < SIZE; j++) // собираем воедино все k
			{
				sum(i) += m_b(j) * m_k(j, i);
				sum_1(i) += m_b1(j) * m_k(j, i);
			}
		}

		/*
			прибавляем к вектору начальных условий
			вектор результатов интегрирования.
			для 4 и 5 порядка
		*/
		x1 = x0 + sum * step;
		_x1 = x0 + sum_1 * step;

		error = GetError();
		new_step = StepCorrection(error);	// Запомнили шаг до конца этой итерации
		//if (NewStep > rounding_error)
		step = new_step;
		//else
		//	step = m_eps_max;	// TODO: тут надо подумать, что в случае 0 шага делать

		// если мы не довольны ошибкой, уточняем шаг с текущим t
		if (error > m_eps_max) // ------------------- основной перевалочный пункт
			continue; 

		m_eps_global += error;
		local_iter = 0;

		// если приращение координаты менее заданного условия прерываем процесс
		if (p_model->IsStopCalculation(t, new_step, x0, x1))
		{
			// сохраним более подробные значения перед прерыванием интегрирования
			TYPE stop_delta = out_delta / 10.0;
			tout -= out_delta;
			tout += stop_delta;
			SaveSubstepResult(tout, stop_delta, new_step, t_end);
			break;
		}

		SaveSubstepResult(tout, out_delta, new_step, t_end);

		// на выход отдаём результат 4 порядка (принимая его основным)
		x0 = x1;
		t += new_step;
	}

#ifdef CONSOLE_OUTPUT
	cout << endl;
	cout << "	m_eps_global = " << m_eps_global << endl;
	cout << "	t = " << t << endl;
	cout << "finished" << endl << endl;
#endif
}

/*
------------- Вычисление k-элементов
*/
void DormanPrinceSolver::SetK(int size)
{
	m_k.fill(0.0);
	m_k.row(0) = p_model->GetRight(x0, t);

	Eigen::VectorXd arg;
	Eigen::VectorXd set_k_sum(size);

	for (int s = 1; s < SIZE; s++) // двигаемся по вектору вниз (по строкам)
	{
		// инициализируем элементы-векторы вектора вспомогательных коэфф.
		//k[s].setSize(size);

		set_k_sum.fill(0.0);

		for (int i = 0; i < s; i++) // проходим по строкам m_A, складывая их
		{
			/*
				гуляем по вектор функциям.
				set_k_sum - сумма (та, что в скобках) произведений коэффициентов для каждой
				вектор-функции (которые вычисляются под k)
			*/
			for (int j = 0; j < size; j++)
			{
				set_k_sum(j) += m_A(s, i) * m_k(i, j);
			}
		}

		arg = x0 + set_k_sum * step;
		m_k.row(s) = p_model->GetRight(arg, t + m_c(s) * step);
	}
}



// Сохранение результатов с заданным в модели интервалом
// Результаты уходят в матрицу результатов модели
void DormanPrinceSolver::SaveSubstepResult(TYPE& tout, TYPE delta, TYPE new_step, TYPE t_end)
{
	TYPE Teta;
	Eigen::VectorXd xout; // сюда записываются значения с учётом коэф. плотной выдачи
	while ((tout < t + new_step) && (tout <= t_end))
	{
		Teta = (tout - t) / new_step;
		xout = ThickExtradition(Teta, new_step);
		p_model->AddResult(xout, tout);
		tout += delta;
	}
}



/*
------------- Плотная выдача.
	Необходима для записи результатов на подшагах.
*/
Eigen::VectorXd DormanPrinceSolver::ThickExtradition(TYPE &Teta, TYPE Step)
{
	TYPE sqrTeta;

	sqrTeta = pow(Teta, 2); // квадрат от тета

	static const size_t b_size = 6;

	Eigen::VectorXd b(b_size);

	b(0) = Teta *
		(1.0 + Teta *
		(-1337.0 / 480.0 + Teta * (1039.0 / 360.0 + Teta * (-1163.0 / 1152.0))));

	b(1) = 0.0;

	b(2) = 100.0 * sqrTeta *
		(1054.0 / 9275.0 + 
		Teta * (-4682.0 / 27825.0 + Teta * (379.0 / 5565.0))) / 3.0;

	b(3) = -5.0 * sqrTeta * 
		(27.0 / 40.0 + Teta * (-9.0 / 5.0 + Teta * (83.0 / 96.0))) / 2.0;

	b(4) = 18225.0 * sqrTeta *
		(-3.0 / 250.0 + Teta * (22.0 / 375.0 + Teta * (-37.0 / 600.0))) / 848.0;

	b(5) = -22.0 * sqrTeta *
		(-3.0 / 10.0 + Teta * (29.0 / 30.0 + Teta * (-17.0 / 24.0))) / 7.0;


	Eigen::VectorXd sum = Eigen::VectorXd::Zero(x_size);

	for (size_t i = 0; i < x_size; i++)
	{
		for (size_t j = 0; j < b_size; j++)
		{
			sum(i) += b(j) * m_k(j, i);
		}
	}

	return x0 + sum * Step;

}

/*
------------- Коррекция текущего шага на основе погрешности
*/
TYPE DormanPrinceSolver::StepCorrection(TYPE Error)
{
	TYPE min_part = std::min<TYPE>(5.0, pow(Error / m_eps_max, 0.2) / 0.9);

	return step / std::max<TYPE>(0.1, min_part);
}

/*
------------- Получение локальной погрешности
*/
TYPE DormanPrinceSolver::GetError()
{
	static const TYPE sqrt_x_size = sqrt(TYPE(x_size));
	static TYPE scalar_in_max = 2.0 * m_rounding_error / m_eps_max;

	// числитель и знаменатель дроби под корнем
	Eigen::VectorXd numerator, denominator(x_size), fraction(x_size);

	//TYPE u = RoundingError(); // вычисление ошибки округления

	numerator = step * (x1 - _x1);

	for (int i = 0; i < x_size; i++)
	{
		denominator(i) = std::max<TYPE>({ 1.0e-5, abs(x1(i)), abs(x0(i)), scalar_in_max });
		fraction(i) = numerator(i) / denominator(i);
	}

	// воспользовались нахождением длины вектора
	return fraction.norm() / sqrt_x_size;
}

TYPE DormanPrinceSolver::RoundingError() const
{
	TYPE v(1), u(1);

	while (1 + v > 1)
	{
		u = v;
		v /= 2;
	}

	return u;
}

// -------------- вспомогательные коэффициенты
void DormanPrinceSolver::Set_c()
{
	TYPE prep[SIZE] = { 0, 0.2, 0.3, 0.8, 8.0 / 9.0, 1.0, 1.0 };
	m_c = SetValues(prep);
}

void DormanPrinceSolver::SetA()
{
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

	m_A.fill(0.0);

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < i; j++)
		{
			m_A(i, j) = prep[i][j];
		}
	}
}

void DormanPrinceSolver::Set_b()
{
	TYPE prep[SIZE] =
	{ 35.0 / 384, 0, 500.0 / 1113, 125.0 / 192, -2187.0 / 6784, 11.0 / 84, 0 };
	m_b = SetValues(prep);
}

void DormanPrinceSolver::Set_b1()
{
	TYPE prep[SIZE] =
	{ 5179.0 / 57600, 0, 7571.0 / 16695, 393.0 / 640, -92097.0 / 339200, 187.0 / 2100, 1.0 / 40 };
	m_b1 = SetValues(prep);
}


// ------------ инкапсуляция
void DormanPrinceSolver::SetEpsMax(TYPE arg)
{
	m_eps_max = arg;
}

//void DormanPrinceSolver::setEps(const TYPE &arg)
//{
//	Error = arg;
//}

TYPE DormanPrinceSolver::GetEpsMax() const
{
	return m_eps_max;
}

TYPE DormanPrinceSolver::GetIter() const
{
	return iter;
}

TYPE DormanPrinceSolver::GetEpsGlobal() const
{
	return m_eps_global;
}