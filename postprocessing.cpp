#include "SDL.h"

//antialiasing which does not involve downscaling
void PrefilterAntiAliasing(SDL_Renderer *renderer) {

}

//for antialiasing involving rendering at a high scale first
SDL_Renderer* DownsizeRenderer(SDL_Renderer *original, int NEW_WIDTH, int NEW_HEIGHT) {

}

//note: this doesnt merely average the RGB values
//
void ToBlackAndWhiteLuma(SDL_Renderer *renderer) {

}

//percent between -100 and 100
void ChangeSaturation(SDL_Renderer *renderer, double percent) {

}

void ChangeHue(SDL_Renderer* renderer, double percent) {

}