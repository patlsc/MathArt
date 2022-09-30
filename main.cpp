#include "SDL.h"
#include <cmath>
using namespace std;

//dimensions in the display
const int WINDOW_H = 1000;
const int WINDOW_W = 1000;
//dimensions in the math world
const double MIN_X = -10;
const double MAX_X = 10;
const double MIN_Y = -10;
const double MAX_Y = 10;

//higher = better performance, more jagged but longer lines
const double DELTA = 0.005;
//higher = worse performance, longer lines
const int NUM_STEPS = 500;

const int NUM_LINES = 900;

const char OUTPUT_PATH[] = "out3.bmp";

int32_t XCordToPixel(double xPos) {
    return (int32_t)((xPos - MIN_X)* WINDOW_W / (MAX_X - MIN_X));
}

int32_t YCordToPixel(double yPos) {
    return (int32_t)((yPos - MIN_Y) * WINDOW_H / (MAX_Y - MIN_Y));
}

double XPixelToCord(int32_t xPixel) {
    return MIN_X + ((double)xPixel) * (MAX_X - MIN_X) / WINDOW_W;
}

double YPixelToCord(int32_t yPixel) {
    return MIN_Y + ((double)yPixel) * (MAX_Y - MIN_Y) / WINDOW_H;
}

double RandRange(double fMin, double fMax) {
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

double XDerivative(double xPos, double yPos) {
    return yPos;
}

double YDerivative(double xPos, double yPos) {
    return -xPos+0.3*yPos;
}

void DrawDiffEqLine(SDL_Renderer* renderer, double startXPos, double startYPos) {
    double xPos = startXPos;
    double yPos = startYPos;
    for (int i = 0; i < NUM_STEPS; i++) {
        
        double nextXPos = xPos + XDerivative(xPos, yPos)*DELTA;
        double nextYPos = yPos + YDerivative(xPos, yPos)*DELTA;

        SDL_RenderDrawLine(renderer, XCordToPixel(xPos), YCordToPixel(yPos), XCordToPixel(nextXPos), YCordToPixel(nextYPos));
        xPos = nextXPos;
        yPos = nextYPos;
    }
}

void DrawManyDiffEqLines(SDL_Renderer *renderer) {
    for (int i = 0; i < NUM_LINES; i++) {
        
        double xPos = RandRange(MIN_X, MAX_X);
        double yPos = RandRange(MIN_Y, MAX_Y);
        DrawDiffEqLine(renderer, xPos, yPos);

    }
}

//midpoint render algorithm for circles
void DrawCircle(SDL_Renderer *renderer, int32_t centreX, int32_t centreY, int32_t radius)
{
    const int32_t diameter = (radius * 2);

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y)
    {
        //  Each of the following renders an octant of the circle
        SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}

bool SaveScreenshotBMP(SDL_Window* SDLWindow, SDL_Renderer* SDLRenderer) {
    SDL_Surface* saveSurface = NULL;
    SDL_Surface* infoSurface = NULL;
    infoSurface = SDL_GetWindowSurface(SDLWindow);
    if (infoSurface == NULL) {

    }
    else {
        unsigned char* pixels = new (std::nothrow) unsigned char[infoSurface->w * infoSurface->h * infoSurface->format->BytesPerPixel];
        if (pixels == 0) {
            return false;
        }
        else {
            if (SDL_RenderReadPixels(SDLRenderer, &infoSurface->clip_rect, infoSurface->format->format, pixels, infoSurface->w * infoSurface->format->BytesPerPixel) != 0) {
                delete[] pixels;
                return false;
            }
            else {
                saveSurface = SDL_CreateRGBSurfaceFrom(pixels, infoSurface->w, infoSurface->h, infoSurface->format->BitsPerPixel, infoSurface->w * infoSurface->format->BytesPerPixel, infoSurface->format->Rmask, infoSurface->format->Gmask, infoSurface->format->Bmask, infoSurface->format->Amask);
                if (saveSurface == NULL) {
                    delete[] pixels;
                    return false;
                }
                SDL_SaveBMP(saveSurface, OUTPUT_PATH);
                SDL_FreeSurface(saveSurface);
                saveSurface = NULL;
            }
            delete[] pixels;
        }
        SDL_FreeSurface(infoSurface);
        infoSurface = NULL;
    }
    return true;
}

int main(int argc, char* argv[]) {

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,WINDOW_W,WINDOW_H,SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_UpdateWindowSurface(window);

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 100);
    SDL_RenderDrawLine(renderer, 0, 0, 500, 500);
	//SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    //DrawManyDiffEqLines(renderer);

	//SDL_RenderDrawPoint(renderer, i, k);
    //DrawCircle(renderer, CENTER_W, CENTER_H, 30);
    /*SDL_Surface* img = SDL_GetWindowSurface(window);
    SDL_SaveBMP(img, "out2.bmp");
    SDL_UnlockSurface(img);*/
    SaveScreenshotBMP(window, renderer);

    SDL_RenderPresent(renderer);
	SDL_Delay(3000);

	return 0;
}