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
		polynomial_sum(0);
	
	for (auto i = 0; i < POLYNOMIAL_DEGREE; i++)
		polynomial_sum += a_vec[i] * pow(t, i + 1);

	return 1 - polynomial_sum * exp(-pow(x, 2));
}

TYPE Linearization::LaplaceFcn(cTYPE x) const
{
	TYPE sign = copysign(0.5, x);

	if (INFINITY == abs(x))
		return sign;		// Ф(+-INF) = +- 1

	return sign * erf(abs(x) / sqrt(2));  // Ф(t) = sqn(t) Ф(|t|)
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

	return LaplaceFcn((u_border - Mx) / sigma) - LaplaceFcn((l_border - Mx) / sigma);
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

TYPE Linearization::J2_integral(cTYPE Mx, cTYPE disp, cTYPE l_border, cTYPE u_border) const
{
	TYPE
		J0 = J0_integral(Mx, disp, l_border, u_border),
		J1 = J1_integral(Mx, disp, l_border, u_border);

	return
		Mx * J1 
		+ disp 
		* (J0 
			- u_border * f_gauss(u_border, Mx, disp) 
			+ l_border * f_gauss(l_border, Mx, disp));
}

LinearCoeff Linearization::getCoefficients(cTYPE Mx, cTYPE disp)
{
	this->Mx = Mx;
	this->disp = disp;

	TYPE
		fi_0 = get_fi_0(),
		k1_first = get_k1_first(fi_0),
		k1_second = get_k1_second(fi_0);

	return { fi_0, k1_first, k1_second };
}


/* 
	SaturationLinearize
*/

SaturationLinearize::SaturationLinearize() : s_index(0), J2(0)
{
	for (auto i = 0; i < INTERVALS; i++)
	{
		J0[i] = 0;
		J1[i] = 0;
	}
}

TYPE SaturationLinearize::get_fi_0()
{
	return 
		-s_index * J0[0] 
		+ J1[1] 
		+ s_index * J0[2];
}

TYPE SaturationLinearize::get_k1_first(cTYPE fi_0)
{
	TYPE
		integral = 
			pow(s_index, 2) * J0[0]
			+ J2
			+ pow(s_index, 2) * J0[2];

	return
		sqrt((integral - pow(fi_0, 2)) / disp);
}

TYPE SaturationLinearize::get_k1_second(cTYPE fi_0)
{
	TYPE
		integral =
		-s_index * J1[0]
		+ J2
		+ s_index * J1[2];

	return
		(integral - Mx * fi_0) / disp;
}

LinearCoeff SaturationLinearize::getCoefficients(cTYPE s, cTYPE Mx, cTYPE disp)
{
	J0[0] = J0_integral(Mx, disp, -INFINITY, -s);
	J0[1] = J0_integral(Mx, disp, -s, s);
	J0[2] = J0_integral(Mx, disp, s, INFINITY);

	J1[0] = J1_integral(Mx, disp, -INFINITY, -s);
	J1[1] = J1_integral(Mx, disp, -s, s);
	J1[2] = J1_integral(Mx, disp, s, INFINITY);

	J2 = J2_integral(Mx, disp, -s, s);

	s_index = s;

	return Linearization::getCoefficients(Mx, disp);
}
