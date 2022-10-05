#include "constants.h"
#include "coords.h"
#include <cmath>

int32_t XCordToPixel(double xPos) {
    return (int32_t)((xPos - MIN_X) * WINDOW_W / (MAX_X - MIN_X));
}

int32_t YCordToPixel(double yPos) {
    return (int32_t)((yPos - MIN_Y) * WINDOW_H / (MAX_Y - MIN_Y));
}

//pixels in floating point coords
double XCordToPixelDouble(double xPos) {
    return ((xPos - MIN_X) * WINDOW_W / (MAX_X - MIN_X));
}

double YCordToPixelDouble(double yPos) {
    return ((yPos - MIN_Y) * WINDOW_H / (MAX_Y - MIN_Y));
}

float XCordToPixelFloat(float xPos) {
    return ((xPos - MIN_X) * WINDOW_W / (MAX_X - MIN_X));
}

float YCordToPixelFloat(float yPos) {
    return ((yPos - MIN_Y) * WINDOW_H / (MAX_Y - MIN_Y));
}

float XPixelToCord(int32_t xPixel) {
    return MIN_X + ((float)xPixel) * (MAX_X - MIN_X) / WINDOW_W;
}

float YPixelToCord(int32_t yPixel) {
    return MIN_Y + ((float)yPixel) * (MAX_Y - MIN_Y) / WINDOW_H;
}

//coordinate->pixel functions clamped to be between 0 and WINDOW_W-1 and 0 and WINDOW_H-1
double ClampD(double a, double minimum, double maximum) {
    return (a > minimum ? (a < maximum ? a : maximum) : minimum);
}

float ClampF(float a, float minimum, float maximum) {
    return (a > minimum ? (a < maximum ? a : maximum) : minimum);
}

int ClampI(int a, int minimum, int maximum) {
    return (a > minimum ? (a < maximum ? a : maximum) : minimum);
}

int32_t XCordToPixelClamped(double xPos) {
    return ClampI(XCordToPixel(xPos),0,WINDOW_W-1);
}

int32_t YCordToPixelClamped(double yPos) {
    return ClampI(YCordToPixel(yPos),0,WINDOW_H-1);
}

float XCordToPixelFloatClamped(float xPos) {
    return ClampF(XCordToPixelFloat(xPos), 0, WINDOW_W - 1);
}

float YCordToPixelFloatClamped(float yPos) {
    return ClampF(XCordToPixelFloat(yPos), 0, WINDOW_H - 1);
}