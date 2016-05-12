#pragma once

#include "Types.h"

struct LinearCoeff
{
	TYPE
		fi_0,
		k1_first,
		k1_second;
};

class Linearization
{
public:
	Linearization();
	virtual ~Linearization();

protected:
	mutable TYPE Mx, disp;

#ifdef _DEBUG
public:
#else
protected:
#endif
	TYPE erf(cTYPE x) const;
	TYPE LaplaceFcn(cTYPE x) const;

	TYPE f_gauss(cTYPE x) const;
	TYPE f_gauss(cTYPE x, cTYPE Mx, cTYPE disp) const;

	TYPE J0_integral(cTYPE Mx, cTYPE disp, cTYPE l_border, cTYPE u_border) const;
	TYPE J1_integral(cTYPE Mx, cTYPE disp, cTYPE l_border, cTYPE u_border) const;
	TYPE J2_integral(cTYPE Mx, cTYPE disp, cTYPE l_border, cTYPE u_border) const;

	virtual TYPE get_fi_0() const = 0;
	virtual TYPE get_k1_first(cTYPE fi_0) const = 0;
	virtual TYPE get_k1_second(cTYPE fi_0) const = 0;

public:
	LinearCoeff getCoefficients(cTYPE Mx, cTYPE disp) const;
};


class SaturationLinearize: public Linearization
{
#define INTERVALS	3
public:
	SaturationLinearize();

protected:
	mutable TYPE s_index;
	mutable TYPE
		J0[INTERVALS],
		J1[INTERVALS],
		J2;

protected:
	TYPE get_fi_0() const override;
	TYPE get_k1_first(cTYPE fi_0) const override;
	TYPE get_k1_second(cTYPE fi_0) const override;

public:
	LinearCoeff getCoefficients(cTYPE s, cTYPE Mx, cTYPE disp) const;
};
