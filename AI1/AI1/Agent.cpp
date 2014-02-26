#include "Agent.h"
#include "Environment.h"
#include "Include.h"

using namespace std;

Agent::Agent(Environment* _world){	
	srand( time(NULL) );
	running = false;
	steps = 0;
	posX = 0;
	posY = 0;
	world = _world;
	positionNode = _world->SetStartNode();

	//Setting up internal map.
	std::deque<Node*> temp;
	//Y
	for (int y = 0; y < 3; y++){
		temp.push_back( new Node(3) );
	}
	//X
	for (int x = 0; x < 3; x++){
		internalMap.push_back(temp);
	}
	internalMap[1][1] = positionNode;
	internalMap[1][1]->visit();
	internalMap[0][1] = world->isMoveAble(posX-1, posY); //up
	internalMap[2][1] = world->isMoveAble(posX+1, posY); //down
	internalMap[1][0] = world->isMoveAble(posX, posY-1); //left
	internalMap[1][2] = world->isMoveAble(posX, posY+1); //right
	internOffsetX = 1;
	internOffsetY = 1;
}

Agent::~Agent(){

	for (int x = 0; x < internalMap.size(); x++) {
		for (int y = 0; y < internalMap[0].size(); y++) {
			delete internalMap[x][y];
			internalMap[x][y] = nullptr;
		}
	}
	delete positionNode;
	positionNode = nullptr;
}

void Agent::Draw(int x, int y){
	std::cout << "\nInternal Map:\n";
	for(unsigned int i = 0; i < internalMap.size(); i++){
		for (unsigned int j = 0; j < internalMap[i].size(); j++){

			if (i == x+internOffsetX && j == y+internOffsetY){
				std::cout << "A";
			} else {
				if (internalMap[i][j]->getValue() == 0){cout << " ";}
				if (internalMap[i][j]->getValue() == 1){cout << "~";}
				if (internalMap[i][j]->getValue() == 2){cout << "#";}
				if (internalMap[i][j]->getValue() == 3){cout << "x";}
			}
		}
		cout << endl;
	}
}

int Agent::Run(){
	running = true;
	
	//running until environment is clean
	while (running) {
		system("CLS");
		world->draw(posX, posY);
		Recon();
		Draw(posX, posY);
		Vacuum();
		Move();
		
		//will end if taking more than 1k steps.
		steps++;
		if(steps > runtime) {
			running = false;
			return 1;
		}
	}
	return 0;
};

void Agent::Vacuum() {

	if ( positionNode->getValue() == 0 ) {
		cout << "Node is clean" << endl;
	} else {
		std::cout<< "I am vacuuming here now, soon clean...";
		Sleep(sleep);
		std::cout<< " Clean!"<< endl;
		positionNode->setValue(0);
		world->AddCleanedNode();
	}
}

void Agent::Move() {
	if( world->isMoveAble(posX+1, posY)->getValue() == 2 && world->isMoveAble(posX-1, posY)->getValue() == 2 &&
		world->isMoveAble(posX, posY+1)->getValue() == 2 && world->isMoveAble(posX, posY-1)->getValue() == 2 ){
			running = false;
			cout << "Trapped bot is sad bot" << endl;
			cin.get();
	} else {
		if(internalMap[posX+internOffsetX+1][posY+internOffsetY]->getValue() == 1){ posX++; }
		else if(internalMap[posX+internOffsetX-1][posY+internOffsetY]->getValue() == 1){ posX--; }
		else if(internalMap[posX+internOffsetX][posY+internOffsetY+1]->getValue() == 1){ posY++; }
		else if(internalMap[posX+internOffsetX][posY+internOffsetY-1]->getValue() == 1){ posY--; }

		//else if ( AStar() ){}
		else{
			//Find shortest distance to unvisted node.
			float dist = 10000;
			int tempX;
			int tempY;
			for (unsigned int x = 0; x < internalMap.size(); x++){
				for (unsigned int y = 0; y < internalMap[0].size(); y++){

					if((internalMap[x][y]->getValue() == 0 || internalMap[x][y]->getValue() == 1) && !internalMap[x][y]->getVisit()){
						
						float temp = std::abs( std::sqrt( std::abs( int(posX+internOffsetX-x) ) * std::abs( int(posY+internOffsetY-y) ) ) );
						if (temp <= dist){
							dist = temp;
							tempX = x; tempY = y;
						}
					}

				}
			}
			//Found a target
			if(dist != 10000){				
				cout << "pos: " << posX+internOffsetX << " " << posY+internOffsetY << endl;
				cout << "Target: " << tempX << " " << tempY << endl;

				if (posX+internOffsetX-tempX > 0 && world->isMoveAble(posX-1, posY)->getValue() != 2){ posX--; }
				else if(posX+internOffsetX-tempX < 0 && world->isMoveAble(posX+1, posY)->getValue() != 2){ posX++; }
				else if (posY+internOffsetY-tempY > 0 && world->isMoveAble(posX, posY-1)->getValue() != 2){ posY--; }
				else if(posY+internOffsetY-tempY < 0 && world->isMoveAble(posX, posY+1)->getValue() != 2){ posY++; }
				
				//force move
				else {
					bool move = false;
					while(move == false){
						int x = rand() % 4;
						switch (x){
							case 0: if(world->isMoveAble(posX, posY-1)->getValue() != 2){ posY--; move = true;} break;
							case 1: if(world->isMoveAble(posX, posY+1)->getValue() != 2){ posY++; move = true;} break;
							case 2: if(world->isMoveAble(posX-1, posY)->getValue() != 2){ posX--; move = true;} break;
							case 3: if(world->isMoveAble(posX+1, posY)->getValue() != 2){ posX++; move = true;} break;
						}
					}
				}
				
			}
			//no possible targets, unvisit all.
			else {
			
				for (unsigned int x = 0; x < internalMap.size(); x++){
					for (unsigned int y = 0; y < internalMap[0].size(); y++){
						internalMap[x][y]->visit(false);
					}
				}
				
				if(world->isMoveAble(posX, posY-1)->getValue() != 2){ posY--; }		
				else if(world->isMoveAble(posX+1, posY)->getValue() != 2){ posX++; }
				else if(world->isMoveAble(posX, posY+1)->getValue() != 2){ posY++; }
				else if (world->isMoveAble(posX-1, posY)->getValue() != 2){ posX--; }
			}
		}


	}
	positionNode = world->isMoveAble(posX, posY);
	cout<< "Moved to x: "<<posX<< " y: "<< posY<<endl;
	Sleep(sleep);
}

void Agent::Recon(){	
	//Add to left of internal map.
	if(posY + internOffsetY-1 < 0){
		internOffsetY++;
		for(unsigned int x = 0; x < internalMap.size(); x++){
			internalMap[x].push_front( new Node(3) );
		}
	}

	//Add to right of internal map.
	if(posY + internOffsetY+1 >= internalMap[0].size() ){
		for(unsigned int x = 0; x < internalMap.size(); x++){
			internalMap[x].push_back( new Node(3) );
		}
	}

	//add to top of internal map.
	if(posX + internOffsetX-1 < 0 ){
		internOffsetX++;
		std::deque<Node*> temp;			
		for (unsigned int y = 0; y < internalMap[0].size(); y++){
			temp.push_back( new Node(3) );
		}
		internalMap.push_front( temp );
	}

	//add to bottom of internal map.
	if(posX + internOffsetX+1 >= internalMap.size() ){
		std::deque<Node*> temp;
		for (unsigned int y = 0; y < internalMap[0].size(); y++){
			temp.push_back( new Node(3) );
		}
		internalMap.push_back( temp );
	}

	internalMap[posX + internOffsetX-1][posY + internOffsetY]->setValue(world->isMoveAble(posX-1, posY)->getValue()); //up
	internalMap[posX + internOffsetX+1][posY + internOffsetY]->setValue(world->isMoveAble(posX+1, posY)->getValue()); //down
	internalMap[posX + internOffsetX][posY + internOffsetY-1]->setValue(world->isMoveAble(posX, posY-1)->getValue()); //left
	internalMap[posX + internOffsetX][posY + internOffsetY+1]->setValue(world->isMoveAble(posX, posY+1)->getValue()); //right

	//visit nodes.
	internalMap[posX+internOffsetX][posY+internOffsetY]->visit();
	if (internalMap[posX + internOffsetX-1][posY + internOffsetY]->getValue() == 2){ internalMap[posX + internOffsetX-1][posY + internOffsetY]->visit(); }
	if (internalMap[posX + internOffsetX+1][posY + internOffsetY]->getValue() == 2){ internalMap[posX + internOffsetX+1][posY + internOffsetY]->visit(); }
	if (internalMap[posX + internOffsetX][posY + internOffsetY+1]->getValue() == 2){ internalMap[posX + internOffsetX][posY + internOffsetY-1]->visit(); }
	if (internalMap[posX + internOffsetX][posY + internOffsetY-1]->getValue() == 2){ internalMap[posX + internOffsetX][posY + internOffsetY+1]->visit(); }

}

