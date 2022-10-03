#pragma once
typedef double twoddoublemagnitude(int, int);
void RenderMagnitudeSquare(int minX, int maxX, int minY, int maxY, double(*magnitudeArray), twoddoublemagnitude f);
void RenderMagnitudesMultithreaded(twoddoublemagnitude f);