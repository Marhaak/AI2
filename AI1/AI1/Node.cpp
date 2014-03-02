#include "Include.h"
#include "Node.h"

using namespace std;

Node::Node(int init){
	//Creation
	value = init;
	visited = false;
	x_pos = 0;
	y_pos = 0;
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

float Node::GetF() {

	return G + H;
}

float Node::ManhattanDistance(Node* nodeEnd) {

	float x = (float)(abs(x_pos - nodeEnd->x_pos));
	float y = (float)(abs(y_pos - nodeEnd->y_pos));

	return x + y;
}

int Node::x() { return x_pos; }

int Node::y() { return y_pos; }

int Node::x(int _x) {
	x_pos = _x;
	return x_pos;
}

int Node::y(int _y) {
	y_pos = _y;
	return y_pos;
}


int Node::id(){
	return ID;
}

int Node::id(int _ID){
	ID = _ID;
	return ID;
}