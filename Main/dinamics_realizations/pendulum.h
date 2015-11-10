#include "Model.h"

/* В разработке. Нужно прокомментировать */

class TPendulum : public TModel
{
protected:
	TYPE length, angle, mass;
	TYPE g;
public:
	TPendulum(){ g = 9.81; };
};

class TMathPendulum : public TPendulum
{
protected:
	TYPE Omega0;
public:
	TYPE Period;

	TMathPendulum(TYPE l, TYPE ang, TYPE m);
	TVector getRight(TVector &X, TYPE t) const;
};