#pragma once
#include "Cell.h"
class CellGroup
{
public:
	CellGroup(void);
	~CellGroup(void);
	void SetCell(int index, Cell *cell);
	Cell GetCell(int index)const;
	std::vector<int> CellGroup::GetValuesInGroup()const;
	// Other Methods
private:
	Cell* m_cells[9];
};