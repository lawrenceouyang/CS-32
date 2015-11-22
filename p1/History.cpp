#include <iostream>

#include "History.h"
#include "Arena.h"
using namespace std;

History::History(int nRows, int nCols)
{
	m_rows = nRows;
	m_cols = nCols;

	for (int r = 0; r < m_rows; r++)
		for (int c = 0; c < m_cols; c++)
			m_dead[r][c] = 0;
}

bool History::record(int r, int c)
{
	if (r > m_rows || c > m_cols || r < 1 || c < 1)
		return false;

	m_dead[r-1][c-1]++;
	return true;
}

void History::display() const
{    
	char displayGrid[MAXROWS][MAXCOLS];
	int r, c;
    
	// Indicate dead Zombies
	for (r = 1; r <= m_rows; r++)
        for (c = 1; c <= m_cols; c++)
		{
			if (m_dead[r-1][c-1] == 0)
				displayGrid[r-1][c-1] = '.';
			else if (m_dead[r-1][c-1] > 0 && m_dead[r-1][c-1] < 27)
				displayGrid[r-1][c-1] = 64+m_dead[r-1][c-1];
			else if (m_dead[r-1][c-1] >= 27)
				displayGrid[r-1][c-1] = 90;
		}

	// Draw the grid
    clearScreen();
    for (r = 1; r <= m_rows; r++)
    {
        for (c = 1; c <= m_cols; c++)
            cout << displayGrid[r-1][c-1];
        cout << endl;
    }
    cout << endl;
}