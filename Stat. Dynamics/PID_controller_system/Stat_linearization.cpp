#include <cmath>
#include "Stat_linearization.h"

#define POLYNOMIAL_DEGREE	5

static cTYPE a_vec[POLYNOMIAL_DEGREE] =
{
	0.254829592,
	-0.284496736,
	1.421413741,
	-1.453152027,
	1.061405429
};

static cTYPE b = 0.3275911;

Linearization::Linearization() : Mx(0), disp(1)
{
}

Linearization::~Linearization()
{
}

TYPE Linearization::erf(cTYPE x) const
{
	TYPE
		t = 1 / (1 + b * abs(x)),
		sign = copysign(x, x),
		polynomial_sum(0);
	
	for (auto i = 0; i < POLYNOMIAL_DEGREE; i++)
		polynomial_sum += a_vec[i] * pow(t, i + 1);

	return sign * (1 - polynomial_sum * exp(-pow(x, 2)));
}

TYPE Linearization::norm(cTYPE x) const
{
	if (INFINITY == abs(x))
		return copysign(0.5, x);	// Ф(+-INF) = +-1/2

	return 0.5 * erf(x / sqrt(2));
}

/* Стандартное нормальное гауссовское распределение */
TYPE Linearization::f_gauss(cTYPE x) const
{
	return f_gauss(x, 0, 1);
}

/* Нормальное гауссовское распределение */
TYPE Linearization::f_gauss(cTYPE x, cTYPE Mx, cTYPE disp) const
{
	TYPE
		const_part = 1 / sqrt(2 * PI * disp),
		e = exp(-pow(x - Mx, 2) / (2 * disp));

	return const_part * e;
}

TYPE Linearization::J0_integral(
	cTYPE Mx, cTYPE disp, cTYPE l_border, cTYPE u_border) const
{
	TYPE sigma = sqrt(disp);

	return norm((u_border - Mx) / sigma) - norm((l_border - Mx) / sigma);
}

TYPE Linearization::J1_integral(
	cTYPE Mx, cTYPE disp, cTYPE l_border, cTYPE u_border) const
{
	TYPE J0 = J0_integral(Mx, disp, l_border, u_border);

	// здесь стандартное нормальное распределение или обычное?
	return 
		Mx * J0 
		- disp * (f_gauss(u_border, Mx, disp) - f_gauss(l_border, Mx, disp));
}

LinearCoeff Linearization::getCoefficients(cTYPE Mx, cTYPE disp)
{
	this->Mx = Mx;
	this->disp = disp;

	TYPE
		fi_0 = get_fi_0(),
		k1_first = get_k1_first(fi_0),
		k1_second = get_k1_second(fi_0),
		k0 = get_k0(fi_0);

	return { fi_0, k1_first, k1_second, k0 };
}



SaturationLinearize::SaturationLinearize(): s_index(0)
{
}

TYPE SaturationLinearize::get_fi_0()
{
}

TYPE SaturationLinearize::get_k1_first(cTYPE fi_0)
{
}

TYPE SaturationLinearize::get_k1_second(cTYPE fi_0)
{
}

TYPE SaturationLinearize::get_k0(cTYPE fi_0)
{
}

LinearCoeff SaturationLinearize::getCoefficients(cTYPE s, cTYPE Mx, cTYPE disp)
{
}
