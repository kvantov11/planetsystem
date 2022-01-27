#include "debug.h"

#include "camera.h"
#include "celestialBody.h"
#include "objects.h"
#include "screen.h"
#include "texture.h"
#include <SDL.h>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

Camera gCamera(0.0, 0.0, 1280.0, 960.0);
Texture background("img/space_background.png", 0.0, 0.0);

SDL_Color textColor{255,255,255};
//Texture slovo("test", 10, 10, textColor);
Texture controlW("W - zoom in", 1000, 10, textColor);
Texture controlS("S - zoom in", 1000, 40, textColor);
Texture controlC("C - follow object", 1000, 70, textColor);
Texture controlX("X - next object", 1000, 100, textColor);
Texture controlY("Y - previous object", 1000, 130, textColor);
Texture controlQ("Q - quit", 1000, 160, textColor);
Texture controlArrows("Arrows - free roam", 1000, 190, textColor);

Texture gName;
Texture gCentreX;
Texture gCentreY;
Texture gVelocity;
Texture gVelocityX;
Texture gVelocityY;

std::string gStr{ "test" };

std::vector<CelestialBody*> gBodyVector;
constexpr int N{ 5 };
Centre centreObj[N];
Body bodyObj[N];
Velocity velocityObj[N];
CelestialBodyInput body[N];
SDL_Color colorObj[N];

void setObjects() 
{
	centreObj[0] = { 450.0,		400.0 };
	centreObj[1] = { 450.0,		500.0 };
	centreObj[2] = { 450.0,		600.0 };
	centreObj[3] = { 450.0,		700.0 };
	centreObj[4] = { 28'000.0,	800.0 };

	bodyObj[0] = { 1'000'000.0,		50.0 };
	bodyObj[1] = { 100.0,			10.0 };
	bodyObj[2] = { 10'000.0,		20.0 };
	bodyObj[3] = { 10.0,			5.0 };
	bodyObj[4] = { 10'000'000.0,	80.0 };

	velocityObj[0] = { 0.0,		0.0 };
	velocityObj[1] = { 170.0,	90.0 };
	velocityObj[2] = { 120.0,	90.0 };
	velocityObj[3] = { 100.0,	90.0 };
	velocityObj[4] = { 1'000.0,	270.0 };

	colorObj[0] = { 0xFF, 0x00, 0x00, 0xFF };
	colorObj[1] = { 0x00, 0xFF, 0x00, 0xFF };
	colorObj[2] = { 0x00, 0x00, 0xFF, 0xFF };
	colorObj[3] = { 0x00, 0xFF, 0xFF, 0xFF };
	colorObj[4] = { 0xFF, 0xFF, 0xFF, 0xFF };


	for (int i = 0; i < N; ++i)
	{
		body[i].set(centreObj[i],bodyObj[i],velocityObj[i], colorObj[i], gBodyVector);
	}
	gName.loadFromRenderedText(gStr);
	gName.setPosition(10, 10);
	gName.setColor(255, 255, 255);

	gCentreX.loadFromRenderedText(gStr);
	gCentreX.setPosition(10, 50);
	gCentreX.setColor(255, 255, 255);

	gCentreY.loadFromRenderedText(gStr);
	gCentreY.setPosition(10, 100);
	gCentreY.setColor(255, 255, 255);

	gVelocity.loadFromRenderedText(gStr);
	gVelocity.setPosition(10, 150);
	gVelocity.setColor(255, 255, 255);

	gVelocityX.loadFromRenderedText(gStr);
	gVelocityX.setPosition(10, 200);
	gVelocityX.setColor(255, 255, 255);

	gVelocityY.loadFromRenderedText(gStr);
	gVelocityY.setPosition(10, 250);
	gVelocityY.setColor(255, 255, 255);
}

void renderObjects(const bool cameraFollow)
{
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(gRenderer); 
	background.renderBackground(gCamera, gRenderer);
	for (int i = 0; i < N; ++i) { gBodyVector.at(i)->render(gCamera, gRenderer); }
	controlW.renderText(gRenderer);
	controlS.renderText(gRenderer);
	controlC.renderText(gRenderer);
	controlX.renderText(gRenderer);
	controlY.renderText(gRenderer);
	controlQ.renderText(gRenderer);
	controlArrows.renderText(gRenderer);
	//slovo.renderText(gRenderer);
	if (cameraFollow)
	{
		gName.renderText(gRenderer);
		gCentreX.renderText(gRenderer);
		gCentreY.renderText(gRenderer);
		gVelocity.renderText(gRenderer);
		gVelocityX.renderText(gRenderer);
		gVelocityY.renderText(gRenderer);
	}
	SDL_RenderPresent(gRenderer);
	for (int i = 0; i < N; ++i)  gBodyVector.at(i)->solveForces(gBodyVector);
	body->updatePosition(gBodyVector);

	
}

void deleteObjects()
{
	for (int i = 0; i < N; ++i)
	{
		body[i].~CelestialBodyInput();
	}
	gBodyVector.clear();
}
