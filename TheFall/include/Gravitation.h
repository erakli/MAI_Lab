#pragma once

namespace Earth
{
/* * * * * * * Модели гравитационного поля Земли * * * * * * */

/* 
	Центральное поле
*/
	class GravitationField
	{
	public:
		virtual ~GravitationField();

		virtual CVector getRight(const CVector &X) const;
	};
}