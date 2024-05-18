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
	LBLock temp;
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
void Grid::Update()
{
	//Make the current block fall or accept movement
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
	if (currentBLock.rotation > 3)//TODO: Make it like a clamp and move it to block logic?
	{
		currentBLock.rotation = 0;
	}
}

void Grid::RotateccwCurrent()
{
	currentBLock.rotation--;
	if (currentBLock.rotation<0)
	{
		currentBLock.rotation = 3;
	}
}

Grid::Grid()
{
	std::cout <<"construct!\n";
}


