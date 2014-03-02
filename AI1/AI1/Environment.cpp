#include "Node.h"
#include "Include.h"
#include "Environment.h"

using namespace std;

Environment::Environment(int _x, int _y, int _dirt, int _obj){

	graphix = new Graphix(_x*32, _y*32);
	renderer = graphix->Renderer();

	botX = 0;
	botY = 0;

	xSize = _x;
	ySize = _y;
	numOfDirts = _dirt;
	NumOfDirtsCleaned = 0;
	srand( time(NULL) );
	
	int id = 0;
	for (int i = 0; i < _x; i++){

		std::vector<Node*> temp;
		map.push_back( temp );
		for (int j = 0; j < _y; j++){

			map[i].push_back( new Node(0) );
			map[i][j]->x(i); map[i][j]->y(j); map[i][j]->id(id++);
		}
	}

	//Setting dirt
	for (int i = 0; i < _dirt; i++){
		SetStartNode()->setValue(1);
	}
	//Setting obj
	for (int j = 0; j < _obj; j++){
		SetStartNode()->setValue(2);
	}
}



Environment::Environment(std::string _file){

	botX = 0;
	botY = 0;

	ifstream file(_file);
	file >> xSize >> ySize;

	graphix = new Graphix(xSize*32, ySize*32);
	renderer = graphix->Renderer();

	NumOfDirtsCleaned = 0;
	numOfDirts = 0;
	
	int id = 0;
	//read the map
	for (int i = 0; i< xSize; i++){

		std::vector<Node*> temp;
		map.push_back( temp );
		for (int j = 0; j < ySize; j++){

			int trash;
			file >> trash;
			if (trash == 1){ numOfDirts++; }

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



//returns the node the bot is trying to move into
Node* Environment::isMoveAble(int _x, int _y) {

	//if outside the map, return a node that is a wall.
	if(_x+botX > xSize-1 || _x+botX < 0 || _y+botY > ySize-1 || _y+botY < 0) {
		return new Node(2);
	}
	//there is an offset to where the bot is, and where it thinks it is.
	else return map[_x+botX][_y+botY];
}



//draws the environment
void Environment::draw(int _x, int _y){

	// Check for events
	graphix->Event(eventHander);
	
	// Setting new dirt if right conditions
	/*dirtCounter++;
	if( dirtCounter!= 0 && dirtCounter % numOfStepsBeforeNewDirt == 0 && reinsertDirt) {
		int xPosHolder = botX;
		int yPosHolder = botY;		
		SetStartNode()->setValue(1);		
		botX = xPosHolder;
		botY = yPosHolder;
		numOfDirts++;
	}*/
	
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
			
			for(int z = 0; z < map[i][j]->links.size(); z++){
				graphix->Draw(i, j, map[i][j]->links[z][0], map[i][j]->links[z][1]);
			}
		}		
	}

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



void Environment::AddCleanedNode() {
	numOfDirts--;
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
		cout << endl;
	}
	cout<< numOfDirtsLeft<< " dirts left\nOn a "<< xSize * ySize<< " map\n";
}

Node* Environment::GetMapNode(int _x, int _y) {

	return map[_x][_y];
}