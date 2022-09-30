#include "SDL.h"
#include "constants.h"
#include "coords.h"
#include <cstdlib>
using namespace std;

double RandRange(double fMin, double fMax) {
    double f = (double)rand() / fMax;
    return fMin + f * (fMax - fMin);
}

double XDerivative(double xPos, double yPos) {
    return yPos;
}

double YDerivative(double xPos, double yPos) {
    return -xPos + 0.3 * yPos;
}

void DrawDiffEqLine(SDL_Renderer* renderer, double startXPos, double startYPos) {
    double xPos = startXPos;
    double yPos = startYPos;
    for (int i = 0; i < NUM_STEPS; i++) {

        double nextXPos = xPos + XDerivative(xPos, yPos) * DELTA;
        double nextYPos = yPos + YDerivative(xPos, yPos) * DELTA;

        SDL_RenderDrawLine(renderer, XCordToPixel(xPos), YCordToPixel(yPos), XCordToPixel(nextXPos), YCordToPixel(nextYPos));
        xPos = nextXPos;
        yPos = nextYPos;
    }
}

void DrawManyDiffEqLines(SDL_Renderer* renderer) {
    for (int i = 0; i < NUM_LINES; i++) {

        double xPos = RandRange(MIN_X, MAX_X);
        double yPos = RandRange(MIN_Y, MAX_Y);
        DrawDiffEqLine(renderer, xPos, yPos);

    }
}