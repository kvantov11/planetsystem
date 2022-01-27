// "camera.h" evaulates intersection of object and camera and calculate position and dimension of rendered part of object on screen
// camera and object are instance in world with coordinates x and y and dimension w and h
// input parameters are SDL rectangle of object and camera position + dimension
// "camera." returns SDL rectangles targerRect - destination and textureRect - source which can be used in SDL_RenderCopy()
// #define SWITCH swaps 4 nested if-else for 1 switch
#ifndef CAMERA_H
#define CAMERA_H
#include <SDL.h>

//defined in  camera.h
struct g_struct_RectDouble
{
	double x;
	double y;
	double w;
	double h;
};

class Camera
{
private:
	g_struct_RectDouble m_cameraCameraRectDouble{};	//camera position and dimension in world
	g_struct_RectDouble m_cameraObjectRectDouble{};	//object position and dimension in world
	g_struct_RectDouble m_cameraTextureRectDouble{};		//part of object
	g_struct_RectDouble m_cameraTargetRectDouble{};		//part of window
	SDL_Rect m_cameraTextureSDL_Rect{};
	SDL_Rect m_cameraTargetSDL_Rect{};
	
	struct m_struct_Screen
	{
		double w;
		double h;
	};
	const m_struct_Screen m_cameraScreen;

	bool b_cameraA{};		//left edge
	bool b_cameraB{};		//top edge
	bool b_cameraC1{};	//right edge
	bool b_cameraD1{};	//bottom edge
	double m_cameraZoom{1.0};

	bool canRender();
	//intialize bools A B C1 D1
	void createBools();
	//calculate x and w of output rectangles
	void xwFunction();
	//calculate y and h of output rectangles
	void yhFunction();
	//return rectangle for object - source
public:
	//camera position and dimension in world
	Camera(double x, double y, double w, double h);
	//input paramater is rectangle of object
	//return false if object is outside of the camera
	//function update output rectangles in the class
	bool inputObjectRectDouble(const g_struct_RectDouble& objRect);
	//return false if object is outside of the camera
	
	const SDL_Rect& getTextureSDL_Rect() const;
	//return rectangle for camera - destination
	const SDL_Rect& getTargetSDL_Rect() const;
	//return rectangle of camera position and dimension in world
	const g_struct_RectDouble& getCameraRectDouble() const;
	//change position of camera in world
	void cameraMovementDouble(double x,double y);
	//5.12.2021 new addon to set camera position
	void setCameraPositionDouble(double x, double y);	// change input to double and calculate int for cameraRect
	double getCameraPositionX() const;
	double getCameraPositionY() const;
	void cameraZoomIn();
	void cameraZoomOut();
	double getCameraZoom() const;
};
#endif

