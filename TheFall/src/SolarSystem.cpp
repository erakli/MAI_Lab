#include <iterator>

#include  "Functions.h"
#include "Time.h"

#include "SolarSystem.h"

using namespace Eigen;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* * * Earth                                          * * * */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

const TYPE
	Earth::muEarth = 398600.436,	// геоцентрическая гравитационная постоянная, [km^3/s^2]
	Earth::angularVeloc = 7.292115e-5,	// угловая скорость вращения, рад/с
	Earth::meanRadius = 6371.3,		// средний радиус для сферической земли, км
	Earth::ae = 6378.136;				// большая полуось ОЗЭ (общеземного эллипсоида), км

/* Господа конструкторы (+ по дате и позиции) */

Earth::Earth()
{
	m_start_values.resize(6);	// гелиоцентрическое положение + скорость
	s_size = m_start_values.size();
	
	/*
		1.1.2016
	*/
	m_start_values(0) = -2.439276441307208e+7;
	m_start_values(1) =  1.332124993767647e+8;
	m_start_values(2) =  5.772281789058973e+7;

	m_start_values(3) = -2.984063142864898e+1;
	m_start_values(4) = -4.727555397178124;
	m_start_values(5) = -2.049346856618893;

	t0 = JD2016 * SECINDAY;
	t1 = t0 + DAYS_IN_CURRENT_YEAR * SECINDAY;
}

Earth::Earth(const TYPE JD)
{
	m_start_values.resize(6);	// гелиоцентрическое положение + скорость
	s_size = m_start_values.size();

	/*
		Положение и скорость в экваториальной гелиоцентрической СК
		В км и км/с соответственно
	*/
	if (JD == JD2016)
	{
		m_start_values(0) = -2.439276441307208e+7;
		m_start_values(1) = 1.332124993767647e+8;
		m_start_values(2) = 5.772281789058973e+7;

		m_start_values(3) = -2.984063142864898e+1;
		m_start_values(4) = -4.727555397178124;
		m_start_values(5) = -2.049346856618893;
	}
	else
	if (JD == 2457468.5)
	{
		m_start_values(0) = -1.484512468045209e+8;
		m_start_values(1) = -1.117361282251260e+6;
		m_start_values(2) = -5.101193558950569e+5;

		m_start_values(3) = -1.813507346095267e-1;
		m_start_values(4) = -2.742106189673085e+1;
		m_start_values(5) = -1.188731012157166e+1;
	}
	else
	if (JD == 2457561.5)
	{
		m_start_values(0) = 2.646770613778915e+6;
		m_start_values(1) = -1.391168307821974e+8;
		m_start_values(2) = -6.033492142652344e+7;

		m_start_values(3) = 2.929880927153534e+1;
		m_start_values(4) = 2.845999982294178e-1;
		m_start_values(5) = 1.232505993914231e-1;
	}
	else
	if (JD == 2457654.5)
	{
		m_start_values(0) = 1.506473988158580e+8;
		m_start_values(1) = 8.608380672583859e+5;
		m_start_values(2) = 3.462104807619269e+5;

		m_start_values(3) = -5.758350444110057e-1;
		m_start_values(4) = 2.724025582030263e+1;
		m_start_values(5) = 1.180895196291067e+1;
	}
	else
	if (JD == 2457744.5)
	{
		m_start_values(0) = -3.488250688338019e+5;
		m_start_values(1) = 1.355541180476501e+8;
		m_start_values(2) = 5.873831689579538e+7;

		m_start_values(3) = -3.027784098174831e+1;
		m_start_values(4) = -2.507359785692029e-1;
		m_start_values(5) = 1.084393412860461e-1;
	}
		
	t0 = JD * SECINDAY;
	t1 = t0 + 365 * SECINDAY;
}

Earth::Earth(const VectorXd &stateVector, const TYPE start)
{
	m_start_values = stateVector;
	s_size = m_start_values.size();

	t0 = start * SECINDAY;
	t1 = t0 + 365 * SECINDAY;
}

Earth::Earth(const Earth &copy_earth)
{
	m_start_values = copy_earth.m_start_values;
	s_size = m_start_values.size();

	t0 = copy_earth.Get_t0();
	t1 = copy_earth.Get_t1();
}


/*
	Храним время в конце вектора
*/
void Earth::AddResult(const VectorXd& X, double t)
{
	VectorXd compile(X.size() + 1); // вектор результата + время
	compile << X, t;

	m_result.row(last_result_idx) = compile;
	last_result_idx++;
}

/*
	Правая часть ДУ невозмущённого кеплеровского движения
	Земли вокруг Солнца
*/
VectorXd Earth::GetRight(const VectorXd& X, TYPE t) const
{
	VectorXd Res(s_size);

	TYPE
		module = X.head(2).norm(),
		//		= CVector::copyPart(X, 2).getLength(),
		moduleX3 = pow(module, 3);

	/* 
		Замена переменной, интегрируем второй
		раз проинтегрированную 2 производную
	*/
	Res(0) = X(3);
	Res(1) = X(4);
	Res(2) = X(5);

	Res(3) = -Sun::muSun * X(0) / moduleX3;
	Res(4) = -Sun::muSun * X(1) / moduleX3;
	Res(5) = -Sun::muSun * X(2) / moduleX3;

	return Res;
}