#ifndef SUPPORTSDL_H
#define SUPPORTSDL_H
#include <SDL.h>

void drawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius);
void drawFillCircle(SDL_Renderer* renderer, int& x, int& y, double& radi); // int& radius changed to double& radi

#endif 

