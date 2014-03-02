#pragma once
#include <vector>
#include "Node.h"
#include "Environment.h"

class PathFinding {

public:
	PathFinding(Environment* _enviornment);

	~PathFinding(void);

	void FindPath(std::vector<Node*>* followPath, Node* startPos, Node* targetPos);
	void ClearOpenList();
	void ClearVisitedList();
	void ClearPathToGoal();
	bool m_initStartGoal;
	bool m_foundGoal;

private:
	void SetStartAndGoal(Node start, Node goal);
	void PathOpened(Node* _node, int x, int y, float newCost, Node* parent);
	Node* GetNextCell();
	void ContinuePath();

	Node *m_startCell;
	Node *m_GoalCell;
	Environment* enviornment;
	std::vector<Node*> m_openList;
	std::vector<Node*> m_VisitedList;
	std::vector<Node*>* m_PathToGoal;
};

