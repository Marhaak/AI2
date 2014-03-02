#pragma once
#include <vector>
#include "Node.h"
#include "Enviorment.h"

class PathFinding {

public:
	PathFinding(Enviorment* _enviornment);

	~PathFinding(void);

	void FindPath(std::vector<Node> followPath, Node* startPos, Node* targetPos);
	void ClearOpenList();
	void ClearVisitedList();
	void ClearPathToGoal();
	bool m_initStartGoal;
	bool m_foundGoal;

private:
	void SetStartAndGoal(Node start, Node goal);
	void PathOpened(int x, int y, float newCost, Node* parent);
	Node *GetNextCell();
	void ContinuePath();

	Node *m_startCell;
	Node *m_GoalCell;
	Enviorment* enviornment;
	std::vector<Node*> m_openList;
	std::vector<Node*> m_VisitedList;
	//std::vector< std::vector<int> > m_PathToGoal;
};

