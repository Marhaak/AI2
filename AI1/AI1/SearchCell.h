#pragma once
#include <cmath>

const int WORLD_SIZE = 15;

class seachCell {

private:
	int x_coord;
	int y_coord;
	int m_id;
	seachCell * parent;
	float G; //steps from start node
	float H; //esimated distance to the goal

public:
	seachCell() : parent(0) {}
	seachCell(int x, int y, seachCell* _parent = 0) : x_coord(x), y_coord(y), parent(_parent), m_id(x * WORLD_SIZE + y), G(0), H(0) {};

	float GetF(); // return G + H;
	float ManhattanDistance(seachCell * nodeEnd);

	int x();
	int y();
};