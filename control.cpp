#include "debug.h"

//#include "camera.h"
#include "control.h"
#include "objects.h"
#include "screen.h"
#include <iostream>
#include <string>

SDL_Event e{};
bool quit{ false };
bool cameraFollow{ false };
double camX{ 0.0 };
double camY{ 0.0 };
int camCount{ 0 };

void eventHandler()
{
	if (gInitSuccess)
	{
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
				if (e.type == SDL_KEYDOWN)
				{
					switch (e.key.keysym.sym)
					{
					case SDLK_q:
						quit = true;
						break;
					case SDLK_UP:
						gCamera.cameraMovementDouble(0.0, -50.0);
						cameraFollow = false;
						break;
					case SDLK_DOWN:
						gCamera.cameraMovementDouble(0.0, 50.0);
						cameraFollow = false;
						break;
					case SDLK_LEFT:
						gCamera.cameraMovementDouble(-50.0, 0.0);
						cameraFollow = false;
						break;
					case SDLK_RIGHT:
						gCamera.cameraMovementDouble(50.0, 0.0);
						cameraFollow = false;
						break;
					case SDLK_c:
						cameraFollow = true;
						break;
					case SDLK_x:
						nextObject();
						break;
					case SDLK_y:
						previousObject();
						break;
					case SDLK_w:
						gCamera.cameraZoomIn();
						break;
					case SDLK_s:
						gCamera.cameraZoomOut();
						break;
					}
				}
			}
			if (cameraFollow)
			{
				camX = gBodyVector.at(camCount)->getCentrePosition().x - static_cast<double>(gScreenWidth) / 2.0 / gCamera.getCameraZoom();
				camY = gBodyVector.at(camCount)->getCentrePosition().y - static_cast<double>(gScreenHeight) / 2.0 / gCamera.getCameraZoom();
				gCamera.setCameraPositionDouble(camX, camY);

				gStr = "object: ";
				gStr += std::to_string(gBodyVector.at(camCount)->returnID());
				gName.loadFromRenderedText(gStr);

				gStr = "centre X: ";
				gStr += std::to_string(static_cast<int>(round(gBodyVector.at(camCount)->getCentrePosition().x)));
				gCentreX.loadFromRenderedText(gStr);

				gStr = "centre Y: ";
				gStr += std::to_string(static_cast<int>(round(gBodyVector.at(camCount)->getCentrePosition().y)));
				gCentreY.loadFromRenderedText(gStr);

				gStr = "velocity: ";
				gStr += std::to_string(static_cast<int>(round(gBodyVector.at(camCount)->getVelocity().value)));
				gVelocity.loadFromRenderedText(gStr);

				gStr = "velocity X: ";
				gStr += std::to_string(static_cast<int>(round(gBodyVector.at(camCount)->getVelocity().x)));
				gVelocityX.loadFromRenderedText(gStr);

				gStr = "velocity Y: ";
				gStr += std::to_string(static_cast<int>(round(gBodyVector.at(camCount)->getVelocity().y)));
				gVelocityY.loadFromRenderedText(gStr);
			}
			renderObjects(cameraFollow);
		}
	}
}
void nextObject()
{
	if (cameraFollow)
	{
		++camCount;
		if (camCount > gBodyVector.at(0)->returnCount() - 1) camCount = 0;
#ifdef DEBUG_CONTROL
		std::cout << "camCount: " << camCount << '\n';
#endif // DEBUG_CONTROL
	}
}
void previousObject()
{
	if (cameraFollow)
	{
		--camCount;
		if (camCount < 0) camCount = gBodyVector.at(0)->returnCount() - 1;
#ifdef DEBUG_CONTROL
		std::cout << "camCount: " << camCount << '\n';
#endif // DEBUG_CONTROL
	}
}
void zoomIn()
{

}
void zoomOut()
{

}
