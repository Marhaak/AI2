#include "Node.h"
#include "Include.h"
#include "Environment.h"

using namespace std;

Environment::Environment(std::string _file){

	botX = 0;	// keeps track of the position of 
	botY = 0;	// the bot.

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
			file >> trash;	// Retrieves from file the map setup.
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
	// Clean up
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

Node* Environment::GetMapNode(int _x, int _y) {

	return map[_x][_y];	// Returns the specified node.
}