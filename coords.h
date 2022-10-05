#pragma once
#include <cstdint>
int32_t XCordToPixel(double xPos);
int32_t YCordToPixel(double xPos);
double XCordToPixelDouble(double xPos);
double YCordToPixelDouble(double yPos);
float XCordToPixelFloat(float xPos);
float YCordToPixelFloat(float yPos);
float XPixelToCord(int32_t xPixel);
float YPixelToCord(int32_t xPixel);
double ClampD(double a, double minimum, double maximum);
float ClampF(float a, float minimum, float maximum);
int ClampI(int a, int minimum, int maximum);
int32_t XCordToPixelClamped(double xPos);
int32_t YCordToPixelClamped(double yPos);
float XCordToPixelFloatClamped(float xPos);
float YCordToPixelFloatClamped(float yPos);