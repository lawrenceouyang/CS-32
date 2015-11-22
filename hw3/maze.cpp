#include <iostream>
using namespace std;

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{                                                                                    
	maze[sr][sc] = '#';
	if (sr == er && sc == ec)
		return true;
	if (sr-1 > 0 && maze[sr-1][sc] == '.')
		if (pathExists(maze, nRows, nCols, sr-1, sc, er, ec)) //North Check
			return true;
	if (sc+1 < nCols-1 && maze[sr][sc+1] == '.')
		if (pathExists(maze, nRows, nCols, sr, sc+1, er, ec)) //East Check
			return true;
	if (sr+1 < nRows-1 && maze[sr+1][sc] == '.')
		if (pathExists(maze, nRows, nCols, sr+1, sc, er, ec)) //South Check
			return true;
	if (sc-1 > 0 && maze[sr][sc-1] == '.')
		if (pathExists(maze, nRows, nCols, sr, sc-1, er, ec)) //West Check
			return true;
	return false;
}
