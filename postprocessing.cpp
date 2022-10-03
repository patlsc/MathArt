#include "constants.h"
#include "pixels.h"

//antialiasing which does not involve downscaling
void PixelsPrefilterAntiAliasing() {

}

//more advanced B&W algorithm based on human eye sensitivity
void PixelsToGreyscaleLuma() {
	for (int xPix = 0; xPix < WINDOW_W; xPix++) {
		for (int yPix = 0; yPix < WINDOW_H; yPix++) {
			int R, G, B;
			GetRGBFromPixel(GetPixelColor(xPix,yPix), &R, &G, &B);
			int gray = (int)(((float)R * 0.2126f + (float)G * 0.7152f + (float)B * 0.0722f));
			SetPixelColor(xPix, yPix, gray, gray, gray);
		}
	}
}

//percent between -100 and 100
void PixelsChangeSaturation(SDL_Renderer *renderer, double percent) {

}

void PixelsChangeHue(SDL_Renderer* renderer, double percent) {

}