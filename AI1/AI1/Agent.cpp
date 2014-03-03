#include "Agent.h"
#include <chrono>

using namespace std;

Agent::Agent(Environment* _world){	
	srand( unsigned int( time(NULL) ) );
	running = false;
	
	steps = 0;
	posX = 14;
	posY = 0;
	world = _world;

	startPos = world->GetMapNode(posX, posY);
	endPos = world->GetMapNode(6, 14);

	pathFinding = new PathFinding(world /*,false*/);

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
		Move();
		world->flip();		
		Sleep( 300 );
		steps++;
		if(!movingPath.size()) {
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

