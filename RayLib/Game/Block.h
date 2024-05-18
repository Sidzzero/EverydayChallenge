#pragma once
#include "Common.h"

class Block
{
public:
	int x;
	int y;
	int rotation = 0;
	Color color;
	std::unordered_map<int, std::vector<Position>> rotationMap;//BETTER TO MANAGE THINGS. EACH NEW BLOCKS ADDS ITS STUFF HERE
	void Draw() 
	{
		auto tempCurrentPos = rotationMap[rotation];
		for (int i=0;i<tempCurrentPos.size();i++)
		{
			DrawRectangle(x+ tempCurrentPos[i].x*CELL_SIZE +OFFSET_X+11,x + tempCurrentPos[i].y * CELL_SIZE + OFFSET_Y + 11, CELL_SIZE-1, CELL_SIZE-1, color);
		}
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
		color = RED;
		rotationMap =
		{ {0 ,  std::vector<Position> { {0,1},{1,1},{2,1},{2,2} }},
		  {1 ,  std::vector<Position> { {1,0},{1,1},{1,2},{2,0} }},
		  {2 ,  std::vector<Position> { {0,0},{0,1},{1,1},{2,1} }},
		  {3 ,  std::vector<Position> { {0,2},{1,2},{1,1},{1,0} }}
		};
	}
};


