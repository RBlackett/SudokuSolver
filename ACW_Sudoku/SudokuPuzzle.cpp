#include "SudokuPuzzle.h"
#include <Windows.h>

SudokuPuzzle::SudokuPuzzle(void) 
{
	array[0][0] = { 0 };
}

SudokuPuzzle::~SudokuPuzzle(void)
{
}

// The method that is called by the main file
void SudokuPuzzle::Solve(char filenameIn[])
{
	// Streaming in the puzzle file
	ifstream fin(filenameIn);
	size_t i = 0;
	while (i < 81 && fin >> array[i / 9][i % 9]) i++;
	InitialiseGrid();
	LARGE_INTEGER start, end, frequency;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start);

	SolvePuzzle();

	QueryPerformanceCounter(&end);
	float time = (end.QuadPart - start.QuadPart) / (static_cast<float> (frequency.QuadPart));
	std::cout << endl << "Time taken to solve puzzle: " << endl << std::fixed << time << endl << endl;

	Output();  // Output the solved puzzle
}

// Method for initialising the grid, based on the array loaded in from the text file
void SudokuPuzzle::InitialiseGrid()
{
	int row = 0;
	int column = 0;;
	int block_incrementer = 0;
	int block_current_pos = 0;
	int block_number = 0;
	int grid3 = 0;

	for (int i = 0; i < 9; ++i)
	{
		for (int x = 0; x < 9; ++x)
		{
			if (column > 8)
			{
				column = 0;
				row++;
			}
			if (block_incrementer > 2)
			{
				block_incrementer = 0;
				block_number++;
				grid3++;
				if (grid3 > 2)
				{
					grid3 = 0;
					if (row <= 2) {
						block_number = 0;
					}
					else if (row <= 5) {
						block_number = 3;
					}
					else if (row <= 8) {
						block_number = 6;
					}
				}
			}
			if (row == 0 || row == 3 || row == 6)
			{
				block_current_pos = block_incrementer;
			}
			else if (row == 1 || row == 4 || row == 7)
			{
				block_current_pos = block_incrementer + 3;
			}
			else if (row == 2 || row == 5 || row == 8)
			{
				block_current_pos = block_incrementer + 6;
			}
			m_grid[i][x] = array[i][x];
			m_gridRows[i].SetCell(x, &m_grid[i][x]);
			m_gridColumns[x].SetCell(i, &m_grid[i][x]);
			m_gridBlocks[block_number].SetCell(block_current_pos, &m_grid[i][x]);
			column++;
			block_incrementer++;
		}
	}
}

// Method to check all cells of the puzzle are solved
bool SudokuPuzzle::CheckIfSolved()const
{
	for (int y = 0; y < 9; ++y)
	{
		for (int x = 0; x < 9; ++x)
		{
			if (m_grid[y][x].Get_Solved() == false)
				return false;
		}
	}
	return true;
}

// Method for the actual solving of the puzzle, based on initialised grids
void SudokuPuzzle::SolvePuzzle()
{
	while (CheckIfSolved() == false) // Loops infinitely if any cell's value is 0
	{
		for (int y = 0; y < 9; ++y)
		{
			for (int x = 0; x < 9; ++x)
			{
				if (m_grid[y][x].Get_Solved() != true)
				{
					int block = ((x / 3) + ((y / 3) * 3));
					std::vector<int> RowNumbers = m_gridRows[y].GetValuesInGroup();
					std::vector<int> ColumnNumbers = m_gridColumns[x].GetValuesInGroup();
					std::vector<int> BlockNumbers = m_gridBlocks[block].GetValuesInGroup();
					std::vector<int> LocatedNumbers;
					LocatedNumbers.reserve(RowNumbers.size() + ColumnNumbers.size() + BlockNumbers.size());
					LocatedNumbers.insert(LocatedNumbers.end(), RowNumbers.begin(), RowNumbers.end());
					LocatedNumbers.insert(LocatedNumbers.end(), ColumnNumbers.begin(), ColumnNumbers.end());
					LocatedNumbers.insert(LocatedNumbers.end(), BlockNumbers.begin(), BlockNumbers.end());
					for (int i = 0; i < LocatedNumbers.size(); ++i)
					{
						int j = LocatedNumbers.at(i);
						m_grid[y][x].Edit_Candidate_List(j);
					}
					RowNumbers.clear();
					ColumnNumbers.clear();
					BlockNumbers.clear();
					LocatedNumbers.clear();
				}
			}
		}
	}
}

// Method for outputting the solved puzzle to a different text file
void SudokuPuzzle::Output() const
{
	ofstream fout("sudoku_solution.txt"); // DO NOT CHANGE THE NAME OF THIS FILE
	if(fout.is_open())
	{
		for(int y = 0; y < 9; ++y)
		{
			for(int x = 0; x < 9; ++x)
			{
				fout << m_grid[y][x].Get_Value() << " ";
				cout << m_grid[y][x].Get_Value() << " ";
			}
			fout << endl;
			cout << endl;
		}
		fout.close();
	}
}