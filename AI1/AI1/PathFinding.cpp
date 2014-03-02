#include "PathFinding.h"

using namespace std;
PathFinding::PathFinding(Environment* _enviornment) {

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
		m_openList.clear();

		for(int i = 0; i < m_VisitedList.size(); i++) {

			delete m_VisitedList[i];
		}
		m_VisitedList.clear();

		m_PathToGoal = _followPath;
		for(int i = 0; m_PathToGoal->size(); i++) {

			delete m_PathToGoal;
		}
		m_PathToGoal->clear();

		m_startCell = _startPos;
		m_startCell->SetParent(NULL);
		
		m_GoalCell = _targetPos;
		m_GoalCell->SetParent(m_GoalCell);

		m_startCell->SetG(0.f);
		m_startCell->SetH(m_startCell->ManhattanDistance(m_GoalCell));

		m_openList.push_back(m_startCell);

		m_initStartGoal = true;

		if(m_initStartGoal) {

			ContinuePath();
		}
	}
}

Node* PathFinding::GetNextCell() {

	// Big number so the first will always be true
	float bestF = 999999999999999.f;
	int cellIndex = -1;

	Node* nextCell = NULL;

	for(int i = 0; i < m_openList.size(); i++) {

		if(m_openList[i]->GetF() < bestF)  {

			bestF = m_openList[i]->GetF();
			cellIndex = i;
		}
	}

	if(cellIndex >= 0) {

		nextCell = m_openList[cellIndex];
		m_VisitedList.push_back(nextCell);
		m_openList.erase(m_openList.begin() + cellIndex);
	}

	return nextCell;
}

void PathFinding::PathOpened(Node* _node, int _x, int _y, float _newCost, Node* _parent) {

	/*if(CELL_BLOCKED) {
		return;
	}*/

	for(int i = 0; i < m_VisitedList.size(); i++) {

		if(_node->id() == m_VisitedList[i]->id()) {

			return;
		}

		Node* holderNode = _node;
		holderNode->SetG(_newCost);
		holderNode->SetH(_parent->ManhattanDistance(m_GoalCell));

		for(int i = 0; i < m_openList.size(); i++) {


		}
	}
}
