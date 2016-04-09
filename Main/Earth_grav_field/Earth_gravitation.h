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


/* Модели гравитационного поля Земли */

/* Центральное поле */
	class CGravitation_field
	{
	public:
		virtual ~CGravitation_field();

		virtual CVector getRight(const CVector &X) const;
	};

/* Нормальное поле в системе точечных масс */
	class CNormal_field : public CGravitation_field
	{
	private:
		MassPoints massPoints;

	public:
		CNormal_field();
		CVector getRight(const CVector &X) const override;
	};

/* Нормальное поле в сферических функциях */
	class CNormal_spheric : public CGravitation_field
	{
	protected:
		// Вычисление нормированных функций Лежандра и их производных по широте
		void PrepareP(
			CMatrix &P, CMatrix &_P, const TYPE fi, const int _degree) const;

		CMatrix ProjectOnDecart(
			const CVector &coord, const CVector &spheric) const;
	public:
		CNormal_spheric();

		CVector getRight(const CVector &X) const override;
	};


}