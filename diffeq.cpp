#include "constants.h"
#include "coords.h"
#include "pixels.h"
#include "colors.h"
#include <cstdlib>
#include <iostream>
#include <chrono>
using namespace std;

float RandRange(float fMin, float fMax) {
    return fMin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (fMax - fMin)));
}

float XDerivative(float xPos, float yPos) {
    return yPos;
}

float YDerivative(float xPos, float yPos) {
    return -xPos + 0.3 * (float)pow(yPos,2);
}

float GetGradientNorm(float xPos, float yPos) {
    float xd = XDerivative(xPos, yPos);
    float yd = YDerivative(xPos, yPos);
    return xd * xd + yd * yd;
}

//CONVERT ALL POSITIONS TO FLOATS
void PixelsAddDiffEqLine(float startXPos, float startYPos, float(*quantileArray)[NUM_QUANTILES]) {
    float xPos = startXPos;
    float yPos = startYPos;
    for (int i = 0; i < NUM_STEPS; i++) {
        float xd = XDerivative(xPos, yPos);
        float yd = YDerivative(xPos, yPos);
        float nextXPos = xPos + xd*DELTA;
        float nextYPos = yPos + yd*DELTA;
        //ending it if it becomes too slow
        float norm = xd * xd + yd * yd;
        if (norm < MINIMUM_SPEED) {
            //cout << "ending due to slowness";
            break;
        }
        //ending it if it strays from the screen
        if ((xPos >= MAX_X && xd > 0) ||
            (yPos >= MAX_Y && yd > 0) ||
            (xPos <= MIN_X && xd < 0) ||
            (yPos <= MIN_Y && yd < 0)
            ) {
            //cout << "ending due to straying from screen";
            break;
        }
        //y pos reaches almost 1 in the last part
        Uint32 col = AssignColorToObservation(norm,*quantileArray);
        /*cout << "making line segment from " << xPos << "," << yPos << " to " << nextXPos << "," << nextYPos << "\n";
        cout << "\tassociated with pixel indices " << XCordToPixelFloatClamped(xPos) << "," << YCordToPixelFloatClamped(yPos) << " to " << XCordToPixelFloatClamped(nextXPos) << "," << YCordToPixelFloatClamped(nextYPos) << "\n";
        cout << "\twith norm " << norm << "\n";
        cout << "\tand col " << std::hex << col << "\n";*/
        
        //TODO: this kind of clipping doesnt work. instead of clamping all
        //coordinates, it should reduce the length of the line so it just hits the end
        
        //PixelsAddUnaliasedLine(XCordToPixelClamped(xPos), YCordToPixelClamped(yPos), XCordToPixelClamped(nextXPos), YCordToPixelClamped(nextYPos), col);
        //PixelsAddAliasedLine(XCordToPixelFloatClamped(xPos), YCordToPixelFloatClamped(yPos), XCordToPixelFloatClamped(nextXPos), YCordToPixelFloatClamped(nextYPos), col);

        xPos = nextXPos;
        yPos = nextYPos;
    }
}

void PixelsAddManyDiffEqLines() {
    float samples[NUM_SAMPLES_TAKEN];
    for (int i = 0; i < NUM_SAMPLES_TAKEN; i++) {
        float xPos = RandRange(MIN_X, MAX_X);
        float yPos = RandRange(MIN_Y, MAX_Y);
        samples[i] = GetGradientNorm(xPos,yPos);
    }
    float quantileArray[NUM_QUANTILES];
    ObtainQuantiles(samples, NUM_SAMPLES_TAKEN, &quantileArray);
    

    auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < NUM_LINES; i++) {

        float xPos = RandRange(MIN_X, MAX_X);
        float yPos = RandRange(MIN_Y, MAX_Y);

        //todo
        PixelsAddDiffEqLine(xPos, yPos, &quantileArray);
    }
    auto end = std::chrono::steady_clock::now();
    float s = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0f;
    std::cout << "Finished Rendering Diffeq Lines in " << s << " seconds\n";
}