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

// 0 clean, 1 dirty, 2 blocked, 3 unknown/yet to visit
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