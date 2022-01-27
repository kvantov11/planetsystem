#include "debug.h"

#include "control.h"
#include "objects.h"
#include "screen.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>

int main(int, char*[])
{
	startSDL();
	setObjects();
	eventHandler();
	closeWindow();
	deleteObjects();
	return 0;
}
