#pragma once
typedef float twodfloatmagnitude(int, int);
void RenderMagnitudeSquare(int minX, int maxX, int minY, int maxY, float(*magnitudeArray), twodfloatmagnitude f);
void RenderMagnitudesMultithreaded(twodfloatmagnitude f);