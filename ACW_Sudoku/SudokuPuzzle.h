#pragma once

#include <iostream>
#include <fstream>
#include "Cell.h"
#include "CellGroup.h"
using namespace std;

class SudokuPuzzle
{
public:
	SudokuPuzzle(void);
	~SudokuPuzzle(void);
	void Solve(char filenameIn[]);
	void SudokuPuzzle::SolvePuzzle();
	bool SudokuPuzzle::CheckIfSolved()const;
private:
	int array[9][9];
	void Output() const;
	Cell m_grid[9][9];
	void InitialiseGrid();
	CellGroup m_gridRows[9];
	CellGroup m_gridColumns[9];
	CellGroup m_gridBlocks[9];
};

