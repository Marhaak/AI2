#include "Include.h"
#include "Node.h"

using namespace std;

Node::Node(int init){
	//Creation
	value = init;
	visited = false;
}

Node::~Node(){
	//Destruction
}

// 0 clean, 1 dirty, 2 blocked, 3 unknown/yet to visit, 4 node for Ai2
int Node::getValue(){
	return value;
}

int Node::setValue(int _new){
	value = _new;
	return value;
}

void Node::visit(bool set){

	if(set){
		visited = true;
	} else { 
		visited = false; 
	}
}

bool Node::getVisit() {
	return visited;
}


void Node::readFile(std::ifstream &in){
	int ant;
	in >> ant;
	for( int x = 0; x < ant; x++){

		std::vector<int> link;
		for (int y = 0; y < 3; y++){
			int temp;
			in >> temp;
			link.push_back( temp );
		}
		links.push_back( link );

	}
}