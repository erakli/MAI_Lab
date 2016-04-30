#pragma once

#include "Types.h"

struct LinearCoeff
{
	TYPE
		fi_0,
		k1_first,
		k1_second,
		k0;
};

class Linearization
{
public:
	Linearization();
	virtual ~Linearization();

protected:
	TYPE Mx, disp;

protected:
	TYPE erf(cTYPE x) const;
	TYPE norm(cTYPE x) const;

protected:
	TYPE f_gauss(cTYPE x) const;
	TYPE f_gauss(cTYPE x, cTYPE Mx, cTYPE disp) const;

	TYPE J0_integral(cTYPE Mx, cTYPE disp, cTYPE l_border, cTYPE u_border) const;
	TYPE J1_integral(cTYPE Mx, cTYPE disp, cTYPE l_border, cTYPE u_border) const;

protected:
	virtual TYPE get_fi_0() = 0;
	virtual TYPE get_k1_first(cTYPE fi_0) = 0;
	virtual TYPE get_k1_second(cTYPE fi_0) = 0;
	virtual TYPE get_k0(cTYPE fi_0) = 0;

public:
	LinearCoeff getCoefficients(cTYPE Mx, cTYPE disp);
};


/* TO-DO: реализовать методы этого класса */

class SaturationLinearize: public Linearization
{
public:
	SaturationLinearize();

protected:
	TYPE s_index;

protected:
	TYPE get_fi_0() override;
	TYPE get_k1_first(cTYPE fi_0) override;
	TYPE get_k1_second(cTYPE fi_0) override;
	TYPE get_k0(cTYPE fi_0) override;

public:
	LinearCoeff getCoefficients(cTYPE s, cTYPE Mx, cTYPE disp);
};
