#pragma once
#include <vector>
#include "SearchCell.h"

class PathFinding {

public:
	PathFinding(void);

	~PathFinding(void);

	void FindPath(/*startPos, targetPos*/);
	void ClearOpenList();
	void ClearVisitedList();
	void ClearPathToGoal();
	bool m_initStartGoal;
	bool m_foundGoal;

private:
	void SetStartAndGoal(seachCell start, seachCell goal);
	void PathOpened(int x, int y, float newCost, seachCell* parent);
	seachCell *GetNextCell();
	void ContinuePath();

	seachCell *m_startCell;
	seachCell *m_GoalCell;
	std::vector<seachCell*> m_openList;
	std::vector<seachCell*> m_VisitedList;
	//std::vector<vector3*> m_PathToGoal;
};

