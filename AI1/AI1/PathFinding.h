#pragma once
#include <vector>
#include "Node.h"
#include "Environment.h"

class PathFinding {

public:
	PathFinding(Environment* _enviornment);

	~PathFinding(void);

	void FindPath(std::vector<Node*>* followPath, Node* startPos, Node* targetPos); // Starting up the pathfinding
	void ClearLists();					// Cleas the lists
	bool m_initStartGoal;
	bool m_foundGoal;

private:
//	void SetStartAndGoal(Node start, Node goal);
	void PathOpened(Node* _node, float _newCost, Node* _parent);	// Adding the new nodes to the openlist
	Node* GetNextCell();				// Getting the next cell in the openlist
	void ContinuePath();				// Going tho the map and finds a path

	Node *m_startCell;
	Node *m_GoalCell;
	Environment* enviornment;		
	std::vector<Node*> m_openList;		// The list over opended nodes
	std::vector<Node*> m_VisitedList;	// The list over visited nodes
	std::vector<Node*>* m_PathToGoal;	//The path to the goal node
};