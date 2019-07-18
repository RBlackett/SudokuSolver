#pragma once
#include <vector>
class Cell
{
public:
	Cell(void);
	Cell(int value);
	~Cell(void);
	void Cell::Set_Value(const int Value_Number);
	int Cell::Get_Value()const;
	bool Cell::Get_Solved()const;
	void Cell::Edit_Candidate_List(const int value_to_remove);
	std::vector<int> Cell::Get_Candidate_List()const;
private:
	std::vector<int> m_candidateList; // or int m_candidateList[9];
	int m_value;
	bool m_solved;
};