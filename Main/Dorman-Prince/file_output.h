#pragma once
#pragma warning( disable: 4996 )
#include <windows.h>
#include <ShellAPI.h>

#include "Matrix_classes.h"
#include "Integrator.h"

#include <iostream>

#define DELAY 2000

using namespace std;

void Dorman_to_file(const TMatrix &Result, const TDormanPrince &Integrator, bool radians = true);