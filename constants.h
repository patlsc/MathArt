#pragma once
//dimensions in the display
const int WINDOW_H = 1000;
const int WINDOW_W = 1500;
//dimensions in the math world
const double MIN_X = -2;
const double MAX_X = 1;
const double MIN_Y = -1;
const double MAX_Y = 1;

//diffeq
//higher = better performance, more jagged but longer lines
const double DELTA = 0.005;
//higher = worse performance, longer lines
const int NUM_STEPS = 500;

const int NUM_LINES = 900;

const char OUTPUT_PATH[] = "out3.bmp";

//mandelbrot
const int NUM_ITERATIONS = 100;
const double MAX_MAGNITUDE = 1000000000;