#pragma once
#include "SDL.h"
Uint32 pixels[];
Uint32 MakePixelFromRGB(int R, int G, int B);
Uint32 MakePixelFromRGB(int R, int G, int B, int A);
void SetPixelColor(int xPix, int yPix, Uint32 val);
Uint32 AddColors(Uint32 first, Uint32 second);
Uint32 MakePixelFromRGBFloats(float R, float G, float B);

void SetPixelsTest();
void PutPixelsOnScreen(SDL_Window* window, SDL_Renderer* renderer);