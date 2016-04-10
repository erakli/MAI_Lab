#pragma once

namespace Earth
{
	/* Структура для хранения точеченых масс */
	struct Mass_Point
	{
		CVector position;
		TYPE value;
	};

	typedef std::vector<Mass_Point> MassPoints;


/* * * * * * * Модели гравитационного поля Земли * * * * * * */

/* 
	Центральное поле
*/
	class CGravitation_field
	{
	public:
		virtual ~CGravitation_field();

		virtual CVector getRight(const CVector &X) const;
	};


/* 
	Нормальное поле в системе точечных масс
*/
	class CNormal_field : public CGravitation_field
	{
	private:
		MassPoints massPoints;

	public:
		CNormal_field();
		CVector getRight(const CVector &X) const override;
	};


/* 
	Нормальное поле в сферических функциях
*/
	class CNormal_spheric : public CGravitation_field
	{
	protected:
		// Вычисление нормированных функций Лежандра и их производных по широте
		void PrepareP(
			CMatrix &P, CMatrix &_P, const TYPE fi, const int _degree) const;

		TYPE P(const int n, const int m, const TYPE fi) const;
		TYPE _P(const int n, const int m, const TYPE fi) const;

		/* 
			Матрица перехода от частных производных по сферическим координатам к
			частным производным по геоцентрическим прямоугольным */
		CMatrix ProjectOnDecart(
			const CVector &coord, const CVector &spheric) const;

	public:
		CVector getRight(const CVector &X) const override;
	};


/*
	Аномальное поле в сферических координатах
*/
	class CAnomalous_spheric : public CNormal_field
	{
	private:
		/* 
			Нормированные коэффициенты разложения гравитационного потенциала Земли
			в ряд по сферическим функциям */
		CMatrix C, S;

		/*
			Вычисление аномалий гравитационного ускорения в сферических 
			координатах */
		void EvalAll(
			CVector &delta_g_spher, const CVector &spheric, 
			const CMatrix &P, const CMatrix &_P);
	public:
		CAnomalous_spheric();

		CVector getRight(const CVector &X) const override;
	};
}