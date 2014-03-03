#pragma once

#include "Include.h"
#include "Node.h"
#include "Graphix.h"

class Environment {
private:
	// Variables
	int xSize;
	int ySize;
	int botX;
	int botY;
	int numOfStepsUsed;		// Will hold the number of steps the agent used
	std::vector< std::vector<Node*> > map; // The map that the agents lives in
	
	
	SDL_Renderer* renderer;
	SDL_Event eventHander;
	
	// Functions

public:
	// Variables
	Graphix* graphix;

	// Functions
	Environment(std::string _file);
	~Environment();
	void draw(int _x, int _y);		// Draws the map
	Node* SetStartNode();			// Returns a startnode that the agent will start on
	void GetScore();
	Node* GetMapNode(int _x, int _y);
	void flip();
};