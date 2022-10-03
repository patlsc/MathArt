#include "SDL.h"
#include <cmath>
#include "constants.h"
#include "coords.h"
#include "mandelbrot.h"
#include "pixels.h"
#include "colors.h"
#include "postprocessing.h"
#include "twodmagnitudes.h"
#include <iostream>
#include <chrono>
using namespace std;

//$(CoreLibraryDependencies);%(AdditionalDependencies)
//midpoint render algorithm for circles
void DrawCircle(SDL_Renderer *renderer, int32_t centerX, int32_t centerY, int32_t radius)
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
        SDL_RenderDrawPoint(renderer, centerX + x, centerY - y);
        SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
        SDL_RenderDrawPoint(renderer, centerX - x, centerY - y);
        SDL_RenderDrawPoint(renderer, centerX - x, centerY + y);
        SDL_RenderDrawPoint(renderer, centerX + y, centerY - x);
        SDL_RenderDrawPoint(renderer, centerX + y, centerY + x);
        SDL_RenderDrawPoint(renderer, centerX - y, centerY - x);
        SDL_RenderDrawPoint(renderer, centerX - y, centerY + x);

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

void DebugPrintPixel(Uint32 pix) {
    cout << "Full Value " << pix << "\n";
    cout << "Hex Full Value " << std::hex << pix << "\n";
    cout << "R" << ((pix & 0xff000000) >> 24) << ", G" << ((pix & 0x00ff0000) >> 16) << ", B" << ((pix & 0x0000ff00) >> 8) << ", A" << (pix & 0x000000ff) << "\n";
}

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,WINDOW_W,WINDOW_H,SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_UpdateWindowSurface(window);

    //SDL_SetRenderDrawColor(renderer, 0, 0, 255, 100);
    //SDL_RenderDrawLine(renderer, 0, 0, 500, 500);

    //DrawMandelbrot(renderer);

	//SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    //DrawManyDiffEqLines(renderer);

	//SDL_RenderDrawPoint(renderer, i, k);
    //DrawCircle(renderer, CENTER_W, CENTER_H, 30);
    /*SDL_Surface* img = SDL_GetWindowSurface(window);
    SDL_SaveBMP(img, "out2.bmp");
    SDL_UnlockSurface(img);*/


    /*cout << "this should add two pixels that are red and blue half and half";
    DebugPrintPixel(AddColors(MakePixelFromRGB(255, 0, 0, 127), MakePixelFromRGB(0, 255, 0, 127)));

    cout << "first pixel in pixels array\n";
    DebugPrintPixel(pixels[0]);
    Uint32 testFirstPixelPointTo;
    Uint32 *testFirstPixel = &testFirstPixelPointTo;
    SDL_Rect firstPixelRectPointTo;
    SDL_Rect* firstPixelRect = &firstPixelRectPointTo;
    (* firstPixelRect).x = 0;
    (* firstPixelRect).y = 0;
    (* firstPixelRect).w = 1;
    (* firstPixelRect).h = 1;
    SDL_RenderReadPixels(renderer, firstPixelRect, 0, testFirstPixel, 4 * WINDOW_W);
    cout << "first pixel displayed on screen\n";
    DebugPrintPixel(*testFirstPixel);*/

    //Uint32 checkpixels[WINDOW_W * WINDOW_H];
    //SDL_RenderReadPixels(renderer, NULL, 0, checkpixels, 4 * WINDOW_W);
    //for (int i = 0; i < 5; i++) {
    //    cout << checkpixels[i];
    //}

    /*
    //doesnt work completely at the very end, but good enough i guess
    double quantiles[] = {0,1,2,3,4,5,6,7,8,9};
    float colorScheme[][3] = {
    {1.0f,0.0f,0.0f}, //red
    {1.0f,1.0f,0.0f}, //orange
    {0.0f,1.0f,0.0f}, //green
    {0.0f,1.0f,1.0f}, //turquoise
    {0.0f,0.0f,1.0f}  //blue
    };
    Uint32 pix1 = AssignColorToObservation(0, quantiles, 10, colorScheme, 5);
    cout << "pix1, should be red";
    DebugPrintPixel(pix1);
    Uint32 pix2 = AssignColorToObservation(1, quantiles, 10, colorScheme, 5);
    cout << "pix2, should be in between red and purple";
    DebugPrintPixel(pix2);
    Uint32 pix3 = AssignColorToObservation(2, quantiles, 10, colorScheme, 5);
    cout << "pix3, should be purple";
    DebugPrintPixel(pix3);
    Uint32 pix4 = AssignColorToObservation(9, quantiles, 10, colorScheme, 5);
    cout << "pix4, should be blue";
    DebugPrintPixel(pix4);
    */

    RenderMagnitudesMultithreaded(GetMandelbrotMagnitude);

    PutPixelsOnScreen(window, renderer);
    SaveScreenshotBMP(window, renderer);

    SDL_RenderPresent(renderer);
	

    //Main loop flag
    bool quit = false;

    //Event handler
    SDL_Event e;
    while (!quit)
    {
        //Handle events on queue
        while (SDL_PollEvent(&e) != 0)
        {
            //User requests quit
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }
    }


	return 0;
}