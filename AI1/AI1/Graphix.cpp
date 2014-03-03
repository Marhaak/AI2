
#include "Graphix.h"
#include "Environment.h"
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

void Graphix::Draw(int _x1, int _y1, int _x2, int _y2, bool colour){

	//invert x/y because SDL
	int y1 = _x1*32;
	int x1 = _y1*32;
	int y2 = _x2*32;
	int x2 = _y2*32;

	//set colour
	SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);

	if(colour){
		SDL_SetRenderDrawColor(renderer, 50, 250, 50, 255);
	}
	
	//makeshift line thickness
	for (int i = 15; i < 18; i++){
		for (int j = 15; j < 18; j++){
			SDL_RenderDrawLine( renderer, x1+i, y1+j, x2+i, y2+j);
		}
	}
}
	
bool Graphix::InitSDL() {
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
		cout << SDL_GetError() << endl;
		return false;
	}

	// Creating the window
	window = SDL_CreateWindow("A star", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, winXSize, winYSize, NULL);
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
	textureSheet[4] = loadImage("node.png");
	textureSheet[5] = loadImage("nodevisit.png");

	// Everything went ok
	return true;
}

Graphix::~Graphix() {

	// "Turn off" SDL
	for(int i = 0; i < sizeof(textureSheet); i++) {

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