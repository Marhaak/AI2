//#pragma once
//#include <vector>
//#include "Node.h"
//
//class PathFinding {
//
//public:
//	PathFinding(void);
//
//	~PathFinding(void);
//
//	vector<Node>FindPath(Node* startPos, Node* targetPos);
//	void ClearOpenList();
//	void ClearVisitedList();
//	void ClearPathToGoal();
//	bool m_initStartGoal;
//	bool m_foundGoal;
//
//private:
//	void SetStartAndGoal(seachCell start, seachCell goal);
//	void PathOpened(int x, int y, float newCost, seachCell* parent);
//	seachCell *GetNextCell();
//	void ContinuePath();
//
//	seachCell *m_startCell;
//	seachCell *m_GoalCell;
//	std::vector<seachCell*> m_openList;
//	std::vector<seachCell*> m_VisitedList;
//	//std::vector< std::vector<int> > m_PathToGoal;
//};
//
