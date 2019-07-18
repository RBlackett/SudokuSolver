#include "Cell.h"

Cell::Cell(void)
{
	m_solved = false;
	m_value = 0;
}

// Setting solved state to true if value isn't 0.
Cell::Cell(int value) :m_value(value), m_solved(false)
{
	if (m_value != 0)
	{
		m_solved = true;
	}
	else
	{
		for (int i = 1; i < 10; i++)
		{
			m_candidateList.push_back(i);
		}
	}
}

// Set and Get methods for the numerical value in a cell
void Cell::Set_Value(const int Value_Number)
{
	this->m_value = Value_Number;
	this->m_solved = true;
}
int Cell::Get_Value()const
{
	return this->m_value;
}

// Returns whether a cell has been solved or not
bool Cell::Get_Solved()const
{
	return this->m_solved;
}

// Method for removing integers from the cell's candidate list
void Cell::Edit_Candidate_List(const int value_to_remove)
{
	for (int i = 0; i < m_candidateList.size(); i++)
	{
		int candidate = m_candidateList.at(i);
		if (candidate == value_to_remove)
		{
			m_candidateList.erase(m_candidateList.begin() + i);
			break;
		}
	}
	// If candidate list contains only 1 element, cell is a naked single and should be solved.
	if (m_candidateList.size() == 1)
	{
		Set_Value(m_candidateList[0]);
	}
}

// Returns the current candidate list of a cell
std::vector<int> Cell::Get_Candidate_List()const
{
	return this->m_candidateList;
}

Cell::~Cell(void)
{
}