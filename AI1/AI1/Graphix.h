#pragma once

#include "Include.h"

class Graphix {

private:
	SDL_Texture* textureSheet[4];		// Array with the textures
	SDL_Window*   window;				// The window
	SDL_Renderer* renderer;				// The renderer
	
	int winXSize;
	int winYSize;
public:
	Graphix(int _x, int _y);
	~Graphix();
	void Draw(int _x, int _y, int _i);
	bool InitSDL();
	SDL_Texture* loadImage(std::string _file);
	void ApplySurface(int _x, int _y, SDL_Texture* _tex, SDL_Renderer* _rend);
	SDL_Renderer* Renderer();
	void Event(SDL_Event _event);
};

