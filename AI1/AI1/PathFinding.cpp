#include "PathFinding.h"

using namespace std;

PathFinding::PathFinding(Environment* _enviornment) {

	enviornment = _enviornment;
	m_initStartGoal = false;
	m_foundGoal = false;
}

PathFinding::~PathFinding(void) {

}

void PathFinding::FindPath(vector<Node*>* _followPath, Node* _startPos, Node* _targetPos) {

	m_PathToGoal = _followPath;
	ClearLists();
			
	m_startCell = _startPos;
	m_startCell->SetParent(NULL);
		
	m_GoalCell = _targetPos;

	m_GoalCell->SetParent(m_GoalCell);

	m_startCell->SetG(0.f);
	m_startCell->SetH(m_startCell->ManhattanDistance(m_GoalCell));

	m_openList.push_back(m_startCell);

	ContinuePath();
}	

Node* PathFinding::GetNextCell() {

	// Big number so the first will always be true
	float bestF = 999999999999999.f;
	int cellIndex = -1;
	Node* nextCell = NULL;
	
	for(unsigned int i = 0; i < m_openList.size(); i++) {

		if(m_openList[i]->GetF() < bestF)  {

			bestF = m_openList[i]->GetF();
			cellIndex = i;
		}
	}

	if(cellIndex >= 0) {
		nextCell = m_openList[cellIndex];
		if(graphSearch) {
			m_VisitedList.push_back(nextCell);
		}
		m_openList.erase(m_openList.begin() + cellIndex);
	}
	return nextCell;
}

// Add current node to open list, and update 
void PathFinding::PathOpened(Node* _node, float _newCost, Node* _parent) {

	//Check if exist in closed list
	if(graphSearch) {
		for(unsigned int i = 0; i < m_VisitedList.size(); i++) {
			if(_node->id() == m_VisitedList[i]->id()) {
				return;
			}
		}
	}

	// iterate trough open list
	for(unsigned int i = 0; i < m_openList.size(); i++) {

		//if current node is found
		if(_node->id() == m_openList[i]->id()) {

			float newF = _node->GetG() + m_openList[i]->GetH();

			if(m_openList[i]->GetF() > newF) {
				m_openList[i]->SetG(_node->GetG() +  _newCost);
				m_openList[i]->SetParent(_node);			
			} else {
				return;
			}
		}	
	}
	_node->SetParent(_parent);
	_node->SetG(_newCost);
	_node->SetH(_parent->ManhattanDistance(m_GoalCell));
	m_openList.push_back(_node);
}

void PathFinding::ContinuePath() {

	if(m_openList.empty()) {
		return;
	}
	while(true) {
		
		Node* currentCell = GetNextCell();
		
		//reached goal
		if(currentCell->id() == m_GoalCell->id()) {
			
			m_GoalCell->SetParent( currentCell->GetParent());
			m_startCell->SetParent(NULL);

			Node* getPath;

			for(getPath = m_GoalCell; getPath != NULL; getPath = getPath->GetParent()) {
				m_PathToGoal->push_back(getPath);
				cout<< getPath->x()<< " "<< getPath->y()<< "\n";
			}
			m_foundGoal = true;
			return;

		} else {
			int numOfLinks = currentCell->links.size();
			for(int i = 0; i < numOfLinks; i++) {

				Node* holderNode = enviornment->GetMapNode(currentCell->links[i][0], currentCell->links[i][1]);
				PathOpened(holderNode, currentCell->links[i][2] + currentCell->GetG(), currentCell);			
			}

			for(unsigned int i = 0; i < m_openList.size(); i++) {

				if(currentCell->id() == m_openList[i]->id()) {
					m_openList.erase(m_openList.begin() + i);
				}
			}
		}
	}
}

void PathFinding::ClearLists() { // Clean up.

	for(unsigned int i = 0; i < m_openList.size(); i++) {
		delete m_openList[i];
	}
	m_openList.clear();

	for(unsigned int i = 0; i < m_VisitedList.size(); i++) {
		delete m_VisitedList[i];
	}
	m_VisitedList.clear();

	for(unsigned int i = 0; m_PathToGoal->size(); i++) {
		//delete m_PathToGoal;
	}
	m_PathToGoal->clear();
}