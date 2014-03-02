#pragma once

#include "Include.h"

class Node {

private:
	// Variables
	// 0 clean, 1 dirty, 2 blocked, 3 unknown/yet to visit
	int value;
	bool visited;
	
	int x_pos;
	int y_pos;
	float G;
	float H;
	
	// Functions

public:
	// Variables
	std::vector< std::vector<int> > links;

	// Functions
	Node(int init);
	~Node();
	int getValue();			// Returns the valus of the node
	int setValue(int _new);	// Sets a new value
	void visit(bool set = true);			// Sets the node til visited
	bool getVisit();		// Returns the visit status
	void readFile(std::ifstream &in);
	float GetF();
	float ManhattanDistance(Node* nodeEnd);

	int x();
	int y();
	int x(int _x);
	int y(int _y);
};