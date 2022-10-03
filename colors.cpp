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

	/*
	cout << "obtained quantile array \n[";
	for (int i = 0; i < numQuantiles; i++) {
		cout << (*quantileArray)[i] << ",";
	}
	cout << "max sampled value " << samples[sample_length - 1];
	cout << "min sampled value " << samples[0];
	*/
}

//sets output array to RGB of resulting color
//given an observation, the quantiles for it, and an array of colors to shift between
Uint32 AssignColorToObservation(double observation, double quantileArray[], int numQuantiles) {
	double p = 0;
	if (observation <= quantileArray[0]) {
		//lower than all observed values, give it first color
		return MakePixelFromRGBFloats(MY_COLORS[0][0], MY_COLORS[0][1], MY_COLORS[0][2]);
	}
	if (observation >= quantileArray[numQuantiles - 1]) {
		//bigger than all observed values
		return MakePixelFromRGBFloats(MY_COLORS[NUM_COLORS - 1][0], MY_COLORS[NUM_COLORS - 1][1], MY_COLORS[NUM_COLORS - 1][2]);
	}
	for (int i = 0; i < numQuantiles-1; i++) {
		double start = quantileArray[i];
		double end = quantileArray[i + 1];
		if (start <= observation && observation <= end) {
			double amount_between = (observation - start) / (end - start);
			p = (double)i + amount_between;
		}
	}
	double k = (double)numQuantiles / (double)NUM_COLORS;
	//how far it is through the color array
	double normalized_p = p / k;
	//the colors its between
	auto c1 = MY_COLORS[(int)floor(normalized_p)];
	auto c2 = MY_COLORS[(int)ceil(normalized_p)];
	//how between it is
	double a = ceil(normalized_p) - normalized_p;

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

//this should produce an increasing gradient from the top left to the bottom right of the screen, covering the entire color array
void SetPixelColorationTest() {
	double* magnitudeArray = new double[WINDOW_W * WINDOW_H];
	for (int xPix = 0; xPix < WINDOW_W; xPix++) {
		for (int yPix = 0; yPix < WINDOW_H; yPix++) {
			magnitudeArray[WINDOW_W * yPix + xPix] = (double)(xPix+yPix);
		}
	}

	SetPixelsFromMagnitudeArray(magnitudeArray);
}