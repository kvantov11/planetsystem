#ifndef SCREEN_H
#define SCREEN_H
#include <SDL.h>
#include <SDL_ttf.h>

inline constexpr int gScreenWidth{ 1280 };
inline constexpr int gScreenHeight{ 960 };
extern SDL_Renderer* gRenderer;
extern bool gInitSuccess;
extern TTF_Font* gFont;

void init();
void initText();
void createWindow();
void createRenderer();
void closeWindow();
void startSDL();
#endif