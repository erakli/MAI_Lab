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
	class CGravitation_Field
	{
	public:
		virtual CVector getRight(const CVector &X, TYPE t) const;
	};

	/* Нормальное поле в системе точечных масс */
	class CNormal_field : public CGravitation_Field
	{
	private:
		MassPoints massPoints;

	public:
		CNormal_field();
		CVector getRight(const CVector &X, TYPE t) const override;
	};
}