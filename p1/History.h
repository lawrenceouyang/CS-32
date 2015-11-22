#ifndef HISTORY_H
#define HISTORY_H

#include "globals.h"

class History
{
public:
	// Constructor/Destructor
	History(int nRows, int nCols);

	bool record(int r, int c);
	void display() const;

private:
	int m_rows;
	int m_cols;
	int m_dead[MAXROWS][MAXCOLS];

};

#endif HISTORY_H