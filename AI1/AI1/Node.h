#pragma once

#include "Include.h"

class Node {

private:
	// Variables
	// 0 clean, 1 dirty, 2 blocked, 3 unknown/yet to visit
	int value;
	bool visited;
	std::vector< std::vector<int> > links;
	
	// Functions

public:

	// Variables

	// Functions
	Node(int init);
	~Node();
	int getValue();			// Returns the valus of the node
	int setValue(int _new);	// Sets a new value
	void visit(bool set = true);			// Sets the node til visited
	bool getVisit();		// Returns the visit status
	void readFile(std::ifstream &in);
};