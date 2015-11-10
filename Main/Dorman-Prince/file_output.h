#include <windows.h>
#include <ShellAPI.h>

#include "Matrix_classes.h"
#include "Integrator.h"

#include <iostream>

#define DELAY 1000

using namespace std;

void Dorman_to_file(const TMatrix &Result, const TDormanPrince &Integrator);