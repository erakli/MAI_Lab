#pragma once
#pragma warning( disable: 4996 )

#include "Matrix_classes.h"
#include "Integrator.h"

#define DELAY 1000

void Dorman_to_file(const CMatrix &Result, const CDormanPrince &Integrator, bool radians = true);
void to_file(const CMatrix &Result, bool radians = true);
void to_file(const CVector &Result, bool radians = true);

void Read_from_file(const char *FileName, CMatrix &target, const UINT PredictSize = 100);