#include "constants.h"
#include "coords.h"
#include "pixels.h"
#include "colors.h"
#include <cstdlib>
#include <iostream>
#include <chrono>
using namespace std;

double RandRange(double fMin, double fMax) {
    return fMin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (fMax - fMin)));
}

double XDerivative(double xPos, double yPos) {
    return yPos;
}

double YDerivative(double xPos, double yPos) {
    return -xPos + 0.3 * pow(yPos,2);
}

float GetGradientNorm(double xPos, double yPos) {
    float xd = XDerivative(xPos, yPos);
    float yd = YDerivative(xPos, yPos);
    return xd * xd + yd * yd;
}

void PixelsAddDiffEqLine(double startXPos, double startYPos, float(*quantileArray)[NUM_QUANTILES]) {
    double xPos = startXPos;
    double yPos = startYPos;
    for (int i = 0; i < NUM_STEPS; i++) {
        double changeX = XDerivative(xPos, yPos) * DELTA;
        double changeY = YDerivative(xPos, yPos) * DELTA;
        double nextXPos = xPos + changeX;
        double nextYPos = yPos + changeY;
        //ending it if it becomes too slow
        if (abs(changeX)+abs(changeY) < MINIMUM_SPEED) {
            //cout << "ending due to slowness";
            break;
        }
        //ending it if it strays from the screen
        if ((nextXPos > MAX_X && changeX > 0) ||
            (nextYPos > MAX_Y && changeY > 0) ||
            (nextXPos < MIN_X && changeX < 0) ||
            (nextYPos < MIN_Y && changeY < 0)
            ) {
            break;
        }
        //y pos reaches almost 1 in the last part
        //cout << "making line segment from " << xPos << "," << yPos << " to " << nextXPos << "," << nextYPos << "\n";
        //cout << "associated with pixel indices " << XCordToPixelClamped(xPos) << "," << YCordToPixelClamped(yPos) << " to " << XCordToPixelClamped(nextXPos) << "," << YCordToPixelClamped(nextYPos) << "\n";
        Uint32 col = AssignColorToObservation(GetGradientNorm((xPos + nextXPos)/2,(yPos+nextYPos)/2),*quantileArray);
        PixelsAddUnaliasedLine(XCordToPixelClamped(xPos), YCordToPixelClamped(yPos), XCordToPixelClamped(nextXPos), YCordToPixelClamped(nextYPos), col);
        //PixelsAddAliasedLine(xPos, yPos, nextXPos, nextYPos, col);

        xPos = nextXPos;
        yPos = nextYPos;
    }
}

void PixelsAddManyDiffEqLines() {
    float samples[NUM_SAMPLES_TAKEN];
    for (int i = 0; i < NUM_SAMPLES_TAKEN; i++) {
        double xPos = RandRange(MIN_X, MAX_X);
        double yPos = RandRange(MIN_Y, MAX_Y);
        samples[i] = GetGradientNorm(xPos,yPos);
    }
    float quantileArray[NUM_QUANTILES];
    ObtainQuantiles(samples, NUM_SAMPLES_TAKEN, &quantileArray);
    

    auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < NUM_LINES; i++) {

        double xPos = RandRange(MIN_X, MAX_X);
        double yPos = RandRange(MIN_Y, MAX_Y);

        //todo
        PixelsAddDiffEqLine(xPos, yPos, &quantileArray);
    }
    auto end = std::chrono::steady_clock::now();
    float s = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0f;
    std::cout << "Finished Rendering Diffeq Lines in " << s << " seconds\n";
}