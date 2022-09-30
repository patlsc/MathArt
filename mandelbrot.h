#pragma once
#include "SDL.h"
#include <complex>
using namespace std;

complex<double> IterationFunction(complex<double> c, complex<double> z);

void DrawMandelbrotPixel(SDL_Renderer* renderer, int xPix, int yPix);

void DrawMandelbrot(SDL_Renderer* renderer);