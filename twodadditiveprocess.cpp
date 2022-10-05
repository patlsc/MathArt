//for multithreaded rendering of two dimensional functions which additively edit the 2d plane
//from a starting point
//for instance: differential equation solution curves
//the difference between this and twodmagnitudes is that now in addition to
//having an array of total magnitudes, we have a weightArray
//in differential equations, magnitudeArray determines the color while weightArray determines the opacity
//basically, it is a two dimensional version of the magnitudeArray render process
#include "constants.h"
#include <cmath>

typedef void twodadditive(float (*), float (*));

const int BROWNIAN_LENGTH = 2000;
void BrownianProcess(int xPix, int yPix, float magnitude, float(*magnitudeArray), float(*weightArray)) {
	int processLength = BROWNIAN_LENGTH;
	int currentX = xPix;
	int currentY = yPix;
	for (int i = 0; i < processLength; i++) {
		magnitudeArray[currentY * WINDOW_W + currentX] = magnitude;
		weightArray[currentY * WINDOW_W + currentX] += 1.0f;
		float r = (float)rand() / (float)RAND_MAX;
		if (r <= 0.25f) {
			currentX++;
		}
		else if (r <= 0.5f) {
			currentX--;
		}
		else if (r <= 0.75f) {
			currentY++;
		}
		else {
			currentY--;
		}
		if (currentX < 0) {
			currentX = 0;
		}
		else if (currentX > WINDOW_W - 1) {
			currentX = WINDOW_W - 1;
		}
		if (currentY < 0) {
			currentY = 0;
		}
		else if (currentY > WINDOW_H - 1) {
			currentY = WINDOW_H - 1;
		}
	}
}