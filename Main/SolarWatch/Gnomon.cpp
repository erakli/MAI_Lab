#include <iterator>
//#include  "file_output.h"

#include "Coordinates.h"
#include "Time.h"

#include "Integrator.h"
#include "SolarSystem.h"

#include "Gnomon.h"

#define START_OF_THIS_YEAR JD2016

using namespace MyTime;

/* private */

/*
	А есть ли у нас данная дата среди посчитанных?
*/
bool CGnomon::DoWeHaveThisDate(const TYPE theDate, Earth::CEarth &Mod)
{
	if (lastActual_JD > 0)		// есть ли у нас посчитанная дата?
	{
		/* Да, есть. Есть ли искомая дата среди посчитанных? */
		if (theDate <= getMidnight(lastActual_JD))
		{
			CVector knownPosition(
				earthPosition_Day[int(theDate - START_OF_THIS_YEAR)]);
			knownPosition.pop_back(); // отсекли время

			Mod.setStart(knownPosition);
			return true;		// отлично! мы можем пропустить первый этап!
		}
		else
		{
			/*
				Нет, искомой даты среди посчитанных нет. Начнём интегрировать
				от последней известной даты
			*/
			CVector
				knownPosition(
					earthPosition_Day[earthPosition_Day.getRowCount() - 1]
				);
			knownPosition.pop_back(); // отсекли время

			Mod.setStart(knownPosition);

			/*
				Первый этап пропускать нельзя. Начальным врменем будет последняя
				известная дата
			*/
			Mod.set_t0(lastActual_JD * SECINDAY);

			lastActual_JD = theDate;
		}
	}
	else
		// нет, посчитанной даты нет, теперь эта дата будет последней посчитанной
		lastActual_JD = theDate;

	return false;
}


void CGnomon::MakeNewStartConditions(Earth::CEarth &Mod)
{
	// храним посчитанную часть года на будущее
	earthPosition_Day.add_toEnd(Mod.getResult());

	// Подготовка второго этапа
	CVector forStart;
	forStart = Mod.getLastResult();
	forStart.pop_back();	// вырезали время из вектора
	Mod.clearResult();	// очистили контейнер результатов перед вторым этапом

	Mod.setStart(forStart);
	Mod.set_t0(Mod.get_t1());
}

//void CGnomon::MakeNewStartConditions_forTimeZone(
//	Earth::CEarth &Mod, CDormanPrince &Integrator, const TYPE timeMoment)
//{
//	Mod.setInterval(SECINDAY / HOURINDAY);
//	Mod.set_t1(timeMoment, true);
//
//	Integrator.Run(Mod);
//
//	MakeNewStartConditions(Mod, false);
//}

/*
	Интегрируем до полуночи искомой даты, начиная с полуночи 
	интегрируем с определённым интервалом и заполняем вектор 
	положений Земли на текущую дату
*/
void CGnomon::getEarthPosition(const TYPE JD, const bool day)
{
	CDormanPrince Integrator;
	Earth::CEarth Model;
	Integrator.setEps_Max(PRECISION);

	// моделирование до определённой даты
	if (day)
	{
		// Полночь заданного дня
		TYPE midNight = getMidnight(JD);

	/* Проверяем, известна ли нам позиция на этот день */
		bool WeAlsoKnowIt(DoWeHaveThisDate(midNight, Model));	

	/* Первый этап интегрирования, до искомого дня */
		if (!WeAlsoKnowIt)
		{
			Model.setInterval(SECINDAY);

			/*
				Рассматриваем случай часовых поясов (ЧП).

				Если ЧП отличен от Гринвича, то сначала интегрируем до предыдущего
				дня с интервалом в сутки.
			*/
			if (timeZone <= 0)
				Model.set_t1(midNight * SECINDAY);
			else
				Model.set_t1((midNight - 1) * SECINDAY);

			Integrator.Run(Model);

			// задаём новые НУ на основании вычислений
			MakeNewStartConditions(Model);

		}

	/* Второй этап, на целый день с интервалом в минуту */
		Model.setInterval(SECINMIN);
		//Model.set_t0(midNight - timeZone / 24.0, true);

		if (timeZone == 0)
			// до след. полночи (без включения самой полуночи)
			Model.set_t1(Model.get_t0() + SECINDAY - SECINMIN);
		else
			// иначе на 2 суток вперёд, чтобы покрыть часовые пояса
			Model.set_t1(Model.get_t0() + 2 * SECINDAY - SECINMIN);

		Integrator.Run(Model);

		/*
			На выход отдаём положения Земли с интервалом в 1 минуту
			на искомый день
			*/
		earthPosition_Minute = Model.getResult();
	}	
	// ---------------------------------------------------------END OF if (day)

	else
	{	// моделируем на весь чёртов год!
		
		/*	Модель в данной функции создаётся с помощью конструктора по-умолчанию,
			в котором начальные условия даны на 1 января 2016 года, а t1 
			установлено на 1 января 2017 года. */
		Model.setInterval(SECINMIN);

		Integrator.Run(Model);

		/*
			На выход отдаём положения Земли на весь год с интервалом в 1 
			минуту
		*/
		earthPosition_Minute = Model.getResult();
	}
}


/*
	Расчёт геоцентрического декартового положения гномона на текущий момент
*/
CVector CGnomon::getPosition(const TYPE t)
{
	curPosition[2] = StarTime(starTimeAtStart, t);
	//curPosition[2] = StarTime(t, position[2]);

	return Transform::Geographic2Fix(curPosition);
}


/*
	Считаем время до рассвета и заката
*/
void CGnomon::CountTimeInDay(
	const bool WorkTime,
	CMatrix& days_of_year, UINT &day_number, bool& SunriseGot, 
	const TYPE scalarProd, const TYPE delta, const int i)
{
	if (scalarProd > 0)
	{
		if (!SunriseGot)
			// увеличиваем счётчик до рассвета на смещение delta
			days_of_year[0][day_number] += delta;
	}
	else
	{
		// как только наступил рассвет ставим флаг, чтобы больше не считать тёмное время
		if (!SunriseGot) SunriseGot = true;
		// считаем время до заката
		days_of_year[1][day_number] += delta;
	}

	/*
		если количество итераций дошло до кратного полуночи числа,
		увеличиваем номер дня */
	if (i % (MININDAY) == 0 && i != 0)
	{
		// учитываем часовой пояс
		days_of_year[0][day_number] += timeZone * SECINHOUR;

		/*
			в конце дня прибавляем к счётчику заката время до рассвета,
			чтобы получить реальное время заката */
		days_of_year[1][day_number] += days_of_year[0][day_number];

		// учёт рабочего светлого времени от 8 до 20 часов. Если истина, то обрезаем
		if (WorkTime)
		{
			if (days_of_year[0][day_number] < 8 * SECINHOUR)
				days_of_year[0][day_number] = 8 * SECINHOUR;

			if (days_of_year[1][day_number] > 20 * SECINHOUR)
				days_of_year[1][day_number] = 20 * SECINHOUR;
		}

		SunriseGot = false;
		day_number++;
	}
}



/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
*	Симуляция движения тени гномона заданной высоты в заданной позиции
*	на данную дату с заданным интервалом
*
*	Результат работы функции - список положений тени в МГП (в топоцентрической СК)
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
CMatrix CGnomon::SimulateShadow(const bool WorkTime, const bool days)
{
	// по новой инициализируем текущую позицию (будем вращать через getPosition)
	curPosition = position;

	TYPE
		curTime = 0,	// полночь UTC+0
		delta = SECINMIN;	// смещение при вычислении curTime

	// для подсчёта светлого времени в секундах: рассвет, закат
	CMatrix days_of_year(2, DAYS_IN_CURRENT_YEAR);
	UINT day_number(0);

	bool SunriseGot = false;	// рассчитали ли мы для текущего дня рассвет и закат

	/* 
		если есть смещение часового пояса, то моделирование проводилось на 2 дня,
		значит нам надо перескочить часть светлого времени предыдущего дня */
	bool long_period_modelling_flag = (timeZone) ? true : false;

/* 
	Вектор тени может быть определен как сумма векторов: 
*/
	for (int i = 0; i < earthPosition_Minute.getRowCount(); i++)
	{

	/* 
		1. вектор, совпадающий по направлению и равный по длине гномон
	*/
		CVector
			// вектор точки расположения гномона в инерциальной геоцентрической СК
			gnomonPos(getPosition(curTime)),
			posNormalized, gnomonVector;

		posNormalized = gnomonPos * (1 / gnomonPos.getLength());
		gnomonVector = posNormalized * height;

		curTime += delta;	// увеличиваем текущее время на интервал в сек
	
	/*
		2. вектор, совпадающий по направлению с вектором луча света и
		соединяющий верхний конец гномона и МГП
	*/
		CVector
			earthPos,
			rayNormalized, rayVector;

		// отсекаем скорость и время
		earthPos = CVector::copyPart(earthPosition_Minute[i], 2);  

		rayNormalized = earthPos * (1 / earthPos.getLength());

		/* 
			По знаку склярного произведения единичного вектора позиции гномона
			и единичного вектора позиции Земли определяем нахождение
			гномона в тени Земли
		*/
		TYPE scalarProd = rayNormalized * posNormalized;

		// ------------------------- вычисляем на конкретную дату положения гномона
		if (days)
		{
			/*
				Если у нас часовой пояс, то мы работаем в расширенном диапазоне.
				Продолжаем до тех пор, пока не достигнем позиции Земли на 
				полночь по местному времени */
			if (long_period_modelling_flag)
			{
				if (timeZone > 0)	// UTC+N
				{
					if (i < MININDAY - timeZone * MININHOUR)
						continue;
				}
				else  	// UTC-N
				{
					if (i < -timeZone * MININHOUR)
						continue;

					/* 
						на случай UTC-N, отслеживаем моделирование на сутки - 
						чтобы мы не залезли на следующий день по местному времени */
					if (i > MININDAY - timeZone * MININHOUR)
						break;
				}
			}

			if (scalarProd > 0)	// мы в тени, исследуем след. позиции
				continue;

			// наконец мы не в тени, продолжаем вычислять вектор тени в Инерц. СК
			rayVector = rayNormalized * (-height / scalarProd);

			addResult(Transform::Fix2Topo(rayVector + gnomonVector, curPosition));

		}
		// ------------------- иначе считаем количество светлых минут в каждом дней
		else  
		{	
			CountTimeInDay(
				WorkTime, 
				days_of_year, day_number, SunriseGot,
				scalarProd, delta, i);
		}	// ENDOF if (days)
	}

	/* 
		если расчёт вели на год, то добавляем единственный вектор с количеством 
		светлого времени по дням */
	if (!days)
	{
		addResult(days_of_year[0]);
		addResult(days_of_year[1]);
	}

	//CMatrix Res(MININDAY, 1);
	return getResult();
}

/*
	Работа со списком результатов
*/
void CGnomon::addResult(const CVector& X)
{
	Result.push_back(X);
	Result_size++;
}

/*
	Выводим результат сразу в метры
*/
CMatrix CGnomon::getResult()
{
	// -------------------------------------- сделать с помощью итераторов!
	/*BaseMatrix Output0
	{ 
		std::make_move_iterator(std::begin(Result)),
		std::make_move_iterator(std::end(Result)) 
	};*/

	CMatrix Output;

	Output.reserve(Result_size);

	std::copy(Result.begin(), Result.end(), std::back_inserter(Output));

	return Output;
}

void CGnomon::clearResult()
{
	Result.clear();
	Result_size = 0;
}

/* public */

CGnomon::CGnomon(const TYPE fi, const TYPE lambda, const SINT timeZone,
				 const TYPE height)
{
	position.setSize(3);
	position[1] = fi;
	position[2] = lambda;

	this->timeZone = timeZone;

	this->height = height;

	Result_size = 0;
	lastActual_JD = 0;

	starTimeAtStart = 0;
}

void CGnomon::setParam(const TYPE fi, const TYPE lambda, const SINT timeZone,
					   const TYPE height)
{
	position.setSize(3);
	position[1] = fi;
	position[2] = lambda;

	this->timeZone = timeZone;

	this->height = height;

	starTimeAtStart = 0;
}

CMatrix CGnomon::GetShadowForDate(const TYPE JD)
{
	/* 
		Рассчёт звёздного времени на начало моделирования. Прибавляем lambda 
		(долготу места), вычитаем часовой пояс */
	if (timeZone == 0)
		starTimeAtStart = StarTime(getMidnight(JD)) + position[2];
			//- Earth::CEarth::angularVeloc * timeZone * 3600;
	else
		starTimeAtStart = StarTime(getMidnight(JD - 1)) + position[2];

	// Расчитываем положение Земли на текущий день
	getEarthPosition(JD);

	CMatrix Shadow(SimulateShadow());	// собрали информацию о движении тени
	clearResult();	// очистили лист с результатами

	return Shadow * 1000;
}

CVector CGnomon::GetLightTimeForYear()
{
	/*
		Рассчёт звёздного времени на начало моделирования. Прибавляем lambda
		(долготу места), вычитаем часовой пояс */
	starTimeAtStart =
		StarTime(getMidnight(START_OF_THIS_YEAR))
		+ position[2];
		//- Earth::CEarth::angularVeloc * timeZone * 3600;

	// Расчитываем положение Земли на год
	getEarthPosition(0, false);

	/*
		Рассчитываем светлое время по дням, записываем в вектор.

		0-ой индекс - из-за особенностей реализации результатом
		SimulateShadow является матрица. Наш результат - единственная строчка
		полученной матрицы
	*/
	CMatrix LightTime(SimulateShadow(true, false));
	clearResult();

	CVector Result(DAYS_IN_CURRENT_YEAR);

	for (int i = 0; i < DAYS_IN_CURRENT_YEAR; i++)
		Result[i] = LightTime[1][i] - LightTime[0][i];

	return Result;
}
