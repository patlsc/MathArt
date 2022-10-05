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
	//return z * cos(z) + c;
	return z*z + c;
}

float GetMandelbrotMagnitude(int xPix, int yPix) {
	complex<double> c = complex<double>(XPixelToCord(xPix), YPixelToCord(yPix));
	complex<double> val = 0;
	int triesTillMax = NUM_ITERATIONS;
	for (int i = 0; i < NUM_ITERATIONS; i++) {
		val = IterationFunction(c, val);
		if (norm(val) >= MAX_MAGNITUDE) {
			triesTillMax = i;
			break;
		}
	}
	return (float)triesTillMax;
}