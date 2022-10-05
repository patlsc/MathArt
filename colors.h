#pragma once
#include "pixels.h"
void ObtainQuantiles(float samples[], int sample_length, float(*quantileArray)[NUM_QUANTILES]);
Uint32 AssignColorToObservation(float observation, float quantileArray[]);
int GenerateRandomInt(int min, int max);
void SetPixelsFromMagnitudeArray(float (*magnitudeArray));
void SetPixelColorationTest();