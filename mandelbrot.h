#pragma once
#include "SDL.h"
#include <complex>
using namespace std;

complex<double> IterationFunction(complex<double> c, complex<double> z);
float GetMandelbrotMagnitude(int xPix, int yPix);
void SetMandelbrotPixels();