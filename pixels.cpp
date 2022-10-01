#include "SDL.h"
#include "constants.h"
#include <cmath>
#include <stdexcept>
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
//all vals must be between 0 and 255
Uint32 MakePixelFromRGB(int R, int G, int B) {
	//return (R & R_MASK) + (G & G_MASK) + (B & B_MASK) + (A_MASK);
	return 255 + (B << 8) + (G << 16) + (R << 24);
}

Uint32 MakePixelFromRGB(int R, int G, int B, int A) {
	//return (R & R_MASK) + (G & G_MASK) + (B & B_MASK) + (A & A_MASK);
	return A + (B << 8) + (G << 16) + (R << 24);
}

void GetRGBFromPixel(Uint32 pix, int* R, int* G, int* B) {
	*R = (pix & R_MASK) >> 24;
	*G = (pix & G_MASK) >> 16;
	*B = (pix & B_MASK) >> 8;
}

Uint32 AddColors(Uint32 first, Uint32 second) {
	Uint32 a = (second & A_MASK) >> 24;
	Uint32 na = 255 - a;
	Uint32 rb = ((na * (first & RB_MASK)) + (a * (second & RB_MASK))) >> 8;
	Uint32 ag = (na * ((first & AG_MASK) >> 8)) + (a * (ONEALPHA | ((second & G_MASK) >> 8)));
	return ((rb & RB_MASK) | (ag & AG_MASK));
}

void SetPixelColor(int xPix, int yPix, int R, int G, int B) {
	pixels[yPix * WINDOW_W + xPix] = MakePixelFromRGB(R, G, B);
}

void AddPixelColor(int xPix, int yPix, int R, int G, int B, int A) {
	Uint32 first = pixels[yPix * WINDOW_W + xPix];
	pixels[yPix * WINDOW_W + xPix] = AddColors(first, MakePixelFromRGB(R, G, B, A));
}

//sets all pixels one color
void SetAllPixels(int R, int G, int B) {
	Uint32 p = MakePixelFromRGB(R, G, B);
	for (int i = 0; i < WINDOW_W*WINDOW_H; i++) {
		pixels[i] = p;
	}
}

//default is black
void SetAllPixels() {
	SetAllPixels(0, 0, 0);
}

void SetPixelsTest() {
	SetAllPixels();
	//for (int i = 0; i < WINDOW_W*10; i++) {
	//	pixels[i] = 0x00ffffff;
	//}
	for (int x = 400; x < 500; x++) {
		for (int y = 0; y < 500; y++) {
			SetPixelColor(x, y, 255, 0, 0);
			//pixels[y*WINDOW_W+x] = 0xff0000ff;
		}
	}
	for (int x = 0; x < 500; x++) {
		for (int y = 400; y < 500; y++) {
			SetPixelColor(x, y, 0, 255, 0);
			//pixels[y*WINDOW_W+x] = 0x00ff00ff;
		}
	}
}

//pixels is pointer to array of pixels from left to right top to bottom
SDL_Surface* MakeSurfaceFromPixels() {
	int pitch = 4 * WINDOW_W;
	return SDL_CreateRGBSurfaceFrom(pixels, WINDOW_W, WINDOW_H, 32, pitch, R_MASK, G_MASK, B_MASK, A_MASK);
}

void PutPixelsOnScreen(SDL_Window *window, SDL_Renderer *renderer) {
	SDL_Surface* surf = MakeSurfaceFromPixels();
	if (surf == NULL) {
		//throw invalid_argument("surface not initialized from pixels correctly");
	}
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
	SDL_FreeSurface(surf);
	SDL_RenderCopy(renderer, tex, NULL, NULL);
}