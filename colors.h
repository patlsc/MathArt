#pragma once
void ObtainQuantiles(double samples[], int sample_length, double quantileArray[], int numQuantiles);
Uint32 AssignColorToObservation(double observation, double quantileArray[], int numQuantiles, float colorArray[][3], int numColors);