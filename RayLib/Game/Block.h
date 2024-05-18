#pragma once
#include "Common.h"
#include "BlockColor.h"
class Block
{
public:
	int id = 0;
	int x;
	int y;
	int rotation = 0;
	Color color;
	std::unordered_map<int, std::vector<Position>> rotationMap;//BETTER TO MANAGE THINGS. EACH NEW BLOCKS ADDS ITS STUFF HERE
	void Draw() 
	{
		auto tempCurrentPos = GetCurrentPositions();

		for (int i=0;i<tempCurrentPos.size();i++)
		{
			DrawRectangle((tempCurrentPos[i].x)*CELL_SIZE +OFFSET_X+11,( tempCurrentPos[i].y) * CELL_SIZE + OFFSET_Y + 11, CELL_SIZE-1, CELL_SIZE-1, color);
		}
	}

	std::vector<Position> GetCurrentPositions()
	{
		auto tempCurrentPos = rotationMap[rotation];
		std::vector<Position> result;
		for (auto pos : tempCurrentPos)
		{
			result.push_back(Position{ pos.x + x ,pos.y + y });
		}
		return result;
	}

	void Move(int a_x, int a_y)
	{
		x += a_x;
		y += a_y;
	}

};

/*
* L BLOCK
0 1 0
0 1 0
0 1 1

0 0 0
1 1 1
1 0 0

1 1 0
0 1 0
0 1 0

0 0 1
1 1 1
0 0 0
*/
class LBLock : public Block
{
public:
	LBLock()
	{
		x = 0;
		y = 0;
		id = 1;
		color = LBlockColor;
		rotationMap =
		{ {0 ,  std::vector<Position> { {0,1},{1,1},{2,1},{2,2} }},
		  {1 ,  std::vector<Position> { {1,0},{1,1},{1,2},{2,0} }},
		  {2 ,  std::vector<Position> { {0,0},{0,1},{1,1},{2,1} }},
		  {3 ,  std::vector<Position> { {0,2},{1,2},{1,1},{1,0} }}
		};
	}
};

class JBLock : public Block
{
public:
	JBLock()
	{
		x = 0;
		y = 0;
		id = 2;
		color = JBlockColor;
		rotationMap =
		{ {0 ,  std::vector<Position> { {0,0},{1,0},{1,1},{1,2} }},
		  {1 ,  std::vector<Position> { {0,1},{0,2},{1,1},{2,1} }},
		  {2 ,  std::vector<Position> { {1,0},{1,1},{1,2},{2,2} }},
		  {3 ,  std::vector<Position> { {0,1},{1,1},{2,0},{2,1} }}
		};
	}
};
class IBLock : public Block
{
public:
	IBLock()
	{
		x = 0;
		y = 0;
		id = 3;
		color = IBlockColor;
		rotationMap =
		{ {0 ,  std::vector<Position> { {1,0},{1,1},{1,2},{1,3} }},
		  {1 ,  std::vector<Position> { {0,2},{1,2},{2,2},{3,2} }},
		  {2 ,  std::vector<Position> { {2,0},{2,1},{2,2},{2,3} }},
		  {3 ,  std::vector<Position> { {0,1},{1,1},{2,1},{3,1} }}
		};
	}
};

class OBLock : public Block
{
public:
	OBLock()
	{
		x = 0;
		y = 0;
		id = 4;
		color = OBlockColor;
		rotationMap =
		{ {0 ,  std::vector<Position> { {0,0},{0,1},{1,0},{1,1} }}
		};
	}
};

class SBLock : public Block
{
public:
	SBLock()
	{
		x = 0;
		y = 0;
		id = 5;
		color = SBlockColor;
		rotationMap =
		{ {0 ,  std::vector<Position> { {0,1},{0,2},{1,0},{1,1} }},
		  {1 ,  std::vector<Position> { {0,1},{1,1},{1,2},{2,2} }},
		  {2 ,  std::vector<Position> { {1,1},{1,2},{2,0},{2,1} }},
		  {3 ,  std::vector<Position> { {0,0},{1,0},{1,1},{2,1} }}
		};
	}
};

class TBLock : public Block
{
public:
	TBLock()
	{
		x = 0;
		y = 0;
		id = 6;
		color = TBlockColor;
		rotationMap =
		{ {0 ,  std::vector<Position> { {0,1},{1,0},{1,1},{1,2} }},
		  {1 ,  std::vector<Position> { {0,1},{1,1},{1,2},{2,1} }},
		  {2 ,  std::vector<Position> { {1,0},{1,1},{1,2},{2,1} }},
		  {3 ,  std::vector<Position> { {0,1},{1,0},{1,1},{2,1} }}
		};
	}
};


class ZBLock : public Block
{
public:
	ZBLock()
	{
		x = 0;
		y = 0;
		id = 7;
		color = ZBlockColor;
		rotationMap =
		{ {0 ,  std::vector<Position> { {0,0},{0,1},{1,1},{1,2} }},
		  {1 ,  std::vector<Position> { {0,2},{1,1},{1,2},{2,1} }},
		  {2 ,  std::vector<Position> { {1,0},{1,1},{2,1},{2,2} }},
		  {3 ,  std::vector<Position> { {0,1},{1,0},{1,1},{2,0} }}
		};
	}
};