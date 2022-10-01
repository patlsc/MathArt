#pragma once
#include "SDL.h"
Uint32 pixels[];
Uint32 MakePixelFromRGB(int R, int G, int B);
Uint32 MakePixelFromRGB(int R, int G, int B, int A);
void SetPixelsTest();
void PutPixelsOnScreen(SDL_Window* window, SDL_Renderer* renderer);