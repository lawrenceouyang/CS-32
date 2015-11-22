#include <queue>
#include <iostream>
using namespace std;

class Coord
{
public:
	Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
	int r() const { return m_r; }
	int c() const { return m_c; }
private:
	int m_r;
	int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) //Given the assumptions stated,
{                                                                                    //parameters nRows and nCols are
	queue<Coord> coordQueue;                                                         //uneeded.
	coordQueue.push(Coord(sr, sc));
	maze[sr][sc] = '#';
	while (!coordQueue.empty())
	{
		Coord curr = coordQueue.front();
		if (curr.r() == er && curr.c() == ec)
			return true;
		coordQueue.pop();
		if (curr.r()-1 > -1 && maze[curr.r()-1][curr.c()] != 'X' && maze[curr.r()-1][curr.c()] != '#') //North Check
		{
			maze[curr.r()-1][curr.c()] = '#';
			coordQueue.push(Coord(curr.r()-1,curr.c()));
		}
		if (curr.c()+1 < nCols && maze[curr.r()][curr.c()+1] != 'X' && maze[curr.r()][curr.c()+1] != '#') //East Check
		{
			maze[curr.r()][curr.c()+1] = '#';
			coordQueue.push(Coord(curr.r(),curr.c()+1));
		}
		if (curr.r()+1 < nRows && maze[curr.r()+1][curr.c()] != 'X' && maze[curr.r()+1][curr.c()] != '#') //South Check
		{
			maze[curr.r()+1][curr.c()] = '#';
			coordQueue.push(Coord(curr.r()+1,curr.c()));
		}
		if (curr.c()-1 > -1 && maze[curr.r()][curr.c()-1] != 'X' && maze[curr.r()][curr.c()-1] != '#') //West Check
		{
			maze[curr.r()][curr.c()-1] = '#';
			coordQueue.push(Coord(curr.r(),curr.c()-1));
		}
	}
	return false;
}