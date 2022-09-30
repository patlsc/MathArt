#pragma once
#include "SDL.h"

double RandRange(double fMin, double fMax);
double XDerivative(double xPos, double yPos);
double YDerivative(double xPos, double yPos);
void DrawDiffEqLine(SDL_Renderer* renderer, double startXPos, double startYPos);
void DrawManyDiffEqLines(SDL_Renderer* renderer);