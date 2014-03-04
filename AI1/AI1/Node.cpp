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

Node::Node() {
	// Default constructor.
}

Node::~Node(){
	//Destruction and mayham
}

// 2 blocked, 3 unknown/yet to visit, 4 node for Ai2
int Node::getValue(){
	return value;
}

int Node::setValue(int _new){
	value = _new;
	return value;
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

// Calculates the distance from where the bot is 
// and to the goal node. Returns the value.
float Node::ManhattanDistance(Node* nodeEnd) {

	float x = (float)(abs(x_pos - nodeEnd->x_pos));
	float y = (float)(abs(y_pos - nodeEnd->y_pos));
	return x + y;
}

// Returns the X value in the node.
int Node::x() { return x_pos; }

// Returns the Y value in the node.
int Node::y() { return y_pos; }

// Returns the ID.
int Node::id(){ return ID; }

// Defines the X value of the node.
int Node::x(int _x) {
	x_pos = _x;
	return x_pos;
}

// Defines the Y value of the node.
int Node::y(int _y) {
	y_pos = _y;
	return y_pos;
}

// Sets the ID for the node and returns it.
int Node::id(int _ID){
	ID = _ID;
	return ID;
}

// Sets the G value and returns it.
float Node::SetG(float _G) {
	G = _G;
	return G;
}

// Sets the H value and returns it.
float Node::SetH(float _H) {
	H = _H;
	return G;
}

// Returns G value
float Node::GetG() {
	return G;
}

// Returns H value
float Node::GetH() {
	return H;
}

// Sets the parent node
void Node::SetParent(Node* _parentNode) {
	parent = _parentNode;
}

// Returns the parent node.
Node* Node::GetParent() {
	return parent;
}