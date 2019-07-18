#include "CellGroup.h"

CellGroup::CellGroup(void)
{
	m_cells[0] = { 0 };
}

// Set and get methods for cellgroups
void CellGroup::SetCell(int index, Cell *cell)
{
	m_cells[index] = cell;
}
Cell CellGroup::GetCell(int index)const
{
	return *m_cells[index];
}

// Method to return all the numerical values within a group, for example within a row, column or 3x3 block
std::vector<int> CellGroup::GetValuesInGroup()const
{
	std::vector<int> vector;
	for (int i = 0; i < 9; ++i)
	{
		vector.push_back(m_cells[i]->Get_Value());
	}
	return vector;
}

CellGroup::~CellGroup(void)
{
}