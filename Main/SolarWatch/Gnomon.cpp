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
			CVector knownPosition(earthPosition_Day[int(theDate - START_OF_THIS_YEAR)]);
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
			Mod.set_t0(lastActual_JD, true);

			lastActual_JD = theDate;
		}
	}
	else
		// нет, посчитанной даты нет, теперь эта дата будет последней посчитанной
		lastActual_JD = theDate;

	return false;
}


void CGnomon::MakeNewStartConditions(Earth::CEarth &Mod, const bool for_Midnight_flag)
{
	// храним посчитанную часть года на будущее
	earthPosition_Day.add_toEnd(Mod.getResult());

	// Подготовка второго этапа
	CVector forStart;
	forStart = Mod.getLastResult();
	forStart.pop_back();	// вырезали время из вектора
	Mod.clearResult();	// очистили контейнер результатов перед вторым этапом

	Mod.setStart(forStart);
	Mod.set_t0(Mod.get_t1(), false);
}

void CGnomon::MakeNewStartConditions_forTimeZone(
	Earth::CEarth &Mod, CDormanPrince &Integrator, const TYPE timeMoment)
{
	Mod.setInterval(SECINDAY / 24.0);
	Mod.set_t1(timeMoment, true);

	Integrator.Run(Mod);

	MakeNewStartConditions(Mod, false);
}

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
				дня с интервалом в сутки, а затем до момента интересующего нас
				дня минус timeZone с интервалом в час. Полученный момент и станет
				новыми начальными условиями для интегрирования на интересующий
				день.
			*/
			if (timeZone <= 0)
				Model.set_t1(midNight, true);
			else
				Model.set_t1(midNight - 1, true);

			Integrator.Run(Model);
			MakeNewStartConditions(Model, true);	// задаём новые НУ на основании вычислений

		}

	/* Второй этап, на целый день с интервалом в минуту */
		Model.setInterval(SECINMIN * interval);
		//Model.set_t0(midNight - timeZone / 24.0, true);

		if (timeZone == 0)
			// до след. полночи (без включения самой полуночи)
			Model.set_t1(
				Model.get_t0() + 1 - interval / TYPE(MININDAY), true);
		else
			// иначе на 2 суток вперёд, чтобы покрыть часовые пояса
			Model.set_t1(
				Model.get_t0() + 2, true);

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
			установлено на 1 января 2017 года. По этой причине мы только задаём
			интервал выдачи - некое кратное количество минут, а всё остальное 
			оставляем по стандарту */
		Model.setInterval(SECINMIN * interval);

		Integrator.Run(Model);

		/*
			На выход отдаём положения Земли на весь год с интервалом в 'interval' 
			минут
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
	Симуляция движения тени гномона заданной высоты в заданной позиции
	на данную дату с заданным интервалом

	Результат работы функции - список положений тени в МГП (в топоцентрической СК)
*/
CMatrix CGnomon::SimulateShadow(const TYPE JD, const bool days)
{
	// по новой инициализируем текущую позицию (будем вращать через getPosition)
	curPosition = position;

	TYPE
		curTime = 0,
		//curTime = timeZone * 60 * SECINMIN,
		//curTime = getMidnight(JD),	// полночь текущего дня
		delta = interval * SECINMIN;	// смещение при вычислении curTime
		//delta = interval / TYPE(MININDAY);

	CVector days_of_year(DAYS_IN_CURRENT_YEAR);	// для подсчёта светлого времени
	UINT day_number(0);

/* 
	Вектор тени может быть определен как сумма векторов: 
*/
	int midNight_onPlace = (!timeZone) ? MININDAY / interval - timeZone * 60 : 0;

	for (int i = midNight_onPlace; i < midNight_onPlace + MININDAY / interval; i++)
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

		//CVector scalar(1);
		//scalar[0] = scalarProd;

		if (days)	// вычисляем на конкретную дату положения гномона
		{
			//addResult(scalar);

			if (scalarProd > 0)	// мы в тени, исследуем след. позиции
			{
				continue;
			}

			// наконец мы не в тени, продолжаем вычислять вектор тени в Инерц. СК
			rayVector = rayNormalized * (-height / scalarProd);

			addResult(Transform::Fix2Topo(rayVector + gnomonVector, curPosition));

		}
		else  // иначе считаем количество светлых минут в каждом дней
		{	
			if (scalarProd < 0)
				// увеличиваем счётчик светлого времени на смещение delta
				days_of_year[day_number] += delta;	 

			// если количество итераций дошло до кратного полуночи числа, увеличиваем номер дня
			if (i % (MININDAY / interval) == 0 && i != 0)
				day_number++;
		}
	}

	/* 
		если расчёт вели на год, то добавляем единственный вектор с количеством 
		светлого времени по дням */
	if (!days)
		addResult(days_of_year);

	//CMatrix Res(MININDAY * interval, 1);
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
	interval = 1;
	lastActual_JD = 0;

	position.setSize(3);
	position[1] = fi;
	position[2] = lambda;

	this->timeZone = timeZone;

	this->height = height;

	Result_size = 0;
	starTimeAtStart = 0;
}

void CGnomon::setParam(const TYPE fi, const TYPE lambda, const SINT timeZone,
					   const TYPE height)
{
	interval = 1;

	position.setSize(3);
	position[1] = fi;
	position[2] = lambda;

	this->timeZone = timeZone;

	this->height = height;

	starTimeAtStart = 0;
}

CMatrix CGnomon::GetShadowForDate(const TYPE JD, const UINT newInterval)
{
	interval = newInterval;

	/* 
		Рассчёт звёздного времени на начало моделирования. Прибавляем lambda 
		(долготу места), вычитаем часовой пояс */
	starTimeAtStart =
		StarTime(getMidnight(JD))
		+ position[2]
		- Earth::CEarth::angularVeloc * timeZone * 3600;

	// Расчитываем положение Земли на текущий день
	getEarthPosition(JD);

	CMatrix Shadow(SimulateShadow(JD));	// собрали информацию о движении тени
	clearResult();	// очистили лист с результатами

	return Shadow * 1000;
}

CVector CGnomon::GetLightTimeForYear(const UINT newInterval)
{
	interval = newInterval;

	/*
		Рассчёт звёздного времени на начало моделирования. Прибавляем lambda
		(долготу места), вычитаем часовой пояс */
	starTimeAtStart =
		StarTime(getMidnight(START_OF_THIS_YEAR))
		+ position[2],
		- Earth::CEarth::angularVeloc * timeZone * 3600;

	// Расчитываем положение Земли на год
	getEarthPosition(0, false);

	/*
		Рассчитываем светлое время по дням, записываем в вектор.

		0-ой индекс - из-за особенностей реализации результатом
		SimulateShadow является матрица. Наш результат - единственная строчка
		полученной матрицы
	*/
	CVector LightTime(SimulateShadow(START_OF_THIS_YEAR, false)[0]);
	clearResult();

	return LightTime;
}
