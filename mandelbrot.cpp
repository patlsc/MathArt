#include "SDL.h"
#include "constants.h"
#include "coords.h"

#include <complex>
using namespace std;

//it is parametrized by c to get f_c
//we start with f_c(0) then f_c^2(0) etc.
complex<double> IterationFunction(complex<double> c, complex<double> z) {
	return z * sin(z) + c;
}

void DrawMandelbrotPixel(SDL_Renderer* renderer, int xPix, int yPix) {
	complex<double> c = complex<double>(XPixelToCord(xPix), YPixelToCord(yPix));
	complex<double> val = 0;
	int triesTillMax = MAX_MAGNITUDE;
	for (int i = 0; i < NUM_ITERATIONS; i++) {
		val = IterationFunction(c, val);
		if (norm(val) >= MAX_MAGNITUDE) {
			triesTillMax = i;
			break;
		}
	}

	if (triesTillMax <= 10) {
		//grows fast, not in mandelbrot
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	}
	else if (triesTillMax <= 30) {
		SDL_SetRenderDrawColor(renderer, 125, 125, 0, 255);
	}
	else if (triesTillMax <= 50) {
		SDL_SetRenderDrawColor(renderer, 125, 255, 0, 255);
	}
	else if (triesTillMax <= 70) {
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	}
	else {
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	}
	SDL_RenderDrawPoint(renderer, xPix, yPix);
}

void DrawMandelbrot(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 100);
	for (int w = 0; w < WINDOW_W; w++) {
		for (int h = 0; h < WINDOW_H; h++) {
			DrawMandelbrotPixel(renderer, w, h);
		}
	}
}