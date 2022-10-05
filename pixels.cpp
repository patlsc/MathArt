#include "SDL.h"
#include "constants.h"
#include <cmath>
#include <stdexcept>
#include <iostream>
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

//floats between 0 and 1
Uint32 MakePixelFromRGBFloats(float R, float G, float B) {
	return 255 + ((int)(B * 255) << 8) + ((int)(G * 255) << 16) + ((int)(R * 255) << 24);
}

Uint32 MakePixelFromRGBAFloats(float R, float G, float B, float A) {
	return (int)(A*255) + ((int)(B * 255) << 8) + ((int)(G * 255) << 16) + ((int)(R * 255) << 24);
}

void GetRGBFloatsFromPixel(Uint32 pix, float* R, float* G, float* B) {
	*R = float((pix & R_MASK) >> 24) / 255.0f;
	*G = float((pix & G_MASK) >> 16) / 255.0f;
	*B = float((pix & B_MASK) >> 8) / 255.0f;
}

void GetRGBAFloatsFromPixel(Uint32 pix, float* R, float* G, float* B, float* A) {
	*R = float((pix & R_MASK) >> 24) / 255.0f;
	*G = float((pix & G_MASK) >> 16) / 255.0f;
	*B = float((pix & B_MASK) >> 8) / 255.0f;
	*A = float((pix & A_MASK)) / 255.0f;
}

//assumes both are full transparency
Uint32 BlendColors(float R1, float G1, float B1, float R2, float G2, float B2, float alpha) {
	return MakePixelFromRGBFloats((1.0f - alpha) * R1 + alpha * R2, (1.0f - alpha) * G1 + alpha * G2, (1.0f - alpha) * B1 + alpha * B2);
}

//if brightness is 1, gives original color
Uint32 ChangeBrightness(Uint32 val, float brightness) {
	int R, G, B;
	GetRGBFromPixel(val, &R, &G, &B);
	R = (int)(R * brightness);
	G = (int)(G * brightness);
	B = (int)(B * brightness);
	return MakePixelFromRGB(R, G, B);
}

Uint32 GetPixelColor(int xPix, int yPix) {
	return pixels[yPix * WINDOW_W + xPix];
}

void SetPixelColor(int xPix, int yPix, Uint32 val) {
	pixels[yPix * WINDOW_W + xPix] = val;
}

void SetPixelColor(int xPix, int yPix, int R, int G, int B) {
	pixels[yPix * WINDOW_W + xPix] = MakePixelFromRGB(R, G, B);
}

//we assume that first color has full opacity
//so if we are adding color for the first time,
//we set it to AddColorOntoFlat(BACKGROUND_INT, second);
//then from there on out we do AddColorOntoFlat(existing_pixel,new);
Uint32 BACKGROUND_INT = 0x00000000;
Uint32 AddColorOnTop(Uint32 first, Uint32 second) {
	/*Uint32 a = (float)(second && A_MASK) / 255.0f;
	Uint32 na = 1.0f-a;
	Uint32 total_A = (first && A_MASK)+a<255? (first&&A_MASK)+a:255;
	Uint32 RB = na * (first & RB_MASK) + a * (second & RB_MASK);
	Uint32 G = na * (first & G_MASK) + a * (second & G_MASK);
	return RB + G + total_A;*/
	float R0, G0, B0, A0;
	float R1, G1, B1, A1;
	GetRGBAFloatsFromPixel(first, &R0, &G0, &B0, &A0);
	GetRGBAFloatsFromPixel(second, &R1, &G1, &B1, &A1);
	return MakePixelFromRGBAFloats(R0 * A0 + R1 * A1, G0 * A0 + G1 * A1, B0 * A0 + B1 * A1, A0 + A1);
}

//note: in general faster to calculate color first
//if it wont change
void AddPixelColor(int xPix, int yPix, int R, int G, int B, int A) {
	Uint32 first = pixels[yPix * WINDOW_W + xPix];
	pixels[yPix * WINDOW_W + xPix] = AddColorOnTop(first, MakePixelFromRGB(R, G, B, A));
}

void AddPixelRectangle(int x0, int y0, int x1, int y1, int R, int G, int B, int A) {
	for (int i = x0; i <= x1; i++) {
		for (int j = y0; j <= y1; j++) {
			AddPixelColor(i, j, R, G, B, A);
		}
	}
}

//bresenham's unaliased line algorithm
void PixelsAddUnaliasedLine(int x0, int y0, int x1, int y1, Uint32 val) {
	int dx = abs(x1 - x0);
	int sx = x0 < x1 ? 1 : -1;
	int dy = -abs(y1 - y0);
	int sy = y0 < y1 ? 1 : -1;
	int error = dx + dy;
	while (true) {
		SetPixelColor(x0, y0, val);
		if (x0 == x1 && y0 == y1) {
			break;
		}
		int e2 = 2 * error;
		if (e2 >= dy) {
			if (x0 == x1) {
				break;
			}
			error += dy;
			x0 = x0 + sx;
		}
		if (e2 <= dx) {
			if (y0 == y1) {
				break;
			}
			error += dx;
			y0 = y0 + sy;
		}
	}
}

//xiaolin wu's line algorithm
//takes floating pixels which can be obtained with XCordToFloatingPixel
int ipart(float val) {
	return (int)floor(val);
}

float fpart(float val) {
	return val - floor(val);
}

float rfpart(float val) {
	return 1 - fpart(val);
}

//brightness is in [0,1]
void SetPixelColorWithAlpha(int xPix, int yPix, float R, float G, float B, float alpha) {
	SetPixelColor(xPix, yPix, BlendColors(BACKGROUND[0], BACKGROUND[1], BACKGROUND[2], R, G, B, alpha));
}

//equivalent to setpixelcolorwithalpha if the background is black, faster
void SetPixelColorWithBrightness(int xPix, int yPix, Uint32 val, float alpha) {
	if (xPix < WINDOW_W && xPix > 0 && yPix < WINDOW_H && yPix > 0) {
		SetPixelColor(xPix, yPix, ChangeBrightness(val, alpha));
	}
}

void SetPixelColorWithBrightness(float xPix, float yPix, Uint32 val, float alpha) {
	if (xPix < WINDOW_W && xPix > 0 && yPix < WINDOW_H && yPix > 0) {
		SetPixelColor((int)xPix, (int)yPix, ChangeBrightness(val, alpha));
	}
}

void PixelsAddAliasedLine(float x0, float y0, float x1, float y1, Uint32 val) {
	const bool steep = abs(y1 - y0) > abs(x1 - x0);
	if (steep) {
		std::swap(x0, y0);
		std::swap(x1, y1);
	}
	if (x0 > x1) {
		std::swap(x0, x1);
		std::swap(y0, y1);
	}

	const float dx = x1 - x0;
	const float dy = y1 - y0;
	const float gradient = (dx == 0) ? 1 : dy / dx;

	int xpx11;
	float intery;
	{
		const float xend = round(x0);
		const float yend = y0 + gradient * (xend - x0);
		const float xgap = rfpart(x0 + 0.5);
		xpx11 = int(xend);
		const int ypx11 = ipart(yend);
		if (steep) {
			SetPixelColorWithBrightness(ypx11, xpx11, val, rfpart(yend) * xgap);
			SetPixelColorWithBrightness(ypx11 + 1, xpx11, val, fpart(yend) * xgap);
		}
		else {
			SetPixelColorWithBrightness(xpx11, ypx11, val, rfpart(yend) * xgap);
			SetPixelColorWithBrightness(xpx11, ypx11 + 1, val, fpart(yend) * xgap);
		}
		intery = yend + gradient;
	}

	int xpx12;
	{
		const float xend = round(x1);
		const float yend = y1 + gradient * (xend - x1);
		const float xgap = rfpart(x1 + 0.5);
		xpx12 = int(xend);
		const int ypx12 = ipart(yend);
		if (steep) {
			SetPixelColorWithBrightness(ypx12, xpx12, val, rfpart(yend) * xgap);
			SetPixelColorWithBrightness(ypx12 + 1, xpx12, val, fpart(yend) * xgap);
		}
		else {
			SetPixelColorWithBrightness(xpx12, ypx12, val, rfpart(yend) * xgap);
			SetPixelColorWithBrightness(xpx12, ypx12 + 1, val, fpart(yend) * xgap);
		}
	}

	if (steep) {
		for (int x = xpx11 + 1; x < xpx12; x++) {
			SetPixelColorWithBrightness(ipart(intery), x, val, rfpart(intery));
			SetPixelColorWithBrightness(ipart(intery) + 1, x, val, fpart(intery));
			intery += gradient;
		}
	}
	else {
		for (int x = xpx11 + 1; x < xpx12; x++) {
			SetPixelColorWithBrightness(x, ipart(intery), val, rfpart(intery));
			SetPixelColorWithBrightness(x, ipart(intery) + 1, val, fpart(intery));
			intery += gradient;
		}
	}
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
			AddPixelColor(x, y, 255, 0, 0, 125);
			//pixels[y*WINDOW_W+x] = 0xff0000ff;
		}
	}
	for (int x = 0; x < 500; x++) {
		for (int y = 400; y < 500; y++) {
			AddPixelColor(x, y, 125, 255, 255, 125);
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