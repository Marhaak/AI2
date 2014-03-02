#pragma once

#include "Include.h"
#include "Environment.h"
#include "PathFinding.h"

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
	PathFinding* pathFinding;
	std::vector<Node*> movingPath;
	Node* startPos;
	Node* endPos;

	// Functions
	void Move();	// This function will move the agent to a new place

public:
	// Variables

	// Functions
	Agent(Environment* _world);
	~Agent();
	int Run();	// The main loop of the agent
};
