#ifndef TEXTURE_H
#define TEXTURE_H
#include "camera.h"
#include "screen.h"
#include <SDL.h>
#include <string>

class Texture
{
private:
	SDL_Texture* m_texture{nullptr}; //pointer to file
	g_struct_RectDouble m_textureRectDouble{}; //dimensions of texture
	SDL_Rect m_textureRectInt{};
	SDL_Color m_textureTextColor{};
	std::string m_textureStr{};
public:
	//path to file, x,y - coordinates of texture in world
	Texture() {};
	Texture(std::string path, double x, double y); 
	Texture(std::string path, int x, int y, SDL_Color textColor);
	~Texture();
	//load file and write width and height of file to textureRect
	void loadFromFile(std::string path);
	void loadFromRenderedText(std::string path);
	void setPosition(int x, int y);
	void setPosition(double x, double y);
	void setColor(Uint8 r, Uint8 g, Uint8 b);
	void free();
	//
	void render(Camera& cam, SDL_Renderer* renderer);
	void renderBackground(Camera& cam, SDL_Renderer* renderer);
	void renderText(SDL_Renderer* renderer);
};
#endif

