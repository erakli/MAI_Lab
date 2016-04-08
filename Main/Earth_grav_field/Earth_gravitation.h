#pragma once

namespace Earth
{
	/* ��������� ��� �������� ��������� ���� */
	struct Mass_Point
	{
		CVector position;
		TYPE value;
	};

	typedef std::vector<Mass_Point> MassPoints;


/* ������ ��������������� ���� ����� */

	/* ����������� ���� */
	class CGravitation_Field
	{
	public:
		virtual CVector getRight(const CVector &X, TYPE t) const;
	};

	/* ���������� ���� � ������� �������� ���� */
	class CNormal_field : public CGravitation_Field
	{
	private:
		MassPoints massPoints;

	public:
		CNormal_field();
		CVector getRight(const CVector &X, TYPE t) const override;
	};
}