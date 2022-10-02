#include "constants.h"
#include "pixels.h"
#include <cmath>
#include <algorithm>
using namespace std;

//get quantiles from a large number of values
//modifies quantileArray
void ObtainQuantiles(double samples[], int sample_length, double (*quantileArray)[NUM_QUANTILES], int numQuantiles) {
	sort(samples,samples+sample_length);

	for (int i = 0; i < numQuantiles; i++) {
		(*quantileArray)[i] = samples[(int)floor(sample_length * i / numQuantiles) - 1];
	}
	(*quantileArray)[0] = 0;
}

//sets output array to RGB of resulting color
//given an observation, the quantiles for it, and an array of colors to shift between
Uint32 AssignColorToObservation(double observation, double quantileArray[], int numQuantiles) {
	double p = 0;
	for (int i = 0; i < numQuantiles-1; i++) {
		double start = quantileArray[i];
		double end = quantileArray[i + 1];
		if (start <= observation && observation <= end) {
			double amount_between = (observation - start) / (end - start);
			p = (double)i + amount_between;
		}
	}
	double k = (double)numQuantiles / (double)NUM_COLORS;

	auto c1 = MY_COLORS[(int)floor(p / k)];
	auto c2 = MY_COLORS[(int)ceil(p / k)];
	double a = 1 - fmod(p,k) / k;

	return MakePixelFromRGBFloats((float)(a * c1[0] + (1.0f - a) * c2[0]), (float)(a * c1[1] + (1.0f - a) * c2[1]), (float)(a * c1[2] + (1.0f - a) * c2[2]));
}

//inclusive of bounds
//todo this is biased
int GenerateRandomInt(int min, int max) {
	return (rand() % (max - min)) + min;
}

//given an array of magnitudes with same width and height as pixels, assign the pixels colors based on their magnitude and the color scheme
void SetPixelsFromMagnitudeArray(double magnitudeArray[]) {
	double samples[NUM_SAMPLES_TAKEN];
	for (int i = 0; i < NUM_SAMPLES_TAKEN; i++) {
		int xPix = GenerateRandomInt(0, WINDOW_W);
		int yPix = GenerateRandomInt(0, WINDOW_H);
		samples[i] = magnitudeArray[yPix * WINDOW_W + xPix];
	}

	double quantileArray[NUM_QUANTILES];
	ObtainQuantiles(samples, NUM_SAMPLES_TAKEN, &quantileArray, NUM_QUANTILES);

	for (int xPix = 0; xPix < WINDOW_W; xPix++) {
		for (int yPix = 0; yPix < WINDOW_H; yPix++) {
			SetPixelColor(xPix, yPix, AssignColorToObservation(magnitudeArray[yPix * WINDOW_W + xPix], quantileArray, NUM_QUANTILES));
		}
	}
}