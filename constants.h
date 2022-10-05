#pragma once
//dimensions in the display
const int WINDOW_H = 1080;
const int WINDOW_W = 1920;
const float ASPECT_RATIO = (float)WINDOW_W / (float)WINDOW_H;
//dimensions in the math world
/*
const double MIN_X = 1.5;
const double MAX_X = 3;
const double MIN_Y = 0;
const double MAX_Y = 0.75;
*/
const float MIN_X = -5;
const float MAX_X = 5;
const float MIN_Y = -5;
const float MAX_Y = 5;

const float BACKGROUND[3] = {0.0f, 0.0f, 0.0f};
//diffeq
//higher = better performance, more jagged but longer lines
const float DELTA = 0.01f;
//if diffeq line is moving slower than this, stop rendering it
const float MINIMUM_SPEED = 0.0001f;
//higher = worse performance, longer lines
const int NUM_STEPS = 300;

const int NUM_LINES = 600;

const char OUTPUT_PATH[] = "out3.bmp";

//mandelbrot
const int NUM_ITERATIONS = 100;
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

const int NUM_SAMPLES_TAKEN = 5000;
const int NUM_QUANTILES = 30;