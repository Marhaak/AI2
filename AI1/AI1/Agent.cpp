#include "Agent.h"
#include <chrono>

using namespace std;

Agent::Agent(Environment* _world){	
	srand( unsigned int( time(NULL) ) );
	running = false;
	
	posX = 0;	// Agents X value
	posY = 0;	// and Y value.
	world = _world;	// Gives the world to the agent.

	startPos = world->GetMapNode(posX, posY);	// Start node.
	endPos = world->GetMapNode(14, 0);			// Goal node.

	pathFinding = new PathFinding(world);		// Gives the world to pathFinding.

	auto start = std::chrono::steady_clock::now();	// Starts the clock.

	pathFinding->FindPath(&movingPath, startPos, endPos);	// Calculates the path.

	auto end = std::chrono::steady_clock::now();	// Stops the clock.
	double elapsed = std::chrono::duration_cast<std::chrono::microseconds>	// Calculates the difference
		(end - start).count();												// and shows it in microseconds.

	cout << "Tiden til A*(ms): " << elapsed;	// Shows you how long A* took to find the path.
	positionNode = startPos;	// Set the agent at the start goal.
}

// Clean up.
Agent::~Agent(){
	delete pathFinding;
	pathFinding = nullptr;
}

int Agent::Run(){
	running = true;

	//running until environment is clean
	while (running) {
		
		//draw the map
		world->draw(posX, posY);

		//draw the selected paths in green.
		world->graphix->Draw(posX, posY, movingPath[movingPath.size()-1]->x(), movingPath[movingPath.size()-1]->y(), true);
		for(int x = 0; x < movingPath.size()-1; x++){
			world->graphix->Draw(movingPath[x]->x(), movingPath[x]->y(), movingPath[x+1]->x(), movingPath[x+1]->y(), true);
		}

		//move, show graphics and delay
		Move();	// Move to the next node 
		world->flip();	// Swaps the images
		Sleep( sleep );	// Delay before looping
		if(!movingPath.size()) { // true if we've reached the goal.
			running = false;
			return 1;
		}
	}
	return 0;
}

void Agent::Move() {
	unsigned int index = 1;
	Node* holder = positionNode;
	positionNode = movingPath[movingPath.size() - index];

	// Keeps track of the remaining path.
	if(index < movingPath.size()) {
		movingPath.erase(movingPath.end() - index);
	}

	holder->setValue(5);		// Set the node to visited.
	posX = positionNode->x();	// Update the agents values.
	posY = positionNode->y();	
}