#include "debug.h"

#include "camera.h"
#include "screen.h"
#include "texture.h"
#include <cmath>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <iostream>

Texture::Texture(std::string path, double x, double y)
{
	loadFromFile(path);
	m_textureRectDouble.x = x;
	m_textureRectDouble.y = y;
	m_textureRectInt.x = static_cast<int>(round(x));
	m_textureRectInt.y = static_cast<int>(round(y));
}
Texture::Texture(std::string path, int x, int y, SDL_Color textColor)
{
	this->m_textureTextColor = textColor;
	m_textureStr = path;
	loadFromRenderedText(m_textureStr);
	m_textureRectInt.x = x;
	m_textureRectInt.y = y;
	m_textureRectDouble.x = static_cast<double>(x);
	m_textureRectDouble.y = static_cast<double>(y);
}
Texture::~Texture()
{
	free();
}
void Texture::loadFromFile(std::string path)
{
	free();
	startSDL();
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		m_texture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (m_texture == nullptr)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			m_textureRectInt.w = loadedSurface->w;
			m_textureRectInt.h = loadedSurface->h;
			m_textureRectDouble.h = static_cast<double>(loadedSurface->h);
			m_textureRectDouble.w = static_cast<double>(loadedSurface->w);
		}
		SDL_FreeSurface(loadedSurface);
		loadedSurface = nullptr;
	}
}
void Texture::loadFromRenderedText(std::string path)
{
	free();
	startSDL();
	m_textureStr = path;
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, m_textureStr.c_str(), m_textureTextColor);
	if (textSurface == nullptr)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		m_texture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (m_texture == nullptr)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			m_textureRectInt.w = textSurface->w;
			m_textureRectInt.h = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}
}
void Texture::setPosition(int x, int y)
{
	m_textureRectInt.x = x;
	m_textureRectInt.y = y;
	m_textureRectDouble.x = static_cast<double>(x);
	m_textureRectDouble.y = static_cast<double>(y);
}
void Texture::setPosition(double x, double y)
{
	m_textureRectDouble.x = x;
	m_textureRectDouble.y = y;
	m_textureRectInt.x = static_cast<int>(round(x));
	m_textureRectInt.y = static_cast<int>(round(y));
}
void Texture::setColor(Uint8 r, Uint8 g, Uint8 b)
{
	m_textureTextColor.r = r;
	m_textureTextColor.g = g;
	m_textureTextColor.b = b;
	loadFromRenderedText(m_textureStr);
}
void Texture::free()
{
	if (m_texture != nullptr)
	{
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;
	}
}
void Texture::render(Camera& cam, SDL_Renderer* renderer)
{
	if (m_texture != nullptr && cam.inputObjectRectDouble(m_textureRectDouble))
	{
		SDL_RenderCopy(renderer, m_texture, &cam.getTextureSDL_Rect(), &cam.getTargetSDL_Rect());
	}
	else
	{
		std::cout << "cant render texture\n";
	}
}
void Texture::renderBackground(Camera& cam, SDL_Renderer* renderer)
{
	//int pocet_na_x_osi{ gScreenWidth / rectInt.w };
	//int zostatok_na_x_osi{ gScreenWidth - pocet_na_x_osi * rectInt.w };
	if (m_texture != nullptr)
	{
		int x{ -(static_cast<int>(round(cam.getCameraPositionX() * cam.getCameraZoom())) % m_textureRectInt.w) - m_textureRectInt.w };
		int y{ -(static_cast<int>(round(cam.getCameraPositionY() * cam.getCameraZoom())) % m_textureRectInt.h) - m_textureRectInt.h };
		SDL_Rect rect{ x,y,m_textureRectInt.w,m_textureRectInt.h };

		while (rect.y < gScreenHeight)
		{
			while (rect.x < gScreenWidth)
			{
				SDL_RenderCopy(renderer, m_texture, NULL, &rect);
				rect.x += m_textureRectInt.w;
			}
			rect.x = x;
			rect.y += m_textureRectInt.h;
		}
	}
	else
	{
		std::cout << "cant render texture\n";
	}
}
void Texture::renderText(SDL_Renderer* renderer)
{
	if (m_texture != nullptr)
	{
		SDL_RenderCopy(renderer, m_texture, NULL, &m_textureRectInt);
	}
	else
	{
		std::cout << "cant render texture\n";
	}
}