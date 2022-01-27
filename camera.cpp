#include "debug.h"

#include "camera.h"
#include <iostream>
#include <SDL.h>

Camera::Camera(double x, double y, double w, double h): m_cameraScreen{ w,h }
{
	m_cameraCameraRectDouble = { x,y,w,h };
}
// main function return false if intersection of camera and object was not found
bool Camera::inputObjectRectDouble(const g_struct_RectDouble& objRect) 
{ 
	m_cameraObjectRectDouble = objRect;
	if (!canRender())
	{
		return false;
	}
	else
	{
		createBools();
		xwFunction();
		m_cameraTextureSDL_Rect.x = static_cast<int>(round(m_cameraTextureRectDouble.x));
		m_cameraTextureSDL_Rect.y = static_cast<int>(round(m_cameraTextureRectDouble.y));
		m_cameraTextureSDL_Rect.w = static_cast<int>(round(m_cameraTextureRectDouble.w));
		m_cameraTextureSDL_Rect.h = static_cast<int>(round(m_cameraTextureRectDouble.h));

		m_cameraTargetSDL_Rect.x = static_cast<int>(round(m_cameraTargetRectDouble.x));
		m_cameraTargetSDL_Rect.y = static_cast<int>(round(m_cameraTargetRectDouble.y));
		m_cameraTargetSDL_Rect.w = static_cast<int>(round(m_cameraTargetRectDouble.w));
		m_cameraTargetSDL_Rect.h = static_cast<int>(round(m_cameraTargetRectDouble.h));
		return true;
	}
}
bool Camera::canRender()
{
	//!C
	if (!(m_cameraCameraRectDouble.x + m_cameraCameraRectDouble.w >= m_cameraObjectRectDouble.x))
	{
		return false;
	}
	//A1
	if (m_cameraCameraRectDouble.x >= m_cameraObjectRectDouble.x + m_cameraObjectRectDouble.w)
	{
		return false;
	}
	//!D
	if (!(m_cameraCameraRectDouble.y + m_cameraCameraRectDouble.h >= m_cameraObjectRectDouble.y))
	{
		return false;
	}
	//B1
	if (m_cameraCameraRectDouble.y >= m_cameraObjectRectDouble.y + m_cameraObjectRectDouble.h)
	{
		return false;
	}
	return true;
}
void Camera::createBools()
{
	//A
	if (m_cameraCameraRectDouble.x >= m_cameraObjectRectDouble.x) b_cameraA = true;
	else b_cameraA = false;
	//C1
	if (m_cameraCameraRectDouble.x + m_cameraCameraRectDouble.w >= m_cameraObjectRectDouble.x + m_cameraObjectRectDouble.w)	b_cameraC1 = true;
	else b_cameraC1 = false;
	//B
	if (m_cameraCameraRectDouble.y >= m_cameraObjectRectDouble.y) b_cameraB = true;
	else b_cameraB = false;
	//D1
	if (m_cameraCameraRectDouble.y + m_cameraCameraRectDouble.h >= m_cameraObjectRectDouble.y + m_cameraObjectRectDouble.h) b_cameraD1 = true;
	else b_cameraD1 = false;
}
void Camera::xwFunction()
{
	if (b_cameraA)
	{
		m_cameraTextureRectDouble.x = m_cameraCameraRectDouble.x - m_cameraObjectRectDouble.x;	// checked
		m_cameraTargetRectDouble.x = 0.0;								// checked
		if (!b_cameraC1)
		{
			m_cameraTextureRectDouble.w = m_cameraCameraRectDouble.w;				// ckecked
			m_cameraTargetRectDouble.w = m_cameraScreen.w;					// modified targetRect.w = cameraRect.w
			yhFunction();
		}
		else
		{
			m_cameraTextureRectDouble.w = m_cameraObjectRectDouble.x + m_cameraObjectRectDouble.w - m_cameraCameraRectDouble.x;	// checked
			m_cameraTargetRectDouble.w = (m_cameraObjectRectDouble.x + m_cameraObjectRectDouble.w - m_cameraCameraRectDouble.x) * m_cameraZoom;	// modified targetRect.w = objectRect.x + objectRect.w - cameraRect.x;
			yhFunction();
		}
	}
	else
	{
		m_cameraTextureRectDouble.x = 0.0;							// checked
		m_cameraTargetRectDouble.x = (m_cameraObjectRectDouble.x - m_cameraCameraRectDouble.x) * m_cameraZoom;	// modified targetRect.x = objectRect.x - cameraRect.x;
		if (!b_cameraC1)
		{		
			m_cameraTextureRectDouble.w = m_cameraCameraRectDouble.x + m_cameraCameraRectDouble.w - m_cameraObjectRectDouble.x;	// checked
			m_cameraTargetRectDouble.w = (m_cameraCameraRectDouble.x + m_cameraCameraRectDouble.w - m_cameraObjectRectDouble.x) * m_cameraZoom;	// modified targetRect.w = cameraRect.x + cameraRect.w - objectRect.x;
			yhFunction(); 
		}
		else
		{
			m_cameraTextureRectDouble.w = m_cameraObjectRectDouble.w;	// checked
			m_cameraTargetRectDouble.w = m_cameraObjectRectDouble.w * m_cameraZoom;	// targetRect.w = objectRect.w;
			yhFunction();
		}
	}
}
void Camera::yhFunction()
{
	if (b_cameraB)
	{
		m_cameraTextureRectDouble.y = m_cameraCameraRectDouble.y - m_cameraObjectRectDouble.y;
		m_cameraTargetRectDouble.y = 0;
		if (!b_cameraD1)
		{
			m_cameraTextureRectDouble.h = m_cameraCameraRectDouble.h;
			m_cameraTargetRectDouble.h = m_cameraScreen.h;	// targetRect.h = cameraRect.h;
		}
		else
		{
			m_cameraTextureRectDouble.h = m_cameraObjectRectDouble.y + m_cameraObjectRectDouble.h - m_cameraCameraRectDouble.y;
			m_cameraTargetRectDouble.h = static_cast<int>(round(static_cast<double>(m_cameraObjectRectDouble.y + m_cameraObjectRectDouble.h - m_cameraCameraRectDouble.y) * m_cameraZoom));	// targetRect.h = objectRect.y + objectRect.h - cameraRect.y;
		}
	}
	else
	{
		m_cameraTextureRectDouble.y = 0;
		m_cameraTargetRectDouble.y = static_cast<int>(round(static_cast<double>(m_cameraObjectRectDouble.y - m_cameraCameraRectDouble.y) * m_cameraZoom));	// targetRect.y = objectRect.y - cameraRect.y
		if (!b_cameraD1)
		{
			m_cameraTextureRectDouble.h = m_cameraCameraRectDouble.y + m_cameraCameraRectDouble.h - m_cameraObjectRectDouble.y;
			m_cameraTargetRectDouble.h = static_cast<int>(round(static_cast<double>(m_cameraCameraRectDouble.y + m_cameraCameraRectDouble.h - m_cameraObjectRectDouble.y) * m_cameraZoom));	// targetRect.h = cameraRect.y + cameraRect.h - objectRect.y;
		}
		else
		{
			m_cameraTextureRectDouble.h = m_cameraObjectRectDouble.h;
			m_cameraTargetRectDouble.h = static_cast<int>(round(static_cast<double>(m_cameraObjectRectDouble.h) * m_cameraZoom));	// targetRect.h = objectRect.h;
		}
	}
}
const SDL_Rect& Camera::getTextureSDL_Rect() const 
{
	return m_cameraTextureSDL_Rect;
}
const SDL_Rect& Camera::getTargetSDL_Rect() const 
{ 
	return m_cameraTargetSDL_Rect;
}
const g_struct_RectDouble& Camera::getCameraRectDouble() const { return m_cameraCameraRectDouble; } // rework to double
void Camera::cameraMovementDouble(double x, double y)
{
	m_cameraCameraRectDouble.x += x;
	m_cameraCameraRectDouble.y += y;
}
void Camera::setCameraPositionDouble(double x, double y)
{
	m_cameraCameraRectDouble.x = x;
	m_cameraCameraRectDouble.y = y;
}
double Camera::getCameraPositionX() const { return m_cameraCameraRectDouble.x; }
double Camera::getCameraPositionY() const { return m_cameraCameraRectDouble.y; }
void Camera::cameraZoomIn()
{ 
	m_cameraZoom *= 2.0;
	m_cameraCameraRectDouble.w = m_cameraScreen.w / m_cameraZoom;
	m_cameraCameraRectDouble.h = m_cameraScreen.h / m_cameraZoom;
	m_cameraCameraRectDouble.x += m_cameraCameraRectDouble.w / 2.0;
	m_cameraCameraRectDouble.y += m_cameraCameraRectDouble.h / 2.0;
}
void Camera::cameraZoomOut() 
{ 
	if (m_cameraZoom <= 1.0/pow(2.0,4.0)) m_cameraZoom = 1.0 / pow(2.0, 4.0);
	else
	{
		m_cameraZoom /= 2.0;
		m_cameraCameraRectDouble.x -= m_cameraCameraRectDouble.w / 2.0;
		m_cameraCameraRectDouble.y -= m_cameraCameraRectDouble.h / 2.0;
		m_cameraCameraRectDouble.w = m_cameraScreen.w / m_cameraZoom;
		m_cameraCameraRectDouble.h = m_cameraScreen.h / m_cameraZoom;
	}
}
double Camera::getCameraZoom() const { return m_cameraZoom; }
