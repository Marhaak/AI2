#pragma once

#include "Include.h"
#include "Environment.h"

class Agent{

private:

	// Variables
	bool running;
	bool beenHere; // false if not been there, true if it has
	int steps;

	int posX;
	int posY;
	int internOffsetX;
	int internOffsetY;

	Node* positionNode;
	Environment* world;
	
	std::deque< std::deque< Node* > > internalMap;
	std::vector<Node> movingPath;

	// Functions
	void Vacuum();	// This function will vacuum if there is dirty
	void Move();	// This function will move the agent to a new place
	void Draw(int x, int y);
	void Recon();


public:
	// Variables

	// Functions
	Agent(Environment* _world);
	~Agent();
	int Run();	// The main loop of the agent
};
