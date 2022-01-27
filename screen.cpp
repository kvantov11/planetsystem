#include "debug.h"

#include "screen.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <iostream>


bool gInitSuccess{ true };
//extern int const screenWidth{ 1280};
//extern int const screenHeight{ 960 };

SDL_Window* window{ nullptr };
SDL_Renderer* gRenderer{ nullptr };
bool bInitDone{ false };
int imgFlags{ IMG_INIT_PNG };
TTF_Font* gFont = nullptr;

void init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		gInitSuccess = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}
	}
}
void initText()
{
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		gInitSuccess = false;
	}
	gFont = TTF_OpenFont("fonts/arial.ttf", 28);
	if (gFont == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		gInitSuccess = false;
	}
}
void createWindow()
{
	if (gInitSuccess)
	{
		window = SDL_CreateWindow("Planet system", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, gScreenWidth, gScreenHeight, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			gInitSuccess = false;
		}
	}
}
void createRenderer()
{
	if (gInitSuccess)
	{
		gRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (gRenderer == NULL)
		{
			printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			gInitSuccess = false;
		}
		else
		{
			//Initialize renderer color
			SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);

			//Initialize PNG loading
			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
				gInitSuccess = false;
			}
		}
	}
}
void closeWindow()
{
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(window);
	TTF_CloseFont(gFont);
	window = nullptr;
	gRenderer = nullptr;
	gFont = nullptr;
	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
}
void startSDL()
{
	if (!bInitDone)
	{
		init();
		initText();
		createWindow();
		createRenderer();
		bInitDone = true;
	}
}