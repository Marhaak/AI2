#include "PathFinding.h"


PathFinding::PathFinding(Enviorment* _enviornment) {

	enviornment = _enviornment;
	m_initStartGoal = false;
	m_foundGoal = false;
}


PathFinding::~PathFinding(void) {

}


void PathFinding::FindPath(std::vector<Node*>* _followPath, Node* _startPos, Node* _targetPos) {

	if(!m_initStartGoal) {

		for(int i = 0; i < m_openList.size(); i++) {

			delete m_openList[i];
		}
		m_openList.clear;

		for(int i = 0; i < m_VisitedList.size; i++) {

			delete m_VisitedList[i];
		}
		m_VisitedList.clear();

		m_PathToGoal = _followPath;
		for(int i = 0; m_PathToGoal->size(); i++) {

			delete m_PathToGoal;
		}
		m_PathToGoal->clear();

		Node start();
		start.x_coord = currentPos.x();

	}
}
