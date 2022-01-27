#ifndef OBJECTS_H
#include "celestialBody.h"
#include "texture.h"
#include <vector>

extern std::vector<CelestialBody*> gBodyVector;
extern Camera gCamera;
extern Texture gName;
extern Texture gCentreX;
extern Texture gCentreY;
extern Texture gVelocity;
extern Texture gVelocityX;
extern Texture gVelocityY;
extern std::string gStr;

void renderObjects(const bool objectCameraFollow);
void setObjects();
void deleteObjects();
#endif

