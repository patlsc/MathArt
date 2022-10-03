//for multithreaded rendering of two-dimensional functions which output magnitude
//requires a function of the form:
//double GetMagnitude(int xPix, int yPix)
#include "constants.h"
#include "colors.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <vector>

typedef double twoddoublemagnitude(int, int);

//renders inclusive of all the bounds
//doing the actual function calculations
void RenderMagnitudeSquare(int minX, int maxX, int minY, int maxY, double(*magnitudeArray), twoddoublemagnitude f) {
	for (int xPix = minX; xPix <= maxX; xPix++) {
		for (int yPix = minY; yPix <= maxY; yPix++) {
			magnitudeArray[WINDOW_W * yPix + xPix] = f(xPix, yPix);
		}
	}
}

//coloring in the pixels based on function value
void SetPixelColorSquare(int minX, int maxX, int minY, int maxY, double(*magnitudeArray), double quantileArray[NUM_QUANTILES]) {
	for (int xPix = minX; xPix <= maxX; xPix++) {
		for (int yPix = minY; yPix <= maxY; yPix++) {
			SetPixelColor(xPix, yPix, AssignColorToObservation(magnitudeArray[yPix * WINDOW_W + xPix], quantileArray));
		}
	}
}

//sets all the pixels
void RenderMagnitudesMultithreaded(twoddoublemagnitude f) {
	//getting function values
	auto start = std::chrono::steady_clock::now();
	std::cout << "Rendering Function Values\n";

	const auto processor_count = std::thread::hardware_concurrency();
	double(*magnitudeArray) = new double[WINDOW_W * WINDOW_H];

	int num_threads_to_make = processor_count;
	//this is rounded down due to integer division, last thread may have to render extra pixels
	int xPixelsPerThread = WINDOW_W / num_threads_to_make;
	
	std::vector<std::thread> functionThreads;
	
	for (int i = 0; i < num_threads_to_make; i++) {
		int minX = i * xPixelsPerThread;
		int maxX = (i + 1) * xPixelsPerThread;
		if (i > 0) {
			minX += 1;
		}
		if (i == num_threads_to_make - 1) {
			//make sure last one fills it all out
			maxX = WINDOW_W-1;
		}
		int minY = 0;
		int maxY = WINDOW_H-1;
		functionThreads.emplace_back(std::thread(RenderMagnitudeSquare, minX, maxX, minY, maxY, magnitudeArray, f));
		std::cout << "\tStarting thread " << i + 1 << " on pixels [" << minX << "," << maxX << "]x[" << minY << "," << maxY << "]\n";
	}

	for (auto& t : functionThreads) {
		t.join();
	}
	
	/*
	std::thread t1(RenderMagnitudeSquare, 0, 200, 0, WINDOW_H, magnitudeArray, f);
	t1.join();
	std::thread t2(RenderMagnitudeSquare, 201, 400, 0, WINDOW_H, magnitudeArray, f);
	t2.join();
	std::thread t3(RenderMagnitudeSquare, 401, 600, 0, WINDOW_H, magnitudeArray, f);
	t3.join();
	std::thread t4(RenderMagnitudeSquare, 601, 800, 0, WINDOW_H, magnitudeArray, f);
	t4.join();
	std::thread t5(RenderMagnitudeSquare, 801, WINDOW_W, 0, WINDOW_H, magnitudeArray, f);
	t5.join();
	*/
	//RenderMagnitudeSquare(0, WINDOW_W-1, 0, WINDOW_H-1, magnitudeArray, f);

	auto end = std::chrono::steady_clock::now();
	float s = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0f;
	std::cout << "Finished Rendering Function Magnitudes in " << s << " seconds\n";

	//getting color distribution

	start = std::chrono::steady_clock::now();
	std::cout << "Generating Color Distribution\n";
	
	double samples[NUM_SAMPLES_TAKEN];
	for (int i = 0; i < NUM_SAMPLES_TAKEN; i++) {
		int xPix = GenerateRandomInt(0, WINDOW_W);
		int yPix = GenerateRandomInt(0, WINDOW_H);
		samples[i] = magnitudeArray[yPix * WINDOW_W + xPix];
	}
	double quantileArray[NUM_QUANTILES];
	ObtainQuantiles(samples, NUM_SAMPLES_TAKEN, &quantileArray);

	end = std::chrono::steady_clock::now();
	s = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0f;
	std::cout << "Finished Sampling Color Distribution in " << s << " seconds\n";

	//coloring in pixels based on distribution

	start = std::chrono::steady_clock::now();
	std::cout << "Coloring Pixels\n";

	//todo make this higher performance if it becomes a problem later on
	std::vector<std::thread> coloringThreads;
	for (int i = 0; i < num_threads_to_make; i++) {
		int minX = i * xPixelsPerThread;
		int maxX = (i + 1) * xPixelsPerThread;
		if (i > 0) {
			minX += 1;
		}
		if (i == num_threads_to_make - 1) {
			//make sure last one fills it all out
			maxX = WINDOW_W-1;
		}
		int minY = 0;
		int maxY = WINDOW_H-1;
		coloringThreads.emplace_back(std::thread(SetPixelColorSquare, minX, maxX, minY, maxY, magnitudeArray, quantileArray));
		std::cout << "\tStarting thread " << i + 1 << " on pixels [" << minX << "," << maxX << "]x[" << minY << "," << maxY << "]\n";
	}

	for (auto& t : coloringThreads) {
		t.join();
	}

	end = std::chrono::steady_clock::now();
	s = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0f;
	std::cout << "Finished Coloring Pixels in " << s << " seconds\n";
}