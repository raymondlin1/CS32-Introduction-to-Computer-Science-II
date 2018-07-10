#include "History.h"
#include "globals.h"
#include <iostream>
using namespace std;

History::History(int nRows, int nCols) 
	: m_nRows(nRows), m_nCols(nCols)
{
	for (int i = 0; i < nRows; i++) 
	{
		for (int j = 0; j < nCols; j++)
		{
			m_history[i][j] = 0;
		}
	}
}

bool History::record(int r, int c)
{
	if (r > MAXROWS || c > MAXCOLS)
	{
		return false;
	}
	else
	{
		m_history[r - 1][c - 1]++;
		return true;
	}
}

void History::display() const
{
	// Position (row,col) in the city coordinate system is represented in
	// the array element grid[row-1][col-1]
	char grid[MAXROWS][MAXCOLS];
	int r, c;

	// Fill the grid with dots
	for (r = 0; r < m_nRows; r++)
		for (c = 0; c < m_nCols; c++)
			grid[r][c] = '.';

	//check the history object and indicate any locations that have been unsuccessfully preached to
	for (r = 0; r < m_nRows; r++)
	{
		for (c = 0; c < m_nCols; c++)
		{
			if (m_history[r][c] != 0)
			{
				grid[r][c] = m_history[r][c] + 64;
			}
		}
	}

	// Draw the grid
	clearScreen();
	for (r = 0; r < m_nRows; r++)
	{
		for (c = 0; c < m_nCols; c++)
			cout << grid[r][c];
		cout << endl;
	}
	cout << endl;
}