#pragma once

#include "Include.h"

class Node {

private:
	// Variables
	// 0 clean, 1 dirty, 2 blocked, 3 unknown/yet to visit
	int value;
	bool visited;
	
	int ID;
	int x_pos;
	int y_pos;
	float G;
	float H;
	Node* parent;
	
	// Functions

public:
	// Variables
	std::vector< std::vector<int> > links;

	// Functions
	Node(int init);
	Node();
	~Node();
	int getValue();			// Returns the valus of the node
	int setValue(int _new);	// Sets a new value
	void readFile(std::ifstream &in);
	float GetF();
	float ManhattanDistance(Node* nodeEnd);

	int x();	// Returns the X value.
	int y();	// Returns the Y value.
	int x(int _x);	// Sets the X value and returns it.
	int y(int _y);	// Sets the Y value and returns it.
	int id();		// Returns the ID value.
	int id(int _ID);// Sets the ID value and returns it. 
	float SetG(float _G);	// Sets the G value.
	float SetH(float _H);	// Sets the H value.
	float GetG();	// Returns the G value.
	float GetH();	// Returns the H value.
	void SetParent(Node* _parentNode);	// Sets new value of the parent.
	Node* GetParent();	// Returns Node pointer with parent.
};