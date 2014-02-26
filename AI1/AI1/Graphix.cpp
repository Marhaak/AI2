#include "Graphix.h"
using namespace std;

Graphix::Graphix(int _x, int _y) {
	winXSize = _x;
	winYSize = _y;
	InitSDL();
}

void Graphix::Draw(int _x, int _y, int _i) {

	// Draws to back buffer
	ApplySurface(_x, _y, textureSheet[_i], renderer);
}
	
bool Graphix::InitSDL() {

	if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
		cout << SDL_GetError() << endl;
		return false;
	}

	// Creating the window
	window = SDL_CreateWindow("Vacuum", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, winXSize, winYSize, NULL);
    if (window == nullptr){
        cout << SDL_GetError() << "\n";
		return false;
    }

	// Creating the renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr){
        cout << SDL_GetError() << endl;
		return false;
    }

	textureSheet[0] = loadImage("ground.png");
	textureSheet[1] = loadImage("dirt.png");
	textureSheet[2] = loadImage("wall.png");
	textureSheet[3] = loadImage("vacuum.png");
	// Everything went ok
	return true;
}

Graphix::~Graphix() {

	// "Turn off" SDL
	for(int i = 0; i < 4; i++) {

		SDL_DestroyTexture(textureSheet[i]);
	}
	
	SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

// Setting the textue on the screen
void Graphix::ApplySurface(int x, int y, SDL_Texture *tex, SDL_Renderer *rend) {
	SDL_Rect pos;
    pos.x = x;
    pos.y = y;
	SDL_QueryTexture(tex, NULL, NULL, &pos.w, &pos.h); 
    SDL_RenderCopy(rend, tex, NULL, &pos);
}

// Loading a image to a texture
SDL_Texture* Graphix::loadImage(string _file) {
	SDL_Texture* tex = nullptr;
	tex = IMG_LoadTexture(renderer, _file.c_str());
    if (tex == nullptr) {
		cout<<"Failed to load image: "<< _file.c_str()<<" "<<  IMG_GetError();
		cin.get();
	}
	
    return tex;
}

SDL_Renderer* Graphix::Renderer() {
	return renderer;
}

// Checking for an quit event
void Graphix::Event(SDL_Event _event) {

	while (SDL_PollEvent(&_event)) {
			
		if (_event.type == SDL_QUIT){

			exit(0);
		}
	}
}