#include "pendulum.h"

#define PI	3.14159265358979323846

/* В разработке. Нужно прокомментировать */

TMathPendulum::TMathPendulum(TYPE l, TYPE ang, TYPE m){
	t0 = 0;
	StartValues.setSize(2);
	s_size = StartValues.getSize();

	length = l;
	angle = ang;
	mass = m;

	Omega0 = sqrt(g / length);

	Period = 2 * PI * sqrt(length / g);

	StartValues[0] = angle * PI / 180;	// fi in rad			// fi
	StartValues[1] = Omega0;	// fi'
}

TVector TMathPendulum::getRight(TVector &X, TYPE t) const{
	TVector Y(s_size);

	Y[0] = X[1];					// p = fi'
	Y[1] = -pow(X[1], 2) * sin(X[0]);

	return Y;
}

