#include "pixels.h"
#include <cmath>
#include <algorithm>
using namespace std;

//get quantiles from a large number of values
void ObtainQuantiles(double samples[], int sample_length, double quantileArray[], int numQuantiles) {
	sort(samples,samples+sample_length);

	for (int i = 0; i < numQuantiles; i++) {
		quantileArray[i] = samples[(int)floor(sample_length * i / numQuantiles) - 1];
	}
	quantileArray[0] = 0;
}

//sets output array to RGB of resulting color
//given an observation, the quantiles for it, and an array of colors to shift between
Uint32 AssignColorToObservation(double observation, double quantileArray[], int numQuantiles, float colorArray[][3], int numColors) {
	double p = 0;
	for (int i = 0; i < numQuantiles-1; i++) {
		double start = quantileArray[i];
		double end = quantileArray[i + 1];
		if (start <= observation && observation <= end) {
			double amount_between = (observation - start) / (end - start);
			p = (double)i + amount_between;
		}
	}
	double k = (double)numQuantiles / (double)numColors;

	auto c1 = colorArray[(int)floor(p / k)];
	auto c2 = colorArray[(int)ceil(p / k)];
	double a = 1 - fmod(p,k) / k;

	return MakePixelFromRGBFloats((float)(a * c1[0] + (1.0f - a) * c2[0]), (float)(a * c1[1] + (1.0f - a) * c2[1]), (float)(a * c1[2] + (1.0f - a) * c2[2]));
}