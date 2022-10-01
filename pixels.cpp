#include "SDL.h"
#include "constants.h"
#include <cmath>
using namespace std;
//this is an interface for doing pixel by pixel manipulations
Uint32 pixels[WINDOW_W * WINDOW_H];

//endianess
Uint32 R_MASK = 0xff000000;
Uint32 G_MASK = 0x00ff0000;
Uint32 B_MASK = 0x0000ff00;
Uint32 A_MASK = 0x000000ff;
Uint32 RGB_MASK = 0xffffff00;
Uint32 RB_MASK = R_MASK | B_MASK;
Uint32 AG_MASK = A_MASK | G_MASK;
Uint32 ONEALPHA = 0x01000000;

//alpha is maximum
Uint32 MakePixelFromRGB(int R, int G, int B) {
	return (R & R_MASK) + (G & G_MASK) + (B & B_MASK) + (A_MASK);
}

Uint32 MakePixelFromRGB(int R, int G, int B, int A) {
	return (R & R_MASK) + (G & G_MASK) + (B & B_MASK) + (A & A_MASK);
}

Uint32 AddColors(Uint32 first, Uint32 second) {
	unsigned int a = (second & A_MASK) >> 24;
	unsigned int na = 255 - a;
	unsigned int rb = ((na * (first & RB_MASK)) + (a * (second & RB_MASK))) >> 8;
	unsigned int ag = (na * ((first & AG_MASK) >> 8)) + (a * (ONEALPHA | ((second & G_MASK) >> 8)));
	return ((rb & RB_MASK) | (ag & AG_MASK));
}

void SetPixelColor(int xPix, int yPix, int R, int G, int B) {
	pixels[yPix * WINDOW_W + xPix] = MakePixelFromRGB(R, G, B);
}

void AddPixelColor(int xPix, int yPix, int R, int G, int B, int A) {
	Uint32 first = pixels[yPix * WINDOW_W + xPix];
	pixels[yPix * WINDOW_W + xPix] = AddColors(first, MakePixelFromRGB(R, G, B, A));
}

//pixels is pointer to array of pixels from left to right top to bottom
SDL_Surface MakeSurfaceFromPixels() {
	int pitch = 4 * WINDOW_W;
	return SDL_CreateRGBSurfaceFrom(pixels, WINDOW_W, WINDOW_H, pitch, R_MASK, G_MASK, B_MASK, A_MASK);
}

void SetPixelsOnScreen(SDL_Window *window) {
	SDL_Surface surf = MakeSurfaceFromPixels();
}