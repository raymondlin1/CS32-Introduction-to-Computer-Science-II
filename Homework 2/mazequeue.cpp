#include <queue>
#include <string>
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

//empty
//size
//front
//back
//push
//emplace
//pop
//swap

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise
{
	queue<Coord> coordQueue;
	Coord start(sr, sc);
	coordQueue.push(start);
	maze[sr][sc] = 'v';

	while (coordQueue.size() != 0)
	{
		int curRow = coordQueue.front().r();
		int curCol = coordQueue.front().c();
		coordQueue.pop();
		if (curRow == er && curCol == ec)
			return true;

		//check east
		if (maze[curRow][curCol + 1] == '.')
		{
			maze[curRow][curCol + 1] = 'v';
			Coord c(curRow, curCol + 1);
			coordQueue.push(c);
		}

		//check south
		if (maze[curRow + 1][curCol] == '.')
		{
			maze[curRow + 1][curCol] = 'v';
			Coord c(curRow + 1, curCol);
			coordQueue.push(c);
		}

		//check west
		if (maze[curRow][curCol - 1] == '.')
		{
			maze[curRow][curCol - 1] = 'v';
			Coord c(curRow, curCol - 1);
			coordQueue.push(c);
		}

		//check north
		if (maze[curRow - 1][curCol] == '.')
		{
			maze[curRow - 1][curCol] = 'v';
			Coord c(curRow - 1, curCol);
			coordQueue.push(c);
		}
	}
	return false;
}

int main()
{

	string maze[10] = {
		"XXXXXXXXXX",
		"X...X..X.X",
		"X..XX....X",
		"X.X.XXXX.X",
		"XXX......X",
		"X...X.XX.X",
		"X.X.X..X.X",
		"X.XXXX.X.X",
		"X..X...X.X",
		"XXXXXXXXXX"
	};

	if (pathExists(maze, 10, 10, 4, 3, 1, 8))
		cout << "Solvable!" << endl;
	else
		cout << "Out of luck!" << endl;
}