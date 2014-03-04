#pragma once

#include "Include.h"
#include "Node.h"
#include "Graphix.h"

class Environment {
private:
	// Variables
	int xSize;	// Size of the
	int ySize;	// map.
	int botX;	// Position of the
	int botY;	// bot.
	std::vector< std::vector<Node*> > map; // The map that the agents lives in.
	
	
	SDL_Renderer* renderer;
	SDL_Event eventHander;
	
	// Functions

public:
	// Variables
	Graphix* graphix;

	// Functions
	Environment(std::string _file);	// Read in the setup of the map.
	~Environment();					// Clean up.
	void draw(int _x, int _y);		// Draws the map.
	Node* GetMapNode(int _x, int _y);	// Returns the specified node.
	void flip();					// Swaps images.
};