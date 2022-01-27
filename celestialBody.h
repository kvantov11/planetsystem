#ifndef CELESTIALBODY_H
#define CELESTIALBODY_H

#include "camera.h"
#include "screen.h"
#include <SDL.h>
#include <vector>

constexpr double deltaT{ 1.0 / 60.0 };									// seconds per frame
constexpr double pi = 3.14159265358979323846;							// pi constant
const double G = 100.0* 6.0 * pi * 2.0 * pow(500.0, 2.0) / 360.0 / 1000000.0;	// gravitational constant
// x centre, y centre
struct Centre
{
	double x{};
	double y{};
};
// mass, radius
struct Body
{
	double mass{};
	double radius{};
};
// value, angle [°], x component, y component
struct Velocity
{
	double value{};
	double angle{};
	double x{};
	double y{};
};
struct Force
{
	double value{};
	double x{};
	double y{};
};
struct Neighbour
{
	double distance{};
	double xOffset{};
	double yOffset{};
};
struct CameraOffset
{
	int x{};
	int y{};
};

class CelestialBody
{
private:
	Centre m_celestialBodyCentre;
	Body m_celestialBodyBody;
	Velocity m_celestialBodyVelocity;
	SDL_Color m_celestialBodyColor;
	Force m_celestialBodyForce;
	Neighbour m_celestialBodyObject;
	CameraOffset m_celestialBodyCameraOffset;
	g_struct_RectDouble m_celestialBodyRectDouble;	// create rectangle around circle, used for camera solver
	static int s_celestialBodyObjCounter;	// counter of objects
	int m_celestialBodyObjectID;			// unique number of object
	void updateVelocity();
public:
	CelestialBody(Centre cen, Body bod, Velocity vel, SDL_Color col);
	static int returnCount();
	int returnID() const;
	void render(Camera& cam, SDL_Renderer* renderer);
	const Centre& getCentrePosition() const;
	double& accessCentreX();
	double& accessCentreY();
	double& accessVelocityX();
	double& accessVelocityY();
	double& accessTextureRectX();
	double& accessTextureRectY();
	double getMass() const;
	double getRadius() const;
	void updatePosition(std::vector<CelestialBody*>& vec);
	void solveForces(std::vector<CelestialBody*>& vec);

	void simulateGravity(std::vector<CelestialBody*>& vec);
	const Velocity& getVelocity() const { return m_celestialBodyVelocity; };
};

class CelestialBodyInput
{
private:
	CelestialBody* newCircle;
public:
	CelestialBodyInput();
	~CelestialBodyInput();
	void set(Centre cen, Body bod, Velocity vel, SDL_Color col, std::vector<CelestialBody*>& vec);
	void updatePosition(std::vector<CelestialBody*>& vec);
};
#endif 