#include "Agent.h"

using namespace std;

Agent::Agent(Environment* _world){	
	srand( unsigned int( time(NULL) ) );
	running = false;
	
	steps = 0;
	posX = 0;
	posY = 0;
	world = _world;
	startPos = world->GetMapNode(9,4);
	endPos = world->GetMapNode(3, 9);
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
		Sleep( 500 );
		
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
	
	unsigned int index = 1;
	Node* holder = positionNode;
	positionNode = movingPath[movingPath.size() - index];

	if(index < movingPath.size()) {

		movingPath.erase(movingPath.end() - index);
	}
	holder->setValue(0);
	positionNode->setValue(3);
}

