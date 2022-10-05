#pragma once
#include "SDL.h"

float RandRange(float fMin, float fMax);
float XDerivative(float xPos, float yPos);
float YDerivative(float xPos, float yPos);
float GetGradientNorm(float xPos, float yPos);
void PixelsAddDiffEqLine(float startXPos, float startYPos, float(*quantileArray)[NUM_QUANTILES]);
void PixelsAddManyDiffEqLines();