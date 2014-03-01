#include "SearchCell.h"

float seachCell::GetF() {

	return G + H;
}

float seachCell::ManhattanDistance(seachCell * nodeEnd) {

	float x = (float)(abs(this->x_coord - nodeEnd->x_coord));
	float y = (float)(abs(this->y_coord - nodeEnd->y_coord));

	return x + y;
}

int seachCell::x() { return x_coord; }

int seachCell::y() { return y_coord; }

void seachCell::y(int _y){y_coord = _y;}

void seachCell::x(int _x){x_coord = _x;}