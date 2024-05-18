#include "Grid.h"



void Grid::Initialize()
{
	numRows = 11;
	numCols = COLUMN;
	cellSize = CELL_SIZE;
	blockColors = GetBlockColors();
	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numCols; j++)
		{
			grids[i][j] = 0;
		}

	}

	blocks = { LBLock{}, JBLock {},IBLock{},OBLock{},SBLock{},TBLock{}, ZBLock{} };
	IBLock temp;
	currentBLock = temp;
}

void Grid::Draw()
{
	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numCols; j++)
		{
			DrawRectangle(i*CELL_SIZE+10+OFFSET_X, j * CELL_SIZE+10 + OFFSET_Y, cellSize-1, cellSize-1, blockColors[grids[i][j]]);
		}

	}

	currentBLock.Draw();
}
int tempCurrentINdex = 0;
void Grid::Update()
{
	//Make the current block fall or accept movement
	//TESTING
	if (IsKeyPressed(KEY_G))
	{
		tempCurrentINdex++;
		tempCurrentINdex = tempCurrentINdex < blocks.size() ? tempCurrentINdex:0;
		currentBLock = blocks[tempCurrentINdex];
	}
	FallBlocks();
}

void Grid::MoveCurrentLeft()
{
	currentBLock.x--;
}


void Grid::MoveCurrentRight()
{
	currentBLock.x++;
}

void Grid::MoveCurrentDown()
{
	currentBLock.y++;
}

void Grid::RotatecwCurrent()
{
	currentBLock.rotation++;
	if (currentBLock.rotation >= currentBLock.rotationMap.size())//TODO: Make it like a clamp and move it to block logic?
	{
		currentBLock.rotation = 0;
	}
}

void Grid::RotateccwCurrent()
{
	currentBLock.rotation--;
	if (currentBLock.rotation<0)
	{
		currentBLock.rotation = currentBLock.rotationMap.size()-1;
	}
}

void Grid::FallBlocks()
{
	elaspedSinceLast += 1.0f * GetFrameTime();
	if (elaspedSinceLast>waitTime)
	{
		elaspedSinceLast = 0;
		currentBLock.y++;
    }
}

Grid::Grid()
{
	std::cout <<"construct!\n";
}


