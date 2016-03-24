#pragma once
#pragma warning( disable: 4996 )

#include "Matrix_classes.h"
#include "Integrator.h"

#define DELAY 2000

void Dorman_to_file(const CMatrix &Result, const CDormanPrince &Integrator, bool radians = true);
void to_file(const CMatrix &Result, bool radians = true);