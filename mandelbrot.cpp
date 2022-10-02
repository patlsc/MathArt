#include "SDL.h"
#include "constants.h"
#include "pixels.h"
#include "colors.h"
#include "coords.h"

#include <complex>
using namespace std;

//it is parametrized by c to get f_c
//we start with f_c(0) then f_c^2(0) etc.
complex<double> IterationFunction(complex<double> c, complex<double> z) {
	return z * sin(z) + c;
}

double GetMandelbrotMagnitude(int xPix, int yPix) {
	complex<double> c = complex<double>(XPixelToCord(xPix), YPixelToCord(yPix));
	complex<double> val = 0;
	int triesTillMax = 0;
	for (int i = 0; i < NUM_ITERATIONS; i++) {
		val = IterationFunction(c, val);
		if (norm(val) >= MAX_MAGNITUDE) {
			triesTillMax = i;
			break;
		}
	}
	return (double)triesTillMax;
}

void SetMandelbrotPixels() {
	double *magnitudeArray = new double[WINDOW_W * WINDOW_H];
	for (int xPix = 0; xPix < WINDOW_W; xPix++) {
		for (int yPix = 0; yPix < WINDOW_H; yPix++) {
			magnitudeArray[WINDOW_W * yPix + xPix] = GetMandelbrotMagnitude(xPix, yPix);
		}
	}
	
	SetPixelsFromMagnitudeArray(magnitudeArray);
}