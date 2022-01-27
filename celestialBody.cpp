#include "debug.h"

#include "camera.h"
#include "celestialBody.h"
#include "screen.h"
#include "supportSDL.h"
#include <math.h>
#include <SDL.h>
#include <iostream>
#include <iomanip>

int CelestialBody::s_celestialBodyObjCounter = 0;
CelestialBody::CelestialBody(Centre cen, Body bod, Velocity vel, SDL_Color col)
{
	m_celestialBodyCentre = cen;
	m_celestialBodyBody = bod;
	m_celestialBodyVelocity = vel;
	m_celestialBodyColor = col;

	m_celestialBodyVelocity.x = sin(m_celestialBodyVelocity.angle / 180.0 * pi) * m_celestialBodyVelocity.value;
	m_celestialBodyVelocity.y = -cos(m_celestialBodyVelocity.angle / 180.0 * pi) * m_celestialBodyVelocity.value;

	m_celestialBodyRectDouble.x = static_cast<int>(round(m_celestialBodyCentre.x - m_celestialBodyBody.radius));
	m_celestialBodyRectDouble.y = static_cast<int>(round(m_celestialBodyCentre.y - m_celestialBodyBody.radius));
	m_celestialBodyRectDouble.w = static_cast<int>(round(2.0 * m_celestialBodyBody.radius));
	m_celestialBodyRectDouble.h = static_cast<int>(round(2.0 * m_celestialBodyBody.radius));

	++s_celestialBodyObjCounter;
	m_celestialBodyObjectID = s_celestialBodyObjCounter;
}
int CelestialBody::returnCount() { return s_celestialBodyObjCounter; }
int CelestialBody::returnID() const { return m_celestialBodyObjectID; }
void CelestialBody::render(Camera& cam, SDL_Renderer* renderer)
{
	if (cam.inputObjectRectDouble(m_celestialBodyRectDouble)) // render circle if circle is in camera
	{
		m_celestialBodyCameraOffset.x = static_cast<int>(round(m_celestialBodyCentre.x - cam.getCameraRectDouble().x) * cam.getCameraZoom());
		m_celestialBodyCameraOffset.y = static_cast<int>(round(m_celestialBodyCentre.y - cam.getCameraRectDouble().y) * cam.getCameraZoom());

		SDL_SetRenderDrawColor(renderer, m_celestialBodyColor.r, m_celestialBodyColor.g, m_celestialBodyColor.b, m_celestialBodyColor.a);
		m_celestialBodyBody.radius = m_celestialBodyBody.radius * cam.getCameraZoom();
		drawFillCircle(renderer, m_celestialBodyCameraOffset.x, m_celestialBodyCameraOffset.y, m_celestialBodyBody.radius);
		m_celestialBodyBody.radius = m_celestialBodyBody.radius / cam.getCameraZoom();
	}
}
const Centre& CelestialBody::getCentrePosition() const { return m_celestialBodyCentre; }
double& CelestialBody::accessCentreX() { return m_celestialBodyCentre.x; }
double& CelestialBody::accessCentreY() { return m_celestialBodyCentre.y; }
double& CelestialBody::accessVelocityX() { return m_celestialBodyVelocity.x; }
double& CelestialBody::accessVelocityY() { return m_celestialBodyVelocity.y; }
double& CelestialBody::accessTextureRectX() { return m_celestialBodyRectDouble.x; }
double& CelestialBody::accessTextureRectY() { return m_celestialBodyRectDouble.y; }
double CelestialBody::getMass() const { return m_celestialBodyBody.mass; }
double CelestialBody::getRadius() const { return m_celestialBodyBody.radius; }
void CelestialBody::updatePosition(std::vector<CelestialBody*>& vec)
{
	for (int i = 0; i < returnCount(); ++i)
	{
		vec.at(i)->accessCentreX() += vec.at(i)->accessVelocityX() * deltaT;
		vec.at(i)->accessCentreY() += vec.at(i)->accessVelocityY() * deltaT;
		vec.at(i)->accessTextureRectX() = static_cast<int>(round(vec.at(i)->getCentrePosition().x - vec.at(i)->getRadius()));
		vec.at(i)->accessTextureRectY() = static_cast<int>(round(vec.at(i)->getCentrePosition().y - vec.at(i)->getRadius()));
	}
}
void CelestialBody::solveForces(std::vector<CelestialBody*>& vec)
{
	m_celestialBodyForce.value = 0.0;
	m_celestialBodyForce.x = 0.0;
	m_celestialBodyForce.y = 0.0;
	for (int i = 0; i < returnCount(); ++i) // use all objects to calculate final force affecting 1 object
	{
		if (i == returnID() - 1) continue; // affected onbject has to be removed from calculating forces because its distance = 0
		m_celestialBodyObject.xOffset = m_celestialBodyCentre.x - vec.at(i)->accessCentreX();
		m_celestialBodyObject.yOffset = m_celestialBodyCentre.y - vec.at(i)->accessCentreY();
		m_celestialBodyObject.distance = sqrt(pow(m_celestialBodyObject.xOffset, 2) + pow(m_celestialBodyObject.yOffset, 2));
		m_celestialBodyForce.value = G * m_celestialBodyBody.mass * vec.at(i)->getMass()/pow(m_celestialBodyObject.distance,2);
		m_celestialBodyForce.x += -m_celestialBodyObject.xOffset / m_celestialBodyObject.distance * m_celestialBodyForce.value;
		m_celestialBodyForce.y += -m_celestialBodyObject.yOffset / m_celestialBodyObject.distance * m_celestialBodyForce.value;
	}
	updateVelocity();
	
}
void CelestialBody::updateVelocity()
{
	m_celestialBodyVelocity.x += m_celestialBodyForce.x / m_celestialBodyBody.mass * deltaT;
	m_celestialBodyVelocity.y += m_celestialBodyForce.y / m_celestialBodyBody.mass * deltaT;
	m_celestialBodyVelocity.value = sqrt(pow(m_celestialBodyVelocity.x, 2) + pow(m_celestialBodyVelocity.y, 2));
}
void CelestialBody::simulateGravity(std::vector<CelestialBody*>& vec)
{
	solveForces(vec);
	//updateVelocity();
	//updatePosition();
	//najskor simulate forces pre vsetky objekty spocitaj a rychlosti
	//az potom mozem prepocitat polohy objektov
}

CelestialBodyInput::CelestialBodyInput()
{
	newCircle = nullptr;
}
void CelestialBodyInput::set(Centre cen, Body bod, Velocity vel, SDL_Color col, std::vector<CelestialBody*>& vec)
{
	newCircle = new CelestialBody(cen, bod, vel, col);
	if (newCircle != nullptr) vec.push_back(newCircle);
	else std::cout << "Error, nullptr in celestialBody\n";
}
CelestialBodyInput::~CelestialBodyInput()
{
	delete newCircle;
	newCircle = nullptr;
}
void CelestialBodyInput::updatePosition(std::vector<CelestialBody*>& vec)
{
	for (int i = 0; i < vec.at(0)->returnCount(); ++i)
	{
		vec.at(i)->accessCentreX() += vec.at(i)->accessVelocityX() * deltaT;
		vec.at(i)->accessCentreY() += vec.at(i)->accessVelocityY() * deltaT;
		vec.at(i)->accessTextureRectX() = static_cast<int>(round(vec.at(i)->getCentrePosition().x - vec.at(i)->getRadius()));
		vec.at(i)->accessTextureRectY() = static_cast<int>(round(vec.at(i)->getCentrePosition().y - vec.at(i)->getRadius()));
	}
}