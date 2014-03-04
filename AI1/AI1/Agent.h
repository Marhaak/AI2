#pragma once

#include "Include.h"
#include "Environment.h"
#include "PathFinding.h"

class Agent{

private:

	// Variables
	bool running; // Determines if the agent should run or not.
	bool beenHere; // false if not been there, true if it has.

	int posX;	// Agents X 
	int posY;	// and Y value.

	Node* positionNode;
	Environment* world;
	PathFinding* pathFinding;
	std::vector<Node*> movingPath;
	Node* startPos;	// Start goal
	Node* endPos;	// End goal

	// Functions
	void Move();	// This function will move the agent to a new place

public:
	// Variables

	// Functions
	Agent(Environment* _world);	// Init the agent and gives the agent the "world".
	~Agent();	// Clean up.
	int Run();	// The main loop of the agent
};