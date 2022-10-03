#pragma once
//dimensions in the display
const int WINDOW_H = 1440;
const int WINDOW_W = 2560;
const float ASPECT_RATIO = (float)WINDOW_W / (float)WINDOW_H;
//dimensions in the math world
const double MIN_X = 1.5;
const double MAX_X = 3;
const double MIN_Y = 0;
const double MAX_Y = 0.75;

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
const float MY_COLORS[NUM_COLORS][3] = {
	{0.8f,0.0f,0.0f}, //red
	{0.8f,0.8f,0.0f}, //orange
	{0.0f,0.8f,0.0f}, //green
	{0.0f,0.8f,0.8f}, //turquoise
	{0.0f,0.0f,0.8f}  //blue
};

/*
const int NUM_COLORS = 6;
const float MY_COLORS[NUM_COLORS][3] = {
	{0.45f,0.0f,0.0f},
	{0.58f,0.09f,0.09f},
	{0.67f,0.12f,0.42f},
	{0.36f,0.67f,0.81f},
	{0.69f,0.25f,0.72f},
	{0.39f,0.15f,0.75f},
};
*/
/*
const int NUM_COLORS = 5;
const float MY_COLORS[NUM_COLORS][3] = {
	{1.0f,1.0f,1.0f},
	{0.75f,0.75f,0.75f},
	{0.5f,0.5f,0.5f},
	{0.25f,0.25f,0.25f},
	{0.0f,0.0f,0.0f},
};
*/

const int NUM_SAMPLES_TAKEN = 3000;
const int NUM_QUANTILES = 40;