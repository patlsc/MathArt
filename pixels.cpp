#include "SDL.h"
#include "constants.h"
#include <cmath>
using namespace std;
//this is an interface for doing pixel by pixel manipulations

//endianess
Uint32 R_MASK = 0xff000000;
Uint32 G_MASK = 0x00ff0000;
Uint32 B_MASK = 0x0000ff00;
Uint32 A_MASK = 0x000000ff;

//alpha is maximum
Uint32 MakePixelFromRGB(int R, int G, int B) {
	return (R & R_MASK) + (G & G_MASK) + (B & B_MASK) + (A_MASK);
}

Uint32 MakePixelFromRGB(int R, int G, int B, int A) {
	return (R & R_MASK) + (G & G_MASK) + (B & B_MASK) + (A & A_MASK);
}

Uint32 GetPixel(int xPix, int yPix) {

}

//pixels is pointer to array of pixels from left to right top to bottom
SDL_Surface MakeSurfaceFromPixels(void *pixels, int w, int h) {
	int pitch = 4 * w;
	return SDL_CreateRGBSurfaceFrom(pixels, w, h, pitch, R_MASK, G_MASK, B_MASK, A_MASK);
}

void SetPixelsOnScreen(SDL_Window *window, void* pixels) {
	SDL_Surface surf = MakeSurfaceFromPixels(pixels, WINDOW_W, WINDOW_H);
	
}