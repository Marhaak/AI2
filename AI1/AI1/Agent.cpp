#include "Agent.h"

using namespace std;

Agent::Agent(Environment* _world){	
	srand( time(NULL) );
	running = false;
	
	steps = 0;
	posX = 0;
	posY = 0;
	world = _world;
	startPos = world->GetMapNode(0,0);
	endPos = world->GetMapNode(14,9);
	pathFinding = new PathFinding(world);
	pathFinding->FindPath(&movingPath, startPos, endPos);
	positionNode = startPos;
}

Agent::~Agent(){

	delete pathFinding;
	pathFinding = nullptr;
}

int Agent::Run(){
	running = true;
	int numOfSteps = movingPath.size();
	//running until environment is clean
	while (running) {
		world->draw(posX, posY);
		Move();
		
		//will end if taking more than 1k steps.
		steps++;
		if(steps > numOfSteps) {
			running = false;
			return 1;
		}
	}
	return 0;
};

void Agent::Move() {
	
	int index = 1;
	positionNode = movingPath[movingPath.size() - index];

	if(index < movingPath.size()) {

		movingPath.erase(movingPath.size - index);
	}
}

