#include "constants.h"
#include "coords.h"

int32_t XCordToPixel(double xPos) {
    return (int32_t)((xPos - MIN_X) * WINDOW_W / (MAX_X - MIN_X));
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