#pragma once
#include "Common.h"
#include "BlockColor.h"
#include "Block.h"

class Grid
{
public :
	int grids[20][10];//Holds the color 
	std::vector<Block> blocks;
	void Initialize();
	void Draw();
	void Update();
	void MoveCurrentLeft();
	void MoveCurrentRight();
	void MoveCurrentDown();
	void RotatecwCurrent();
	void RotateccwCurrent();
	Grid();

private:
	int numRows = 1;
	int numCols = 1;
	int cellSize ;
	std::vector<Color> blockColors;

	Block currentBLock;
	Block nextBLock;

};

