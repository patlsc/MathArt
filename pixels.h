#pragma once
#include "SDL.h"
Uint32 pixels[];
Uint32 MakePixelFromRGB(int R, int G, int B);
Uint32 MakePixelFromRGB(int R, int G, int B, int A);
Uint32 ChangeBrightness(Uint32 val, float brightness);
Uint32 AddColorOnTop(Uint32 first, Uint32 second);
void GetRGBFromPixel(Uint32 pix, int* R, int* G, int* B);
Uint32 GetPixelColor(int xPix, int yPix);
void AddPixelColor(int xPix, int yPix, int R, int G, int B, int A);
void AddPixelRectangle(int x0, int y0, int x1, int y1, int R, int G, int B, int A);
void PixelsAddUnaliasedLine(int x0, int y0, int x1, int y1, Uint32 val);
void PixelsAddAliasedLine(float x0, float y0, float x1, float y1, Uint32 val);
void SetPixelColor(int xPix, int yPix, Uint32 val);
void SetPixelColor(int xPix, int yPix, int R, int G, int B);
Uint32 AddColors(Uint32 first, Uint32 second);
Uint32 MakePixelFromRGBFloats(float R, float G, float B);

void SetPixelsTest();
void PutPixelsOnScreen(SDL_Window* window, SDL_Renderer* renderer);