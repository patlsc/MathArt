#pragma once
//dimensions in the display
const int WINDOW_H = 1000;
const int WINDOW_W = 1500;
//dimensions in the math world
const double MIN_X = 1.2;
const double MAX_X = 1.8;
const double MIN_Y = -0.25;
const double MAX_Y = 0.25;

//diffeq
//higher = better performance, more jagged but longer lines
const double DELTA = 0.005;
//higher = worse performance, longer lines
const int NUM_STEPS = 500;

const int NUM_LINES = 900;

const char OUTPUT_PATH[] = "out3.bmp";

//mandelbrot
const int NUM_ITERATIONS = 200;
const double MAX_MAGNITUDE = 1000000000;

//coloring
//5 colors RGB
const int NUM_COLORS = 5;
/*
const float MY_COLORS[NUM_COLORS][3] = {
	{1.0f,0.0f,0.0f}, //red
	{1.0f,1.0f,0.0f}, //orange
	{0.0f,1.0f,0.0f}, //green
	{0.0f,1.0f,1.0f}, //turquoise
	{0.0f,0.0f,1.0f}  //blue
};
*/

const int NUM_SAMPLES_TAKEN = 5000;
const int NUM_QUANTILES = 20;

//3d rendering
const double THREEDCAM_X = 0;
const double THREEDCAM_Y = 0;
const double THREEDCAM_Z = 0;