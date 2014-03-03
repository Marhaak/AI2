#include "Node.h"
#include "Include.h"
#include "Environment.h"

using namespace std;

Environment::Environment(std::string _file){

	botX = 0;
	botY = 0;

	ifstream file(_file);
	file >> xSize >> ySize;

	graphix = new Graphix(xSize*32, ySize*32);
	renderer = graphix->Renderer();
	
	int id = 0;
	//read the map
	for (int i = 0; i< xSize; i++){

		std::vector<Node*> temp;
		map.push_back( temp );
		for (int j = 0; j < ySize; j++){

			int trash;
			file >> trash;
			map[i].push_back( new Node(trash) );
			map[i][j]->x(i); map[i][j]->y(j); map[i][j]->id(id++);
		}
	}

	//read nodes
	while( !file.eof() ){
		int x; int y;
		file >> x >> y;
		map[x][y]->readFile(file);
	}
}

Environment::~Environment(){	

	delete graphix;
	graphix = nullptr;
}

//draws the environment
void Environment::draw(int _x, int _y){

	// Check for events
	graphix->Event(eventHander);
	
	// Clear the screen
	SDL_RenderClear(renderer);

	//Drawing the nodes
	for (int i = 0; i < xSize; i++){
		for (int j = 0; j < ySize; j++){

			if(j == _x+botX && i == _y+botY){ graphix->Draw(i * 32, j * 32,3);}
			else{
				graphix->Draw(i * 32, j * 32, map[j][i]->getValue());
			}
		}
	}

	//drawing the lines
	for (int i = 0; i < xSize; i++){
		for (int j = 0; j < ySize; j++){
			
			for(unsigned int z = 0; z < map[i][j]->links.size(); z++){
				graphix->Draw(i, j, map[i][j]->links[z][0], map[i][j]->links[z][1]);
			}
		}		
	}
}

void Environment::flip(){
	// Swap buffers
	SDL_RenderPresent(renderer);
}

Node* Environment::SetStartNode() {
	Node* startNode = new Node(2);
	
	//set random start node that is not a wall.
	while(startNode->getValue() == 2 || startNode->getValue() == 1 ) {
		botX = rand() % xSize;
		botY = rand() % ySize;
		startNode = map[botX][botY];
	}
	return startNode;
}

void Environment::GetScore() {
	int numOfDirtsLeft = 0;

	// Going thru and finding all the dirts that are left
	for (int i = 0; i < xSize; i++){
		for (int j = 0; j < ySize; j++){			
			if(map[i][j]->getValue() == 1) {
				numOfDirtsLeft++;
			}
		}
	}
}

Node* Environment::GetMapNode(int _x, int _y) {

	return map[_x][_y];
}