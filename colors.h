#pragma once
#include "pixels.h"
void ObtainQuantiles(double samples[], int sample_length, double(*quantileArray)[NUM_QUANTILES]);
Uint32 AssignColorToObservation(double observation, double quantileArray[]);
int GenerateRandomInt(int min, int max);
void SetPixelsFromMagnitudeArray(double magnitudeArray[]);
void SetPixelColorationTest();