#include "Agent.h"
#include <chrono>

using namespace std;

Agent::Agent(Environment* _world){	
	srand( unsigned int( time(NULL) ) );
	running = false;
	
	steps = 0;
	posX = 0;
	posY = 0;
	world = _world;

	startPos = world->GetMapNode(0,0);
	endPos = world->GetMapNode(14,0);
	pathFinding = new PathFinding(world);

	auto start = std::chrono::steady_clock::now();

	pathFinding->FindPath(&movingPath, startPos, endPos);

	auto end = std::chrono::steady_clock::now();

	double elapsed = std::chrono::duration_cast<std::chrono::microseconds>
		(end - start).count();

	cout << "Tiden til A*(ms): " << elapsed;

	
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
		
		Move();
		world->draw(posX, posY);
		world->graphix->Draw(posX, posY, movingPath[movingPath.size()-1]->x(), movingPath[movingPath.size()-1]->y(), true);
		
		world->flip();		
		Sleep( 300 );
		
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

	holder->setValue(5);
	posX = positionNode->x();
	posY = positionNode->y();
	
}

